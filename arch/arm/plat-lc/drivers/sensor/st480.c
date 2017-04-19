/*
 * Copyright (C) 2012 Senodia.
 *
 * This software is licensed under the terms of the GNU General Public
 * License version 2, as published by the Free Software Foundation, and
 * may be copied, distributed, and modified under those terms.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 */

#include <linux/i2c.h>
#include <linux/slab.h>
#include <linux/miscdevice.h>
#include <linux/gpio.h>
#include <linux/uaccess.h>
#include <linux/delay.h>
#include <linux/input.h>
#include <linux/workqueue.h>
#include <linux/freezer.h>
#include <linux/ioctl.h>
#include <linux/module.h>
#include <plat/st480.h>

#if ST480_AUTO_TEST
#include <linux/kthread.h>
#endif

/*
 * Debug
 */
#define SENODIA_DEBUG_MSG       0
#define SENODIA_DEBUG_FUNC      0

#if SENODIA_DEBUG_MSG
#define SENODIADBG(format, ...) printk(KERN_INFO "SENODIA " format "\n", ## __VA_ARGS__)
#else
#define SENODIADBG(format, ...)
#endif

#if SENODIA_DEBUG_FUNC
#define SENODIAFUNC(func) printk(KERN_INFO "SENODIA " func " is called\n")
#else
#define SENODIAFUNC(func)
#endif
/*******************************************************************/

#define ST480IO                   0xA1

/* IOCTLs for hal*/
#define ECS_IOCTL_APP_SET_MFLAG		_IOW(ST480IO, 0x10, short)
#define ECS_IOCTL_APP_GET_MFLAG		_IOR(ST480IO, 0x11, short)
#define ECS_IOCTL_APP_SET_DELAY		_IOW(ST480IO, 0x12, short)
#define ECS_IOCTL_APP_GET_DELAY		_IOR(ST480IO, 0x13, short)
#define ECS_IOCTL_APP_SET_MVFLAG	_IOW(ST480IO, 0x14, short)
#define ECS_IOCTL_APP_GET_MVFLAG	_IOR(ST480IO, 0x15, short)

struct st480_data {
	struct i2c_client *client;
	struct input_dev *input_dev;
	struct platform_data_st480 *pdata;
	struct delayed_work work;
};

static struct st480_data *st480;

static atomic_t m_flag;
static atomic_t mv_flag;

static atomic_t open_count;
static atomic_t open_flag;
static atomic_t reserve_open_flag;

volatile static short st480_delay = ST480_DEFAULT_DELAY;

struct mag_3 {
	s16  mag_x,
	     mag_y,
	     mag_z;
};
volatile static struct mag_3 mag;

/*
 * i2c transfer
 * read/write
 */
static int st480_i2c_transfer_data(struct i2c_client *client, int len, char *buf, int length)
{
	struct i2c_msg msgs[] = {
		{
			.addr  =  client->addr,
			.flags  =  0,
			.len  =  len,
			.buf  =  buf,
		},
		{
			.addr  =  client->addr,
			.flags  = I2C_M_RD,
			.len  =  length,
			.buf  =  buf,
		},
	};

	if(i2c_transfer(client->adapter, msgs, 2) < 0) {
		pr_err("megnetic_i2c_read_data: transfer error\n");
		return EIO;
	} else
		return 0;
}

/*
 * Device detect and init
 *
 */
