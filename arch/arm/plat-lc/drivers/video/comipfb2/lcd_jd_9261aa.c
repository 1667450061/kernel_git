#include "comipfb.h"
#include "comipfb_dev.h"
#include "mipi_cmd.h"
#include "mipi_interface.h"

static u8 backlight_cmds[][ROW_LINE] = {
//      {0x00, GEN_CMD, SW_PACK2, 0x02, 0xB0, 0x04},
	{0x00, GEN_CMD, LW_PACK, 0x07, 0x05, 0x00, 0xBB, 0x7B, 0xFF, 0x0F, 0x02, 0x01, 0x00},
};

//[0]: delay after transfer; [1]:count of data; [2]: word count ls; [3]:word count ms; [4]...: data for transfering
static u8 lcd_cmds_init[][ROW_LINE] = {
	/****Start Initial Sequence ***/
	{0x01, DCS_CMD, LW_PACK, 0x06, 0x04, 0x00, 0xBF, 0x92, 0x61, 0xF3},
	{0x01, DCS_CMD, LW_PACK, 0x05, 0x03, 0x00, 0xB3, 0x00, 0x65},
	{0x01, DCS_CMD, LW_PACK, 0x05, 0x03, 0x00, 0xB4, 0x00, 0x39},
	{0x00, DCS_CMD, LW_PACK, 0x09, 0x07, 0x00, 0xB8, 0x00, 0xF0, 0x01, 0x00, 0xF0, 0x01},
	{0x01, DCS_CMD, SW_PACK2, 0x02, 0xC3, 0x04, },
	{0x01, DCS_CMD, LW_PACK, 0x05, 0x03, 0x00, 0xC4, 0x00, 0x78},
	{0x01, DCS_CMD, LW_PACK, 0x0C, 0x0A, 0x00, 0xC7, 0x00, 0x02, 0x32, 0x08, 0x68, 0x2A, 0x12, 0xA5, 0xA5},
	{0x00, DCS_CMD, LW_PACK, 0x29, 0x27, 0x00, 0xC8, 0x7F, 0x6B, 0x5A, 0x4D, 0x49, 0x39, 0x3C, 0x24, 0x3B, 0x37, 0x36, 0x51, 0x40, 0x47, 0x3A, 0x3C, 0x22, 0x09, 0x02, 0x7F, 0x6B, 0x5A, 0x4D, 0x49, 0x39, 0x3C, 0x24, 0x3B, 0x37, 0x36, 0x51, 0x40, 0x47, 0x3A, 0x3C, 0x22, 0x09, 0x02},
	{0x01, DCS_CMD, LW_PACK, 0x16, 0x14, 0x00, 0xD4, 0x1E, 0x1F, 0x17, 0x37, 0x1F, 0x06, 0x1F, 0x04, 0x1F, 0x0A, 0x1F, 0x08, 0x00, 0x02, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F},
	{0x01, DCS_CMD, LW_PACK, 0x16, 0x14, 0x00, 0xD5, 0x1E, 0x1F, 0x17, 0x37, 0x1F, 0x07, 0x1F, 0x05, 0x1F, 0x0B, 0x1F, 0x09, 0x01, 0x03, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F},
	{0x01, DCS_CMD, LW_PACK, 0x16, 0x14, 0x00, 0xD6, 0x1F, 0x1E, 0x17, 0x17, 0x1F, 0x09, 0x1F, 0x0B, 0x1F, 0x05, 0x1F, 0x07, 0x03, 0x01, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F},
	{0x01, DCS_CMD, LW_PACK, 0x16, 0x14, 0x00, 0xD7, 0x1F, 0x1E, 0x17, 0x17, 0x1E, 0x08, 0x1F, 0x0A, 0x1F, 0x04, 0x1F, 0x06, 0x02, 0x00, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F},
	{0x01, DCS_CMD, LW_PACK, 0x17, 0x15, 0x00, 0xD8, 0x00, 0x00, 0x00, 0x30, 0x03, 0x30, 0x01, 0x02, 0x00, 0x01, 0x02, 0x03, 0x7B, 0x00, 0x00, 0x73, 0x07, 0x06, 0x7B, 0x08},
	{0x01, DCS_CMD, LW_PACK, 0x18, 0x16, 0x00, 0xD9, 0x00, 0x00, 0x00, 0x88, 0x00, 0x00, 0x06, 0x7B, 0x00, 0x87, 0x01, 0x3B, 0xDB, 0x1F, 0x00, 0x00, 0x00, 0x03, 0x7B, 0x01, 0xE0},
	{0x01, DCS_CMD, SW_PACK1, 0x01, 0x35},
	{0x78, DCS_CMD, SW_PACK1, 0x01, 0x11},
	{0x28, DCS_CMD, SW_PACK1, 0x01, 0x29},
};

