#include "comipfb.h"
#include "comipfb_dev.h"
#include "mipi_cmd.h"
#include "mipi_interface.h"

static u8 backlight_cmds[][ROW_LINE] = {
	{0x00, DCS_CMD, LW_PACK, 0x08, 0x06, 0x00, 0xFF, 0xFF, 0x98, 0x06, 0x04, 0x00},
        {0x00, DCS_CMD, SW_PACK2, 0x02, 0x51, 0xBE},
};

/****Start Initial Sequence ***/
static u8 lcd_cmds_init[][ROW_LINE] = {
	//=======================================================
	{0x00, DCS_CMD, LW_PACK, 0x08, 0x06, 0x00, 0xFF, 0xFF, 0x98, 0x06, 0x04, 0x01},
	//Output SDA
	{0x00, DCS_CMD, SW_PACK2, 0x02, 0x08, 0x10},
	//DE = 1 Active
	{0x00, DCS_CMD, SW_PACK2, 0x02, 0x21, 0x01},
	//Resolution setting 480 X 800
	{0x00, DCS_CMD, SW_PACK2, 0x02, 0x30, 0x02},
	//Inversion setting for 2-dot
	{0x00, DCS_CMD, SW_PACK2, 0x02, 0x31, 0x02},

	{0x00, DCS_CMD, SW_PACK2, 0x02, 0x40, 0x15},
	{0x00, DCS_CMD, SW_PACK2, 0x02, 0x41, 0x33},
	{0x00, DCS_CMD, SW_PACK2, 0x02, 0x42, 0x03},
	{0x00, DCS_CMD, SW_PACK2, 0x02, 0x43, 0x02},
	{0x00, DCS_CMD, SW_PACK2, 0x02, 0x44, 0x02},

	{0x00, DCS_CMD, SW_PACK2, 0x02, 0x50, 0x80},
	{0x00, DCS_CMD, SW_PACK2, 0x02, 0x51, 0x80},
	//Flicker MSB
	{0x00, DCS_CMD, SW_PACK2, 0x02, 0x52, 0x00},
	//Flicker LSB
	{0x00, DCS_CMD, SW_PACK2, 0x02, 0x53, 0x76},
	//Low voltage detection
	{0x00, DCS_CMD, SW_PACK2, 0x02, 0x57, 0x50},

	{0x00, DCS_CMD, SW_PACK2, 0x02, 0x60, 0x07},
	{0x00, DCS_CMD, SW_PACK2, 0x02, 0x61, 0x00},
	{0x00, DCS_CMD, SW_PACK2, 0x02, 0x62, 0x08},
	{0x00, DCS_CMD, SW_PACK2, 0x02, 0x63, 0x00},

	//Positive Gamma
	{0x00, DCS_CMD, SW_PACK2, 0x02, 0xa0, 0x00},
	{0x00, DCS_CMD, SW_PACK2, 0x02, 0xa1, 0x03},
	{0x00, DCS_CMD, SW_PACK2, 0x02, 0xa2, 0x21},
	{0x00, DCS_CMD, SW_PACK2, 0x02, 0xa3, 0x05},
	{0x00, DCS_CMD, SW_PACK2, 0x02, 0xa4, 0x00},
	{0x00, DCS_CMD, SW_PACK2, 0x02, 0xa5, 0x0d},
	{0x00, DCS_CMD, SW_PACK2, 0x02, 0xa6, 0x0a},
	{0x00, DCS_CMD, SW_PACK2, 0x02, 0xa7, 0x0a},
	{0x00, DCS_CMD, SW_PACK2, 0x02, 0xa8, 0x00},
	{0x00, DCS_CMD, SW_PACK2, 0x02, 0xa9, 0x02},
	{0x00, DCS_CMD, SW_PACK2, 0x02, 0xaa, 0x06},
	{0x00, DCS_CMD, SW_PACK2, 0x02, 0xab, 0x06},
	{0x00, DCS_CMD, SW_PACK2, 0x02, 0xac, 0x0b},
	{0x00, DCS_CMD, SW_PACK2, 0x02, 0xad, 0x27},
	{0x00, DCS_CMD, SW_PACK2, 0x02, 0xae, 0x25},
	{0x00, DCS_CMD, SW_PACK2, 0x02, 0xaf, 0x00},

	//Negative Gamma
	{0x00, DCS_CMD, SW_PACK2, 0x02, 0xc0, 0x00},
	{0x00, DCS_CMD, SW_PACK2, 0x02, 0xc1, 0x00},
	{0x00, DCS_CMD, SW_PACK2, 0x02, 0xC2, 0x08},
	{0x00, DCS_CMD, SW_PACK2, 0x02, 0xc3, 0x01},
	{0x00, DCS_CMD, SW_PACK2, 0x02, 0xc4, 0x03},
	{0x00, DCS_CMD, SW_PACK2, 0x02, 0xc5, 0x18},
	{0x00, DCS_CMD, SW_PACK2, 0x02, 0xc6, 0x0b},
	{0x00, DCS_CMD, SW_PACK2, 0x02, 0xc7, 0x08},
	{0x00, DCS_CMD, SW_PACK2, 0x02, 0xc8, 0x06},
	{0x00, DCS_CMD, SW_PACK2, 0x02, 0xc9, 0x0d},
	{0x00, DCS_CMD, SW_PACK2, 0x02, 0xca, 0x07},
	{0x00, DCS_CMD, SW_PACK2, 0x02, 0xcb, 0x05},
	{0x00, DCS_CMD, SW_PACK2, 0x02, 0xcc, 0x0d},
	{0x00, DCS_CMD, SW_PACK2, 0x02, 0xcd, 0x31},
	{0x00, DCS_CMD, SW_PACK2, 0x02, 0xce, 0x2b},
	{0x00, DCS_CMD, SW_PACK2, 0x02, 0xcf, 0x00},
	{0x00, DCS_CMD, SW_PACK2, 0x02, 0xce, 0x2b},
	{0x00, DCS_CMD, SW_PACK2, 0x02, 0xcf, 0x00},

	//Change to Page 6 CMD for GIP timing
	{0x00, DCS_CMD, LW_PACK, 0x08, 0x06, 0x00, 0xff, 0xff, 0x98, 0x06, 0x04, 0x06},
	{0x00, DCS_CMD, SW_PACK2, 0x02, 0x00, 0x21},
	{0x00, DCS_CMD, SW_PACK2, 0x02, 0x01, 0x06},
	{0x00, DCS_CMD, SW_PACK2, 0x02, 0x02, 0x00},
	{0x00, DCS_CMD, SW_PACK2, 0x02, 0x03, 0x00},
	{0x00, DCS_CMD, SW_PACK2, 0x02, 0x04, 0x01},
	{0x00, DCS_CMD, SW_PACK2, 0x02, 0x05, 0x01},
	{0x00, DCS_CMD, SW_PACK2, 0x02, 0x06, 0x80},
	{0x00, DCS_CMD, SW_PACK2, 0x02, 0x07, 0x02},
	{0x00, DCS_CMD, SW_PACK2, 0x02, 0x08, 0x05},
	{0x00, DCS_CMD, SW_PACK2, 0x02, 0x09, 0x00},
	{0x00, DCS_CMD, SW_PACK2, 0x02, 0x0a, 0x00},
	{0x00, DCS_CMD, SW_PACK2, 0x02, 0x0b, 0x00},
	{0x00, DCS_CMD, SW_PACK2, 0x02, 0x0c, 0x01},
	{0x00, DCS_CMD, SW_PACK2, 0x02, 0x0d, 0x01},
	{0x00, DCS_CMD, SW_PACK2, 0x02, 0x0e, 0x00},
	{0x00, DCS_CMD, SW_PACK2, 0x02, 0x0f, 0x00},
	{0x00, DCS_CMD, SW_PACK2, 0x02, 0x10, 0xf0},
	{0x00, DCS_CMD, SW_PACK2, 0x02, 0x11, 0xf4},
	{0x00, DCS_CMD, SW_PACK2, 0x02, 0x12, 0x00},
	{0x00, DCS_CMD, SW_PACK2, 0x02, 0x13, 0x00},
	{0x00, DCS_CMD, SW_PACK2, 0x02, 0x14, 0x00},
	{0x00, DCS_CMD, SW_PACK2, 0x02, 0x15, 0xc0},
	{0x00, DCS_CMD, SW_PACK2, 0x02, 0x16, 0x08},
	{0x00, DCS_CMD, SW_PACK2, 0x02, 0x17, 0x00},
	{0x00, DCS_CMD, SW_PACK2, 0x02, 0x18, 0x00},
	{0x00, DCS_CMD, SW_PACK2, 0x02, 0x19, 0x00},
	{0x00, DCS_CMD, SW_PACK2, 0x02, 0x1a, 0x00},
	{0x00, DCS_CMD, SW_PACK2, 0x02, 0x1b, 0x00},
	{0x00, DCS_CMD, SW_PACK2, 0x02, 0x1c, 0x00},
	{0x00, DCS_CMD, SW_PACK2, 0x02, 0x1d, 0x00},

	{0x00, DCS_CMD, SW_PACK2, 0x02, 0x20, 0x02},
	{0x00, DCS_CMD, SW_PACK2, 0x02, 0x21, 0x13},
	{0x00, DCS_CMD, SW_PACK2, 0x02, 0x22, 0x45},
	{0x00, DCS_CMD, SW_PACK2, 0x02, 0x23, 0x67},
	{0x00, DCS_CMD, SW_PACK2, 0x02, 0x24, 0x01},
	{0x00, DCS_CMD, SW_PACK2, 0x02, 0x25, 0x23},
	{0x00, DCS_CMD, SW_PACK2, 0x02, 0x26, 0x45},
	{0x00, DCS_CMD, SW_PACK2, 0x02, 0x27, 0x67},

	{0x00, DCS_CMD, SW_PACK2, 0x02, 0x30, 0x13},
	{0x00, DCS_CMD, SW_PACK2, 0x02, 0x31, 0x22},
	{0x00, DCS_CMD, SW_PACK2, 0x02, 0x32, 0x22},
	{0x00, DCS_CMD, SW_PACK2, 0x02, 0x33, 0x22},
	{0x00, DCS_CMD, SW_PACK2, 0x02, 0x34, 0x22},
	{0x00, DCS_CMD, SW_PACK2, 0x02, 0x35, 0xbb},
	{0x00, DCS_CMD, SW_PACK2, 0x02, 0x36, 0xaa},
	{0x00, DCS_CMD, SW_PACK2, 0x02, 0x37, 0xdd},
	{0x00, DCS_CMD, SW_PACK2, 0x02, 0x38, 0xcc},
	{0x00, DCS_CMD, SW_PACK2, 0x02, 0x39, 0x66},
	{0x00, DCS_CMD, SW_PACK2, 0x02, 0x3a, 0x77},
	{0x00, DCS_CMD, SW_PACK2, 0x02, 0x3b, 0x22},
	{0x00, DCS_CMD, SW_PACK2, 0x02, 0x3c, 0x22},
	{0x00, DCS_CMD, SW_PACK2, 0x02, 0x3d, 0x22},
	{0x00, DCS_CMD, SW_PACK2, 0x02, 0x3e, 0x22},
	{0x00, DCS_CMD, SW_PACK2, 0x02, 0x3f, 0x22},

	{0x00, DCS_CMD, SW_PACK2, 0x02, 0x40, 0x22},
	{0x00, DCS_CMD, SW_PACK2, 0x02, 0x52, 0x10},
	{0x00, DCS_CMD, SW_PACK2, 0x02, 0x53, 0x10},

	//Change to Page 7 CMD for user command
	{0x00, DCS_CMD, LW_PACK, 0x08, 0x06, 0x00, 0xff, 0xff, 0x98, 0x06, 0x04, 0x07},
	{0x00, DCS_CMD, SW_PACK2, 0x02, 0x17, 0x22},
	{0x00, DCS_CMD, SW_PACK2, 0x02, 0x02, 0x77},

	// Change to Page 0 CMD for Normal command
	{0x00, DCS_CMD, LW_PACK, 0x08, 0x06, 0x00, 0xff, 0xff, 0x98, 0x06, 0x04, 0x00},
	//open te
	{0x00, DCS_CMD, SW_PACK2, 0x02, 0x35, 0x00},

	//Exit Sleep
	{0x78, DCS_CMD, SW_PACK1, 0x01, 0x11},
	//Display on
	{0x0a, DCS_CMD, SW_PACK1, 0x01, 0x29},
	{0x00, DCS_CMD, LW_PACK, 0x08, 0x06, 0x00, 0xFF, 0xFF, 0x98, 0x06, 0x04, 0x08},
};