static int st480_setup(struct i2c_client *client)
{
	int ret;
	unsigned char buf[5];

	memset(buf, 0, 5);

	buf[0] = READ_REGISTER_CMD;
	buf[1] = 0x00;
	ret = 0;

#ifdef IC_CHECK
	while(st480_i2c_transfer_data(client, 2, buf, 3)!=0) {
		ret++;
		msleep(1);
		if(st480_i2c_transfer_data(client, 2, buf, 3)==0) {
			break;
		}
		if(ret > MAX_FAILURE_COUNT) {
			return -EIO;
		}
	}

	if(buf[2] != ST480_DEVICE_ID) {
		return -ENODEV;
	}
#endif

//init register step 1
	buf[0] = WRITE_REGISTER_CMD;
	buf[1] = ONE_INIT_DATA_HIGH;
	buf[2] = ONE_INIT_DATA_LOW;
	buf[3] = ONE_INIT_REG;
	ret = 0;
	while(st480_i2c_transfer_data(client, 4, buf, 1)!=0) {
		ret++;
		msleep(1);
		if(st480_i2c_transfer_data(client, 4, buf, 1)==0) {
			break;
		}
		if(ret > MAX_FAILURE_COUNT) {
			return -EIO;
		}
	}

//init register step 2
	buf[0] = WRITE_REGISTER_CMD;
	buf[1] = TWO_INIT_DATA_HIGH;
	buf[2] = TWO_INIT_DATA_LOW;
	buf[3] = TWO_INIT_REG;
	ret = 0;
	while(st480_i2c_transfer_data(client, 4, buf, 1)!=0) {
		ret++;
		msleep(1);
		if(st480_i2c_transfer_data(client, 4, buf, 1)==0) {
			break;
		}
		if(ret > MAX_FAILURE_COUNT) {
			return -EIO;
		}
	}

//set calibration register
	buf[0] = WRITE_REGISTER_CMD;
	buf[1] = CALIBRATION_DATA_HIGH;
	buf[2] = CALIBRATION_DATA_LOW;
	buf[3] = CALIBRATION_REG;
	ret = 0;
	while(st480_i2c_transfer_data(client, 4, buf, 1)!=0) {
		ret++;
		msleep(1);
		if(st480_i2c_transfer_data(client, 4, buf, 1)==0) {
			break;
		}
		if(ret > MAX_FAILURE_COUNT) {
			return -EIO;
		}
	}

//set mode config
	buf[0] = SINGLE_MEASUREMENT_MODE_CMD;
	ret=0;
	while(st480_i2c_transfer_data(client, 1, buf, 1)!=0) {
		ret++;
		msleep(1);
		if(st480_i2c_transfer_data(client, 1, buf, 1)==0) {
			break;
		}
		if(ret > MAX_FAILURE_COUNT) {
			return -EIO;
		}
	}

	return 0;
}

static void st480_work_func(void)
{
	char buffer[9];
	int ret;
	s16 hw_data[3];

	memset(buffer, 0, 9);
	memset(hw_data, 0, 3);

	buffer[0] = READ_MEASUREMENT_CMD;
	ret=0;
	while(st480_i2c_transfer_data(st480->client, 1, buffer, 9)!=0) {
		ret++;
		msleep(1);
		if(st480_i2c_transfer_data(st480->client, 1, buffer, 9)==0) {
			break;
		}
		if(ret > MAX_FAILURE_COUNT) {
			return;
		}
	}

	if(!((buffer[0]>>4) & 0X01)) {
		hw_data[0] = (buffer[3]<<8)|buffer[4];
		hw_data[1] = (buffer[5]<<8)|buffer[6];
		hw_data[2] = (buffer[7]<<8)|buffer[8];

		mag.mag_x = ((st480->pdata->negate_x) ? (-hw_data[st480->pdata->axis_map_x])
		             : (hw_data[st480->pdata->axis_map_x]));
		mag.mag_y = ((st480->pdata->negate_y) ? (-hw_data[st480->pdata->axis_map_y])
		             : (hw_data[st480->pdata->axis_map_y]));
		mag.mag_z = ((st480->pdata->negate_z) ? (-hw_data[st480->pdata->axis_map_z])
		             : (hw_data[st480->pdata->axis_map_z]));

		if( ((buffer[1]<<8)|(buffer[2])) > 46244) {
			mag.mag_x = mag.mag_x * (1 + (70/128/4096) * (((buffer[1]<<8)|(buffer[2])) - 46244));
			mag.mag_y = mag.mag_y * (1 + (70/128/4096) * (((buffer[1]<<8)|(buffer[2])) - 46244));
			mag.mag_z = mag.mag_z * (1 + (70/128/4096) * (((buffer[1]<<8)|(buffer[2])) - 46244));
		} else if( ((buffer[1]<<8)|(buffer[2])) < 46244) {
			mag.mag_x = mag.mag_x * (1 + (60/128/4096) * (((buffer[1]<<8)|(buffer[2])) - 46244));
			mag.mag_y = mag.mag_y * (1 + (60/128/4096) * (((buffer[1]<<8)|(buffer[2])) - 46244));
			mag.mag_z = mag.mag_z * (1 + (60/128/4096) * (((buffer[1]<<8)|(buffer[2])) - 46244));
		}

		SENODIADBG("st480 raw data: x = %d, y = %d, z = %d \n",mag.mag_x,mag.mag_y,mag.mag_z);
	}

	//set mode config
	buffer[0] = SINGLE_MEASUREMENT_MODE_CMD;
	ret=0;
	while(st480_i2c_transfer_data(st480->client, 1, buffer, 1)!=0) {
		ret++;
		msleep(1);
		if(st480_i2c_transfer_data(st480->client, 1, buffer, 1)==0) {
			break;
		}
		if(ret > MAX_FAILURE_COUNT) {
			return;
		}
	}
}