static u8 lcd_cmds_suspend[][ROW_LINE] = {
	{0x64, DCS_CMD, SW_PACK1, 0x01, 0x28},
	{0xff, DCS_CMD, SW_PACK1, 0x01, 0x10},  //TODO delay is 300ms.
	{0x10, GEN_CMD, SW_PACK2, 0x02, 0xB1, 0x01}, //4.5ma,but diaodian
};

static u8 lcd_cmds_resume[][ROW_LINE] = {
	{0x01, DCS_CMD, LW_PACK, 0x06, 0x04, 0x00, 0xBF, 0x92, 0x61, 0xF3},
	{0x01, DCS_CMD, LW_PACK, 0x05, 0x03, 0x00, 0xB3, 0x00, 0x65},
	{0x01, DCS_CMD, LW_PACK, 0x05, 0x03, 0x00, 0xB4, 0x00, 0x39},
	{0x00, DCS_CMD, LW_PACK, 0x09, 0x07, 0x00, 0xB8, 0x00, 0xF0, 0x01, 0x00, 0xF0, 0x01},
	{0x01, DCS_CMD, SW_PACK2, 0x02, 0xC3, 0x04, },
	{0x01, DCS_CMD, LW_PACK, 0x05, 0x03, 0x00, 0xC4, 0x00, 0x78},
	{0x01, DCS_CMD, LW_PACK, 0x0C, 0x0A, 0x00, 0xC7, 0x00, 0x02, 0x32, 0x08, 0x68, 0x2A, 0x12, 0xA5, 0xA5},
	{0x00, DCS_CMD, LW_PACK, 0x29, 0x27, 0x00, 0xC8, 0x7F, 0x6B, 0x5A, 0x4D, 0x49, 0x39, 0x3C, 0x24, 0x3B, 0x37, 0x36, 0x51, 0x40, 0x47, 0x3A, 0x3C, 0x22, 0x09, 0x02, 0x7F, 0x6B, 0x5A, 0x4D, 0x49, 0x39, 0x3C, 0x24, 0x3B, 0x37, 0x36, 0x51, 0x40, 0x47, 0x3A, 0x3C, 0x22, 0x09, 0x02},
	{0x01, DCS_CMD, LW_PACK, 0x16, 0x14, 0x00, 0xD4, 0x1E, 0x1F, 0x17, 0x37, 0x1F, 0x06, 0x1F, 0x04, 0x1F, 0x0A, 0x1F, 0x08, 0x00, 0x02, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F},
	{0x01, DCS_CMD, LW_PACK, 0x16, 0x14, 0x00, 0xD5, 0x1E, 0x1F, 0x17, 0x37, 0x1F, 0x07, 0x1F, 0x05, 0x1F, 0x0B, 0x1F, 0x09, 0x01, 0x03, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F},
	{0x01, DCS_CMD, LW_PACK, 0x16, 0x14, 0x00, 0xD6, 0x1F, 0x1E, 0x17, 0x17, 0x1F, 0x09, 0x1F, 0x0B, 0x1F, 0x05, 0x1F, 0x07, 0x03, 0x01, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F},
	{0x01, DCS_CMD, LW_PACK, 0x16, 0x14, 0x00, 0xD7, 0x1F, 0x1E, 0x17, 0x17, 0x1E, 0x08, 0x1F, 0x0A, 0x1F, 0x04, 0x1F, 0x06, 0x02, 0x00, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F},
	{0x01, DCS_CMD, LW_PACK, 0x17, 0x15, 0x00, 0xD8, 0x00, 0x00, 0x00, 0x30, 0x03, 0x30, 0x01, 0x02, 0x00, 0x01, 0x02, 0x03, 0x7B, 0x00, 0x00, 0x73, 0x07, 0x06, 0x7B, 0x08},
	{0x01, DCS_CMD, LW_PACK, 0x18, 0x16, 0x00, 0xD9, 0x00, 0x00, 0x00, 0x88, 0x00, 0x00, 0x06, 0x7B, 0x00, 0x87, 0x01, 0x3B, 0xDB, 0x1F, 0x00, 0x00, 0x00, 0x03, 0x7B, 0x01, 0xE0},
	{0x01, DCS_CMD, SW_PACK1, 0x01, 0x35},
	{0x78, DCS_CMD, SW_PACK1, 0x01, 0x11},
	{0x28, DCS_CMD, SW_PACK1, 0x01, 0x29},

	{0xff, DCS_CMD, SW_PACK1, 0x01, 0x11},
	{0x00, GEN_CMD, SW_PACK2, 0x02, 0xB0, 0x04},
	{0x00, GEN_CMD, LW_PACK, 0x07, 0x05, 0x00, 0xBB, 0x7B, 0xFF, 0x0F, 0x02, 0x01, 0x00},
	{0xff, DCS_CMD, SW_PACK1, 0x01, 0x29},
};
static u8 lcd_pre_read_id[][ROW_LINE] = {
	{0x00, DCS_CMD, LW_PACK, 0x06, 0x04, 0x00, 0xBF, 0x5A, 0xA5, 0xFF},
};
static struct common_id_info lcd_common_id_info[] = {
	{DCS_CMD, {0x92, 0x61}, 2, 0xDF},
};
static struct common_id_info lcd_common_esd_info[] = {
	{DCS_CMD, {0x9C}, 1, 0x0A},
};