static u8 lcd_cmds_suspend[][ROW_LINE] = {
	{0x00, DCS_CMD, LW_PACK, 0x08, 0x06, 0x00, 0xff, 0xff, 0x98, 0x06, 0x04, 0x00},
	{0x0a, DCS_CMD, SW_PACK1, 0x01, 0x28},
	{0x78, DCS_CMD, SW_PACK1, 0x01, 0x10},	//TODO delay is 120ms.
};

static u8 lcd_cmds_resume[][ROW_LINE] = {
	{0x00, DCS_CMD, LW_PACK, 0x08, 0x06, 0x00, 0xff, 0xff, 0x98, 0x06, 0x04, 0x00},
	{0x78, DCS_CMD, SW_PACK1, 0x01, 0x11},
	{0x0a, DCS_CMD, SW_PACK1, 0x01, 0x29},
};
static struct common_id_info lcd_common_esd_info[] = {
	{DCS_CMD, {0x9C}, 1, 0x0A},
};

static int lcd_djn_ili9806e_reset(struct comipfb_info *fbi)
{
	int gpio_rst = fbi->pdata->gpio_rst;

	if (gpio_rst >= 0) {
		gpio_request(gpio_rst, "LCD Reset");
		gpio_direction_output(gpio_rst, 1);
		mdelay(1);
		gpio_direction_output(gpio_rst, 0);
		mdelay(10);
		gpio_direction_output(gpio_rst, 1);
		mdelay(120);
		gpio_free(gpio_rst);
	}
	return 0;
}