static void st480_input_func(struct work_struct *work)
{
	SENODIAFUNC("st480_input_func");
	st480_work_func();

	if (atomic_read(&m_flag) || atomic_read(&mv_flag)) {
		input_report_abs(st480->input_dev, ABS_HAT0X, mag.mag_x);
		input_report_abs(st480->input_dev, ABS_HAT0Y, mag.mag_y);
		input_report_abs(st480->input_dev, ABS_BRAKE, mag.mag_z);
	}

	input_sync(st480->input_dev);

	schedule_delayed_work(&st480->work,msecs_to_jiffies(st480_delay));
}

static void ecs_closedone(void)
{
	SENODIAFUNC("ecs_closedone");
	atomic_set(&m_flag, 0);
	atomic_set(&mv_flag, 0);
}

/***** st480 functions ***************************************/
static int st480_open(struct inode *inode, struct file *file)
{
	int ret = -1;

	SENODIAFUNC("st480_open");

	if (atomic_cmpxchg(&open_count, 0, 1) == 0) {
		if (atomic_cmpxchg(&open_flag, 0, 1) == 0) {
			atomic_set(&reserve_open_flag, 1);
			ret = 0;
		}
	}

	if(atomic_read(&reserve_open_flag)) {
		schedule_delayed_work(&st480->work,msecs_to_jiffies(st480_delay));
	}
	return ret;
}

static int st480_release(struct inode *inode, struct file *file)
{
	SENODIAFUNC("st480_release");

	atomic_set(&reserve_open_flag, 0);
	atomic_set(&open_flag, 0);
	atomic_set(&open_count, 0);

	ecs_closedone();

	cancel_delayed_work(&st480->work);
	return 0;
}

#if OLD_KERNEL_VERSION
static int
st480_ioctl(struct inode *inode, struct file *file,
            unsigned int cmd, unsigned long arg)
#else
static long
st480_ioctl(struct file *file, unsigned int cmd, unsigned long arg)
#endif
{
	void __user *argp = (void __user *)arg;
	short flag;

	SENODIADBG("enter %s\n", __func__);

	switch (cmd) {
	case ECS_IOCTL_APP_SET_MFLAG:
	case ECS_IOCTL_APP_SET_MVFLAG:
		if (copy_from_user(&flag, argp, sizeof(flag))) {
			return -EFAULT;
		}
		if (flag < 0 || flag > 1) {
			return -EINVAL;
		}
		break;
	case ECS_IOCTL_APP_SET_DELAY:
		if (copy_from_user(&flag, argp, sizeof(flag))) {
			return -EFAULT;
		}
		break;
	default:
		break;
	}

	switch (cmd) {
	case ECS_IOCTL_APP_SET_MFLAG:
		atomic_set(&m_flag, flag);
		SENODIADBG("MFLAG is set to %d", flag);
		break;
	case ECS_IOCTL_APP_GET_MFLAG:
		flag = atomic_read(&m_flag);
		SENODIADBG("Mflag = %d\n",flag);
		break;
	case ECS_IOCTL_APP_SET_MVFLAG:
		atomic_set(&mv_flag, flag);
		SENODIADBG("MVFLAG is set to %d", flag);
		break;
	case ECS_IOCTL_APP_GET_MVFLAG:
		flag = atomic_read(&mv_flag);
		SENODIADBG("MVflag = %d\n",flag);
		break;
	case ECS_IOCTL_APP_SET_DELAY:
		st480_delay = flag;
		break;
	case ECS_IOCTL_APP_GET_DELAY:
		flag = st480_delay;
		break;
	default:
		return -ENOTTY;
	}

	switch (cmd) {
	case ECS_IOCTL_APP_GET_MFLAG:
	case ECS_IOCTL_APP_GET_MVFLAG:
	case ECS_IOCTL_APP_GET_DELAY:
		if (copy_to_user(argp, &flag, sizeof(flag))) {
			return -EFAULT;
		}
		break;
	default:
		break;
	}

	return 0;
}


static struct file_operations st480_fops = {
	.owner = THIS_MODULE,
	.open = st480_open,
	.release = st480_release,
#if OLD_KERNEL_VERSION
	.ioctl = st480_ioctl,
#else
	.unlocked_ioctl = st480_ioctl,
#endif
};


static struct miscdevice st480_device = {
	.minor = MISC_DYNAMIC_MINOR,
	.name = "st480",
	.fops = &st480_fops,
};

/*********************************************/
#if ST480_AUTO_TEST
static int sensor_test_read(void)

{
	st480_work_func();
	return 0;
}