static int lcd_jd_9261aa_reset ( struct comipfb_info *fbi )
{
	int gpio_rst = fbi->pdata->gpio_rst;

	if ( gpio_rst >= 0 ) {
		gpio_request ( gpio_rst, "LCD Reset" );
		gpio_direction_output ( gpio_rst, 1 );
		mdelay ( 10 );
		gpio_direction_output ( gpio_rst, 0 );
		mdelay ( 10 );
		gpio_direction_output ( gpio_rst, 1 );
		mdelay ( 20 );
		gpio_free ( gpio_rst );
	}
	return 0;
}

static int lcd_jd_9261aa_suspend ( struct comipfb_info *fbi )
{
	int ret = 0;
	struct comipfb_dev_timing_mipi *mipi;

	mipi = & ( fbi->cdev->timing.mipi );

	if ( mipi->display_mode == MIPI_VIDEO_MODE ) {
		mipi_dsih_hal_mode_config ( fbi, 1 );
	}

	if ( ! ( fbi->pdata->flags & COMIPFB_SLEEP_POWEROFF ) )
		ret = comipfb_if_mipi_dev_cmds ( fbi, &fbi->cdev->cmds_suspend );

	msleep ( 20 );
	mipi_dsih_dphy_enable_hs_clk ( fbi, 0 );

	if ( fbi->cdev->reset )
		fbi->cdev->reset ( fbi );

	mipi_dsih_dphy_ulps_en ( fbi, 1 );
	mipi_dsih_dphy_reset ( fbi, 0 );
	mipi_dsih_dphy_shutdown ( fbi, 0 );

	return ret;
}

