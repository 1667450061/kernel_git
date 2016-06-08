#include "comipfb.h"
#include "comipfb_dev.h"
#include "mipi_cmd.h"
#include "mipi_interface.h"

static u8 backlight_cmds[][ROW_LINE] = {
        {0x00, GEN_CMD, SW_PACK2, 0x02, 0x51, 0xFF},
};

//[0]: delay after transfer; [1]:count of data; [2]: word count ls; [3]:word count ms; [4]...: data for transfering
static u8 lcd_cmds_init[][ROW_LINE] = {
	/****Start Initial Sequence ***/
	{0  ,GEN_CMD,SW_PACK2, 0x02,0x00,0x00},
	{0  ,GEN_CMD,LW_PACK,  6,4, 0,0xFF,0x80,0x09,0x01},
	{0  ,GEN_CMD,SW_PACK2, 0x02,0x00,0x80},
	{0  ,GEN_CMD,LW_PACK,   5,3, 0,0xFF,0x80,0x09},
	{0  ,GEN_CMD,SW_PACK2, 0x02,0x00,0x03},
	{0  ,GEN_CMD,SW_PACK2, 0x02,0xFF,0x01},
	{0  ,GEN_CMD,SW_PACK2, 0x02,0x00,0x00},
	{0  ,GEN_CMD,LW_PACK,   5,3,0,0xD8,0x87,0x87},
	{0  ,GEN_CMD,SW_PACK2, 0x02,0x00,0xB1},
	{0  ,GEN_CMD,SW_PACK2, 0x02,0xC5,0xA9},
	{0  ,GEN_CMD,SW_PACK2, 0x02,0x00,0x00},
	{0  ,GEN_CMD,SW_PACK2, 0x02,0xD9,0x20},
	{0  ,GEN_CMD,SW_PACK2, 0x02,0x00,0x90},
	{0  ,GEN_CMD,LW_PACK,   6,4, 0,0xC5,0x96,0xA7,0x01},
	{0  ,GEN_CMD,SW_PACK2, 0x02,0x00,0x81},
	{0  ,GEN_CMD,SW_PACK2, 0x02,0xC1,0x66},
	{0  ,GEN_CMD,SW_PACK2, 0x02,0x00,0xA1},
	{0  ,GEN_CMD,LW_PACK,   6,4, 0,0xC1,0x08,0x02,0x1B},
	{0  ,GEN_CMD,SW_PACK2, 0x02,0x00,0x81},
	{0  ,GEN_CMD,SW_PACK2, 0x02,0xC4,0x83},
	{0  ,GEN_CMD,SW_PACK2, 0x02,0x00,0x90},
	{0  ,GEN_CMD,SW_PACK2, 0x02,0xB3,0x02},
	{0  ,GEN_CMD,SW_PACK2, 0x02,0x00,0x92},
	{0  ,GEN_CMD,SW_PACK2, 0x02,0xB3,0x45},
	{0  ,GEN_CMD,SW_PACK2, 0x02,0x00,0xA7},
	{0  ,GEN_CMD,SW_PACK2, 0x02,0xB3,0x00},
	{0  ,GEN_CMD,SW_PACK2, 0x02,0x00,0xB4},
	{0  ,GEN_CMD,SW_PACK2, 0x02,0xC0,0x10},
	{0  ,GEN_CMD,SW_PACK2, 0x02,0x00,0x00},
	{0  ,GEN_CMD,SW_PACK2, 0x02,0x36,0x00},
	{0  ,GEN_CMD,SW_PACK2, 0x02,0x00,0x90},
	{0  ,GEN_CMD,LW_PACK,   9,7, 0,0xC0,0x00,0x44,0x00,0x00,0x00,0x03},
	{0  ,GEN_CMD,SW_PACK2, 0x02,0x00,0xA6},
	{0  ,GEN_CMD,LW_PACK,   6,4,0,0xC1,0x00,0x00,0x00},
	{0  ,GEN_CMD,SW_PACK2, 0x02,0x00,0x80},
	{0  ,GEN_CMD,LW_PACK,   9,7, 0,0xCE,0x87,0x03,0x00,0x86,0x03,0x00},
	{0  ,GEN_CMD,SW_PACK2, 0x02,0x00,0x90},
	{0  ,GEN_CMD,LW_PACK,   9,7, 0,0xCE,0x33,0x54,0x00,0x33,0x55,0x00},
	{0  ,GEN_CMD,SW_PACK2, 0x02,0x00,0xA0},
	{0  ,GEN_CMD,LW_PACK,   17,15, 0,0xCE,0x38,0x03,0x03,0x58,0x00,0x00,0x00,0x38,0x02,0x03,0x59,0x00,0x00,0x00},
	{0  ,GEN_CMD,SW_PACK2, 0x02,0x00,0xB0},
	{0  ,GEN_CMD,LW_PACK,   17,15, 0,0xCE,0x38,0x01,0x03,0x5A,0x00,0x00,0x00,0x38,0x00,0x03,0x5B,0x00,0x00,0x00},
	{0  ,GEN_CMD,SW_PACK2, 0x02,0x00,0xC0},
	{0  ,GEN_CMD,LW_PACK,   17,15, 0,0xCE,0x30,0x00,0x03,0x5C,0x00,0x00,0x00,0x30,0x01,0x03,0x5D,0x00,0x00,0x00},
	{0  ,GEN_CMD,SW_PACK2, 0x02,0x00,0xD0},
	{0  ,GEN_CMD,LW_PACK,   17,15, 0,0xCE,0x38,0x05,0x03,0x5E,0x00,0x00,0x00,0x38,0x04,0x03,0x5F,0x00,0x00,0x00},
	{0  ,GEN_CMD,SW_PACK2, 0x02,0x00,0xC0},
	{0  ,GEN_CMD,LW_PACK,   13,11, 0,0xCF,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x80,0x00,0x09},
	{0  ,GEN_CMD,SW_PACK2, 0x02,0x00,0xC0},
	{0  ,GEN_CMD,LW_PACK,   18,16, 0,0xCB,0x00,0x04,0x04,0x04,0x04,0x00,0x00,0x04,0x04,0x04,0x04,0x00,0x00,0x00,0x00},
	{0  ,GEN_CMD,SW_PACK2, 0x02,0x00,0xD0},
	{0  ,GEN_CMD,LW_PACK,   18,16, 0,0xCB,0x00,0x00,0x00,0x00,0x00,0x00,0x04,0x04,0x04,0x04,0x00,0x00,0x04,0x04,0x04},
	{0  ,GEN_CMD,SW_PACK2, 0x02,0x00,0xE0},
	{0  ,GEN_CMD,LW_PACK,   13,11, 0,0xCB,0x04,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
	{0  ,GEN_CMD,SW_PACK2, 0x02,0x00,0x80},
	{0  ,GEN_CMD,LW_PACK,   13,11, 0,0xCC,0x00,0x26,0x25,0x02,0x06,0x00,0x00,0x0A,0x0E,0x0C},
	{0  ,GEN_CMD,SW_PACK2, 0x02,0x00,0x90},
	{0  ,GEN_CMD,LW_PACK,   18,16, 0,0xCC,0x10,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x26,0x25,0x01,0x05},
	{0  ,GEN_CMD,SW_PACK2, 0x02,0x00,0xA0},
	{0  ,GEN_CMD,LW_PACK,   18,16, 0,0xCC,0x00,0x00,0x09,0x0D,0x0B,0x0F,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
	{0  ,GEN_CMD,SW_PACK2, 0x02,0x00,0xB0},
	{0  ,GEN_CMD,LW_PACK,   13,11, 0,0xCC,0x00,0x25,0x26,0x05,0x01,0x00,0x00,0x0D,0x09,0x0B},
	{0  ,GEN_CMD,SW_PACK2, 0x02,0x00,0xC0},
	{0  ,GEN_CMD,LW_PACK,   18,16, 0,0xCC,0x0F,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x25,0x26,0x06,0x02},
	{0  ,GEN_CMD,SW_PACK2, 0x02,0x00,0xD0},
	{0  ,GEN_CMD,LW_PACK,   18,16, 0,0xCC,0x00,0x00,0x0E,0x0A,0x0C,0x10,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
	{0  ,GEN_CMD,SW_PACK2, 0x02,0x00,0x00},
	{0  ,GEN_CMD,LW_PACK,   19,17, 0,0xE1,0x06,0x07,0x0A,0x0A,0x04,0x16,0x0F,0x0F,0x00,0x04,0x03,0x07,0x0E,0x21,0x1D,0x0B},
	{0  ,GEN_CMD,SW_PACK2, 0x02,0x00,0x00},
	{0  ,GEN_CMD,SW_PACK2, 0x02,0x35,0x00},
	{0  ,GEN_CMD,LW_PACK,   19,17, 0,0xE2,0x06,0x07,0x0A,0x0A,0x04,0x17,0x0F,0x0F,0x00,0x04,0x02,0x07,0x0F,0x22,0x1E,0x0B},
	{0  ,GEN_CMD,SW_PACK2, 0x02,0x00,0x00},
	{0  ,GEN_CMD,LW_PACK,   6,4,0,0xFF,0xFF,0xFF,0xFF},
	{120,GEN_CMD,SW_PACK2, 0x2,0x11, 0x00}, // sleep out
	{0  ,GEN_CMD,SW_PACK2, 0x2,0x29, 0x00}, // display on
	//{0  ,GEN_CMD,SW_PACK2, 0x2,0x2C, 0x00}, // display on
	//{  1), {0x2C}, // normal on
};

static u8 lcd_cmds_suspend[][ROW_LINE] = {
//	{50, GEN_CMD, SHUTDOWN_SW_PACK,  0x00, 0x00},
	{0x64, GEN_CMD, SW_PACK1, 0x01, 0x28},
	{0x00, GEN_CMD, SW_PACK1, 0x01, 0x10},
};

static u8 lcd_cmds_resume[][ROW_LINE] = {
	{0  ,GEN_CMD,SW_PACK2, 0x02,0x00,0x00},
	{0  ,GEN_CMD,LW_PACK,  6,4, 0,0xFF,0x80,0x09,0x01},
	{0  ,GEN_CMD,SW_PACK2, 0x02,0x00,0x80},
	{0  ,GEN_CMD,LW_PACK,   5,3, 0,0xFF,0x80,0x09},
	{0  ,GEN_CMD,SW_PACK2, 0x02,0x00,0x03},
	{0  ,GEN_CMD,SW_PACK2, 0x02,0xFF,0x01},
	{0  ,GEN_CMD,SW_PACK2, 0x02,0x00,0x00},
	{0  ,GEN_CMD,LW_PACK,   5,3,0,0xD8,0x87,0x87},
	{0  ,GEN_CMD,SW_PACK2, 0x02,0x00,0xB1},
	{0  ,GEN_CMD,SW_PACK2, 0x02,0xC5,0xA9},
	{0  ,GEN_CMD,SW_PACK2, 0x02,0x00,0x00},
	{0  ,GEN_CMD,SW_PACK2, 0x02,0xD9,0x20},
	{0  ,GEN_CMD,SW_PACK2, 0x02,0x00,0x90},
	{0  ,GEN_CMD,LW_PACK,   6,4, 0,0xC5,0x96,0xA7,0x01},
	{0  ,GEN_CMD,SW_PACK2, 0x02,0x00,0x81},
	{0  ,GEN_CMD,SW_PACK2, 0x02,0xC1,0x66},
	{0  ,GEN_CMD,SW_PACK2, 0x02,0x00,0xA1},
	{0  ,GEN_CMD,LW_PACK,   6,4, 0,0xC1,0x08,0x02,0x1B},
	{0  ,GEN_CMD,SW_PACK2, 0x02,0x00,0x81},
	{0  ,GEN_CMD,SW_PACK2, 0x02,0xC4,0x83},
	{0  ,GEN_CMD,SW_PACK2, 0x02,0x00,0x90},
	{0  ,GEN_CMD,SW_PACK2, 0x02,0xB3,0x02},
	{0  ,GEN_CMD,SW_PACK2, 0x02,0x00,0x92},
	{0  ,GEN_CMD,SW_PACK2, 0x02,0xB3,0x45},
	{0  ,GEN_CMD,SW_PACK2, 0x02,0x00,0xA7},
	{0  ,GEN_CMD,SW_PACK2, 0x02,0xB3,0x00},
	{0  ,GEN_CMD,SW_PACK2, 0x02,0x00,0xB4},
	{0  ,GEN_CMD,SW_PACK2, 0x02,0xC0,0x10},
	{0  ,GEN_CMD,SW_PACK2, 0x02,0x00,0x00},
	{0  ,GEN_CMD,SW_PACK2, 0x02,0x36,0x00},
	{0  ,GEN_CMD,SW_PACK2, 0x02,0x00,0x90},
	{0  ,GEN_CMD,LW_PACK,   9,7, 0,0xC0,0x00,0x44,0x00,0x00,0x00,0x03},
	{0  ,GEN_CMD,SW_PACK2, 0x02,0x00,0xA6},
	{0  ,GEN_CMD,LW_PACK,   6,4,0,0xC1,0x00,0x00,0x00},
	{0  ,GEN_CMD,SW_PACK2, 0x02,0x00,0x80},
	{0  ,GEN_CMD,LW_PACK,   9,7, 0,0xCE,0x87,0x03,0x00,0x86,0x03,0x00},
	{0  ,GEN_CMD,SW_PACK2, 0x02,0x00,0x90},
	{0  ,GEN_CMD,LW_PACK,   9,7, 0,0xCE,0x33,0x54,0x00,0x33,0x55,0x00},
	{0  ,GEN_CMD,SW_PACK2, 0x02,0x00,0xA0},
	{0  ,GEN_CMD,LW_PACK,   17,15, 0,0xCE,0x38,0x03,0x03,0x58,0x00,0x00,0x00,0x38,0x02,0x03,0x59,0x00,0x00,0x00},
	{0  ,GEN_CMD,SW_PACK2, 0x02,0x00,0xB0},
	{0  ,GEN_CMD,LW_PACK,   17,15, 0,0xCE,0x38,0x01,0x03,0x5A,0x00,0x00,0x00,0x38,0x00,0x03,0x5B,0x00,0x00,0x00},
	{0  ,GEN_CMD,SW_PACK2, 0x02,0x00,0xC0},
	{0  ,GEN_CMD,LW_PACK,   17,15, 0,0xCE,0x30,0x00,0x03,0x5C,0x00,0x00,0x00,0x30,0x01,0x03,0x5D,0x00,0x00,0x00},
	{0  ,GEN_CMD,SW_PACK2, 0x02,0x00,0xD0},
	{0  ,GEN_CMD,LW_PACK,   17,15, 0,0xCE,0x38,0x05,0x03,0x5E,0x00,0x00,0x00,0x38,0x04,0x03,0x5F,0x00,0x00,0x00},
	{0  ,GEN_CMD,SW_PACK2, 0x02,0x00,0xC0},
	{0  ,GEN_CMD,LW_PACK,   13,11, 0,0xCF,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x80,0x00,0x09},
	{0  ,GEN_CMD,SW_PACK2, 0x02,0x00,0xC0},
	{0  ,GEN_CMD,LW_PACK,   18,16, 0,0xCB,0x00,0x04,0x04,0x04,0x04,0x00,0x00,0x04,0x04,0x04,0x04,0x00,0x00,0x00,0x00},
	{0  ,GEN_CMD,SW_PACK2, 0x02,0x00,0xD0},
	{0  ,GEN_CMD,LW_PACK,   18,16, 0,0xCB,0x00,0x00,0x00,0x00,0x00,0x00,0x04,0x04,0x04,0x04,0x00,0x00,0x04,0x04,0x04},
	{0  ,GEN_CMD,SW_PACK2, 0x02,0x00,0xE0},
	{0  ,GEN_CMD,LW_PACK,   13,11, 0,0xCB,0x04,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
	{0  ,GEN_CMD,SW_PACK2, 0x02,0x00,0x80},
	{0  ,GEN_CMD,LW_PACK,   13,11, 0,0xCC,0x00,0x26,0x25,0x02,0x06,0x00,0x00,0x0A,0x0E,0x0C},
	{0  ,GEN_CMD,SW_PACK2, 0x02,0x00,0x90},
	{0  ,GEN_CMD,LW_PACK,   18,16, 0,0xCC,0x10,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x26,0x25,0x01,0x05},
	{0  ,GEN_CMD,SW_PACK2, 0x02,0x00,0xA0},
	{0  ,GEN_CMD,LW_PACK,   18,16, 0,0xCC,0x00,0x00,0x09,0x0D,0x0B,0x0F,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
	{0  ,GEN_CMD,SW_PACK2, 0x02,0x00,0xB0},
	{0  ,GEN_CMD,LW_PACK,   13,11, 0,0xCC,0x00,0x25,0x26,0x05,0x01,0x00,0x00,0x0D,0x09,0x0B},
	{0  ,GEN_CMD,SW_PACK2, 0x02,0x00,0xC0},
	{0  ,GEN_CMD,LW_PACK,   18,16, 0,0xCC,0x0F,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x25,0x26,0x06,0x02},
	{0  ,GEN_CMD,SW_PACK2, 0x02,0x00,0xD0},
	{0  ,GEN_CMD,LW_PACK,   18,16, 0,0xCC,0x00,0x00,0x0E,0x0A,0x0C,0x10,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
	{0  ,GEN_CMD,SW_PACK2, 0x02,0x00,0x00},
	{0  ,GEN_CMD,LW_PACK,   19,17, 0,0xE1,0x06,0x07,0x0A,0x0A,0x04,0x16,0x0F,0x0F,0x00,0x04,0x03,0x07,0x0E,0x21,0x1D,0x0B},
	{0  ,GEN_CMD,SW_PACK2, 0x02,0x00,0x00},
	{0  ,GEN_CMD,SW_PACK2, 0x02,0x35,0x00},
	{0  ,GEN_CMD,LW_PACK,   19,17, 0,0xE2,0x06,0x07,0x0A,0x0A,0x04,0x17,0x0F,0x0F,0x00,0x04,0x02,0x07,0x0F,0x22,0x1E,0x0B},
	{0  ,GEN_CMD,SW_PACK2, 0x02,0x00,0x00},
	{0  ,GEN_CMD,LW_PACK,   6,4,0,0xFF,0xFF,0xFF,0xFF},
	{120,GEN_CMD,SW_PACK2, 0x2,0x11, 0x00}, // sleep out
	{0  ,GEN_CMD,SW_PACK2, 0x2,0x29, 0x00}, // display on
};

static int lcd_by_otm8018b_reset(struct comipfb_info *fbi)
{
	int gpio_rst = fbi->pdata->gpio_rst;

	if (gpio_rst >= 0) {
		gpio_request(gpio_rst, "LCD Reset");
		gpio_direction_output(gpio_rst, 1);
		mdelay(10);
		gpio_direction_output(gpio_rst, 0);
		mdelay(10);
		gpio_direction_output(gpio_rst, 1);
		mdelay(200);
		gpio_free(gpio_rst);
	}
	return 0;
}

static int lcd_by_otm8018b_suspend(struct comipfb_info *fbi)
{
	int ret=0;
	struct comipfb_dev_timing_mipi *mipi;

	mipi = &(fbi->cdev->timing.mipi);

	if (mipi->display_mode == MIPI_VIDEO_MODE) {
		mipi_dsih_hal_mode_config(fbi, 1);
	}else
		mipi_dsih_hal_dcs_wr_tx_type(fbi, 3, 1);
	
	if (!(fbi->pdata->flags & COMIPFB_SLEEP_POWEROFF))
		ret = comipfb_if_mipi_dev_cmds(fbi, &fbi->cdev->cmds_suspend);
	msleep(20);
	mipi_dsih_dphy_enable_hs_clk(fbi, 0);
	if(fbi->cdev->reset)
		fbi->cdev->reset(fbi);

	mipi_dsih_dphy_ulps_en(fbi, 1);
	mipi_dsih_dphy_reset(fbi, 0);
	mipi_dsih_dphy_shutdown(fbi, 0);

	return ret;
}

static int lcd_by_otm8018b_resume(struct comipfb_info *fbi)
{
	int ret=0;
	struct comipfb_dev_timing_mipi *mipi;

	mipi = &(fbi->cdev->timing.mipi);

	mipi_dsih_dphy_shutdown(fbi, 1);
	mipi_dsih_dphy_reset(fbi, 1);
	mipi_dsih_dphy_ulps_en(fbi, 0);

	if (fbi->pdata->flags & COMIPFB_SLEEP_POWEROFF) {
		/* Reset device. */
		if (fbi->cdev->reset)
			fbi->cdev->reset(fbi);
		ret = comipfb_if_mipi_dev_cmds(fbi, &fbi->cdev->cmds_init);
	}
  
	if (fbi->cdev->reset)
		fbi->cdev->reset(fbi);

#ifdef CONFIG_FBCON_DRAW_PANIC_TEXT
	if (unlikely(kpanic_in_progress == 1)) {
		ret = comipfb_if_mipi_dev_cmds(fbi, &fbi->cdev->cmds_init);
	}
	else
		ret = comipfb_if_mipi_dev_cmds(fbi, &fbi->cdev->cmds_resume);
#else
	ret = comipfb_if_mipi_dev_cmds(fbi, &fbi->cdev->cmds_resume);
#endif
	msleep(20);
	if (mipi->display_mode == MIPI_VIDEO_MODE) {
		mipi_dsih_hal_mode_config(fbi, 0);
	}else
		mipi_dsih_hal_dcs_wr_tx_type(fbi, 3, 0);

	mipi_dsih_dphy_enable_hs_clk(fbi, 1);

	msleep(50);

	return ret;
}

//the REG c181 must set to 0x77 ,max fps is 70HZ
/* 2012-12-19 pclk 31.2M 4-26-24-1-20-21----534*896  65.2fps */
struct comipfb_dev lcd_by_otm8018b_dev = {
	.name = "lcd_by_otm8018b",
	.interface_info = COMIPFB_MIPI_IF,
	.lcd_id = 0,
	.refresh_en = 1,
	.bpp = 32,
	.xres = 480,
	.yres = 854,
	.flags = 0,
	.pclk = 28000000,//31000000
	.timing = {
		.mipi = {
			.hs_freq = 52500,		//Kbyte
			.lp_freq = 10000,		//KHZ
			.no_lanes = 2,
			.display_mode = MIPI_VIDEO_MODE,
			.im_pin_val = 1,
			.color_mode = {
				.color_bits = COLOR_CODE_24BIT,
			},
			.videomode_info = {
				.hsync = 4,
				.hbp = 36,
				.hfp = 34,
				.vsync = 2,
				.vbp = 20,
				.vfp = 21,
				.sync_pol = COMIPFB_VSYNC_HIGH_ACT,
				.lp_cmd_en = 1,
				.lp_hfp_en = 1,
				.lp_hbp_en = 1,
				.lp_vact_en = 1,
				.lp_vfp_en = 1,
				.lp_vbp_en = 1,
				.lp_vsa_en = 1,
				.mipi_trans_type = VIDEO_BURST_WITH_SYNC_PULSES,
			},
			.commandmode_info = {
				.tear_fx_en = 1,
				.ack_rqst_en = 0,
				.gen_sw_0p_tx = 1,
				.gen_sw_1p_tx = 1,
				.gen_sw_2p_tx = 1,
				.gen_sr_0p_tx = 1,
				.gen_sr_1p_tx = 1,
				.gen_sr_2p_tx = 1,
				.gen_lw_tx = 1,
				.dcs_sw_0p_tx = 1,
				.dcs_sw_1p_tx = 1,
				.dcs_sr_0p_tx = 1,
				.dcs_lw_tx = 1,
				.max_rd_pkt_size = 1,
				.timeout = {
					.hs_rd_to_cnt = 0,
					.lp_rd_to_cnt = 0,
					.hs_wr_to_cnt = 20,
					.lp_wr_to_cnt = 20,
					.bta_to_cnt = 100,
				},
			},
			.phytime_info = {
				.clk_tprepare = 3, //HSBYTECLK
			},
			.teinfo = {
				.te_source = 1, //external signal
				.te_trigger_mode = 0,
				.te_en = 0,
				.te_sync_en = 1,
			},
			.ext_info = {
				.eotp_tx_en = 0,
			},
		},
	},
	.cmds_init = {ARRAY_AND_SIZE(lcd_cmds_init)},
	.cmds_suspend = {ARRAY_AND_SIZE(lcd_cmds_suspend)},
	.cmds_resume = {ARRAY_AND_SIZE(lcd_cmds_resume)},
	.reset = lcd_by_otm8018b_reset,
	.suspend = lcd_by_otm8018b_suspend,
	.resume = lcd_by_otm8018b_resume,
	.backlight_info = {{ARRAY_AND_SIZE(backlight_cmds)},
				.brightness_bit = 5,
				},
};

static int __init lcd_by_otm8018b_init(void)
{
	return comipfb_dev_register(&lcd_by_otm8018b_dev);
}

subsys_initcall(lcd_by_otm8018b_init);