static int auto_test_read(void *unused)
{
	while(1) {
		sensor_test_read();
		msleep(200);
	}
	return 0;
}
#endif

int st480_probe(struct i2c_client *client, const struct i2c_device_id *id)
{
	int err = 0;

#if ST480_AUTO_TEST
	struct task_struct *thread;
#endif

	SENODIAFUNC("st480_probe");

	if (!i2c_check_functionality(client->adapter, I2C_FUNC_I2C)) {
		printk(KERN_ERR "SENODIA st480_probe: check_functionality failed.\n");
		err = -ENODEV;
		goto exit0;
	}

	/* Allocate memory for driver data */
	st480 = kzalloc(sizeof(struct st480_data), GFP_KERNEL);
	if (!st480) {
		printk(KERN_ERR "SENODIA st480_probe: memory allocation failed.\n");
		err = -ENOMEM;
		goto exit1;
	}

	st480->client = client;

	i2c_set_clientdata(client, st480);

	INIT_DELAYED_WORK(&st480->work, st480_input_func);

	st480->pdata = kmalloc(sizeof(*st480->pdata), GFP_KERNEL);
	if (st480->pdata == NULL) {
		err = -ENOMEM;
		dev_err(&client->dev,
		        "failed to allocate memory for st480 pdata: %d\n", err);
		goto exit2;
	}

	memcpy(st480->pdata, client->dev.platform_data, sizeof(*st480->pdata));

	if(st480_setup(st480->client) != 0) {
		printk("st480 setup error!\n");
		goto exit3;
	}

	/* Declare input device */
	st480->input_dev = input_allocate_device();
	if (!st480->input_dev) {
		err = -ENOMEM;
		printk(KERN_ERR
		       "SENODIA st480_probe: Failed to allocate input device\n");
		goto exit3;
	}

	/* Setup input device */
	set_bit(EV_ABS, st480->input_dev->evbit);

	/* x-axis of raw magnetic vector (-32768, 32767) */
	input_set_abs_params(st480->input_dev, ABS_HAT0X, ABSMIN_MAG, ABSMAX_MAG, 0, 0);
	/* y-axis of raw magnetic vector (-32768, 32767) */
	input_set_abs_params(st480->input_dev, ABS_HAT0Y, ABSMIN_MAG, ABSMAX_MAG, 0, 0);
	/* z-axis of raw magnetic vector (-32768, 32767) */
	input_set_abs_params(st480->input_dev, ABS_BRAKE, ABSMIN_MAG, ABSMAX_MAG, 0, 0);
	/* Set name */
	st480->input_dev->name = "mag_st480";

	/* Register */
	err = input_register_device(st480->input_dev);
	if (err) {
		printk(KERN_ERR
		       "SENODIA st480_probe: Unable to register input device\n");
		goto exit4;
	}

	err = misc_register(&st480_device);
	if (err) {
		printk(KERN_ERR
		       "SENODIA st480_probe: st480_device register failed\n");
		goto exit5;
	}

	/* As default, report all information */
	atomic_set(&m_flag, 1);
	atomic_set(&mv_flag, 1);

#if ST480_AUTO_TEST
	thread=kthread_run(auto_test_read,NULL,"st480_read_test");
#endif

	printk("st480 probe done.");
	return 0;

exit5:
	misc_deregister(&st480_device);
	input_unregister_device(st480->input_dev);
exit4:
	input_free_device(st480->input_dev);
exit3:
	kfree(st480->pdata);
exit2:
	kfree(st480);
exit1:
exit0:
	return err;

}

static int st480_remove(struct i2c_client *client)
{
	misc_deregister(&st480_device);
	input_unregister_device(st480->input_dev);
	input_free_device(st480->input_dev);
	cancel_delayed_work(&st480->work);
	kfree(st480->pdata);
	kfree(st480);
	return 0;
}

static const struct i2c_device_id st480_id[] = {
	{ST480_I2C_NAME, 0 },
	{ }
};

static struct i2c_driver st480_driver = {
	.probe		= st480_probe,
	.remove 	= st480_remove,
	.id_table	= st480_id,
	.driver = {
		.name = ST480_I2C_NAME,
	},
};

static int __init st480_init(void)
{
	return i2c_add_driver(&st480_driver);
}

static void __exit st480_exit(void)
{
	i2c_del_driver(&st480_driver);
}

module_init(st480_init);
module_exit(st480_exit);

MODULE_AUTHOR("Tori Xu <xuezhi_xu@senodia.com>");
MODULE_DESCRIPTION("senodia st480 linux driver");
MODULE_LICENSE("GPL");
MODULE_VERSION("2.0.0");