static int lcd_djn_ili9806e_suspend(struct comipfb_info *fbi)
{
	int ret=0;
	struct comipfb_dev_timing_mipi *mipi;
	int gpio_rst = fbi->pdata->gpio_rst;

	mipi = &(fbi->cdev->timing.mipi);

	if (mipi->display_mode == MIPI_VIDEO_MODE) {
		mipi_dsih_hal_mode_config(fbi, 1);
	}
	//if (!(fbi->pdata->flags & COMIPFB_SLEEP_POWEROFF))
		ret = comipfb_if_mipi_dev_cmds(fbi, &fbi->cdev->cmds_suspend);
	msleep(20);
	mipi_dsih_dphy_enable_hs_clk(fbi, 0);

	if (gpio_rst >= 0) {
		gpio_request(gpio_rst, "LCD Reset");
		gpio_direction_output(gpio_rst, 1);
		mdelay(10);
		gpio_direction_output(gpio_rst, 0);
		mdelay(50);
	}

	mipi_dsih_dphy_ulps_en(fbi, 1);
	mipi_dsih_dphy_reset(fbi, 0);
	mipi_dsih_dphy_shutdown(fbi, 0);

	return ret;
}

static int lcd_djn_ili9806e_resume(struct comipfb_info *fbi)
{
	int ret=0;
	struct comipfb_dev_timing_mipi *mipi;

	mipi = &(fbi->cdev->timing.mipi);

	mipi_dsih_dphy_shutdown(fbi, 1);
	mipi_dsih_dphy_reset(fbi, 1);
	mdelay(2);
	mipi_dsih_dphy_ulps_en(fbi, 0);

	if (fbi->cdev->reset)
		fbi->cdev->reset(fbi);
#if 0
#ifdef CONFIG_FBCON_DRAW_PANIC_TEXT
	if (unlikely(kpanic_in_progress == 1)) {
		ret = comipfb_if_mipi_dev_cmds(fbi, &fbi->cdev->cmds_init);
	}
	else
		ret = comipfb_if_mipi_dev_cmds(fbi, &fbi->cdev->cmds_resume);
#else
	ret = comipfb_if_mipi_dev_cmds(fbi, &fbi->cdev->cmds_resume);
#endif
#endif

	if (!(fbi->pdata->flags & COMIPFB_SLEEP_POWEROFF))
		ret = comipfb_if_mipi_dev_cmds(fbi, &fbi->cdev->cmds_resume);
	else
		ret = comipfb_if_mipi_dev_cmds(fbi, &fbi->cdev->cmds_init);

	msleep(20);
	if (mipi->display_mode == MIPI_VIDEO_MODE) {
		mipi_dsih_hal_mode_config(fbi, 0);
	}
	mipi_dsih_dphy_enable_hs_clk(fbi, 1);

	return ret;
}