static int lcd_jd_9261aa_resume ( struct comipfb_info *fbi )
{
	int ret = 0;
	struct comipfb_dev_timing_mipi *mipi;

	mipi = & ( fbi->cdev->timing.mipi );

	mipi_dsih_dphy_shutdown ( fbi, 1 );
	mipi_dsih_dphy_reset ( fbi, 1 );
	mipi_dsih_dphy_ulps_en ( fbi, 0 );

	if ( fbi->cdev->reset )
		fbi->cdev->reset ( fbi );

#ifdef CONFIG_FBCON_DRAW_PANIC_TEXT

	if ( unlikely ( kpanic_in_progress == 1 ) ) {
		ret = comipfb_if_mipi_dev_cmds ( fbi, &fbi->cdev->cmds_init );
	} else
		ret = comipfb_if_mipi_dev_cmds ( fbi, &fbi->cdev->cmds_resume );

#else
	ret = comipfb_if_mipi_dev_cmds ( fbi, &fbi->cdev->cmds_resume );
#endif
	msleep ( 20 );

	if ( mipi->display_mode == MIPI_VIDEO_MODE ) {
		mipi_dsih_hal_mode_config ( fbi, 0 );
	}

	mipi_dsih_dphy_enable_hs_clk ( fbi, 1 );

	return ret;
}

struct comipfb_dev lcd_jd_9261aa_dev = {
	.name = "lcd_jd_9261aa",
	.interface_info = COMIPFB_MIPI_IF,
	.lcd_id = LCD_ID_JD_9261AA,
	.refresh_en = 1,
	.bpp = 32,
	.xres = 540,
	.yres = 960,
	.flags = 0,
	.pclk = 34000000,//30M,62
	.auto_fps = 1,
	.timing = {
		.mipi = {
			.hs_freq = 52000,               //Kbyte
			.lp_freq = 13000,                //KHZ
			.no_lanes = 2,
			.display_mode = MIPI_VIDEO_MODE,
			.im_pin_val = 1,
			.color_mode = {
				.color_bits = COLOR_CODE_24BIT,
			},
			.videomode_info = {
				.hsync = 10,
				.hbp = 10,
				.hfp = 10,
				.vsync = 2,
				.vbp = 12,
				.vfp = 5,
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
				//.clk_tprepare = 3, //HSBYTECLK
			},
			.teinfo = {
				.te_source = 1, //external signal
				.te_trigger_mode = 0,
				.te_en = 0,
				.te_sync_en = 0,
			},
			.ext_info = {
				//.eotp_tx_en = 1,
			},
		},
	},
	.panel_id_info = {
		.id_info = lcd_common_id_info,
		.num_id_info = 1,
		.prepare_cmd = {ARRAY_AND_SIZE(lcd_pre_read_id)},
	},
	.cmds_init = {ARRAY_AND_SIZE ( lcd_cmds_init ) },
	.cmds_suspend = {ARRAY_AND_SIZE ( lcd_cmds_suspend ) },
	.cmds_resume = {ARRAY_AND_SIZE ( lcd_cmds_resume ) },
	.reset = lcd_jd_9261aa_reset,
	.suspend = lcd_jd_9261aa_suspend,
	.resume = lcd_jd_9261aa_resume,
	.backlight_info = {
		ARRAY_AND_SIZE ( backlight_cmds ),
		.brightness_bit = 8,
	},
#ifdef CONFIG_FB_COMIP_ESD
	.esd_id_info = {
		.id_info = lcd_common_esd_info,
		.num_id_info = 1,
	},
#endif

};

static int __init lcd_jd_9261aa_init ( void )
{
	return comipfb_dev_register ( &lcd_jd_9261aa_dev );
}

subsys_initcall ( lcd_jd_9261aa_init );