struct comipfb_dev lcd_djn_ili9806e_dev = {
	.name = "lcd_djn_ili9806e",
	.interface_info = COMIPFB_MIPI_IF,
	.lcd_id = LCD_ID_DJN_ILI9806E,
	.refresh_en = 1,
	.bpp = 32,
	.xres = 480,
	.yres = 800,
	.flags = 0,
	.pclk = 24000000,
	.timing = {
		.mipi = {
			.hs_freq = 39000,	//Kbyte
			.lp_freq = 13000,	//KHZ
			.no_lanes = 2,
			.display_mode = MIPI_VIDEO_MODE,
			.im_pin_val = 1,
			.color_mode = {
				.color_bits = COLOR_CODE_24BIT,
			},
			.videomode_info = {
				.hsync = 6,
				.hbp = 15,
				.hfp = 12,
				.vsync = 4,
				.vbp = 7,
				.vfp = 8,
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
			.phytime_info = {
				.clk_tprepare = 3, //HSBYTECLK
			},
			.teinfo = {
				.te_source = 1, //external signal
				.te_trigger_mode = 0,
				.te_en = 1,
				.te_sync_en = 0,
			},
			.ext_info = {
				.eotp_tx_en = 1,
			},
		},
	},
	.cmds_init = {ARRAY_AND_SIZE(lcd_cmds_init)},
	.cmds_suspend = {ARRAY_AND_SIZE(lcd_cmds_suspend)},
	.cmds_resume = {ARRAY_AND_SIZE(lcd_cmds_resume)},
#ifdef CONFIG_FB_COMIP_ESD
	.esd_id_info = {
		.id_info = lcd_common_esd_info,
		.num_id_info = 1,
	},
#endif
	.reset = lcd_djn_ili9806e_reset,
	.suspend = lcd_djn_ili9806e_suspend,
	.resume = lcd_djn_ili9806e_resume,
	.backlight_info = {{ARRAY_AND_SIZE(backlight_cmds)},
				.brightness_bit = 5 + ROW_LINE,
	},
};

static int __init lcd_djn_ili9806e_init(void)
{
	return comipfb_dev_register(&lcd_djn_ili9806e_dev);
}

subsys_initcall(lcd_djn_ili9806e_init);
