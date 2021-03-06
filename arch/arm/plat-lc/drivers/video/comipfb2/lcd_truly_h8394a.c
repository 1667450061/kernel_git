#include "comipfb.h"
#include "comipfb_dev.h"
#include "mipi_cmd.h"
#include "mipi_interface.h"

static u8 lcd_cmds_init[][ROW_LINE] = {

	{0x00, DCS_CMD, LW_PACK, 0x06, 0x04, 0x00, 0xB9, 0XFF, 0X83, 0X94},

	{0x00, DCS_CMD, LW_PACK, 0x05, 0x03, 0x00, 0xBA, 0x13, 0x82},

	// set B1 (POWER)  delay 20ms
	{0x00, DCS_CMD, LW_PACK, 0x14, 0X12, 0x00, 0xB1, 0x01, 0x00, 0x04, 0xC4, 0x03, 0x12, 0xF1, 0x24, 0x2C, 0x3F, 0x3F, 0x57, 0x02, 0x00, 0xE6, 0xE2, 0xA6},
	// SET B2(DISPLAY)
	{0x00, DCS_CMD, LW_PACK, 0x09, 0x07, 0x00, 0xB2, 0x00, 0xC8, 0x0E, 0x30, 0x00, 0x33},
	// SET B4(CYC)
	{0x00, DCS_CMD, LW_PACK, 0x22, 0x20, 0x00, 0xB4, 0x80, 0x04, 0x32, 0x10, 0x08, 0x54, 0x15, 0x0F, 0x22, 0x10, 0x08, 0x47, 0x53, 0x54, 0x0A, 0x4B, 0x53, 0x54, 0x02, 0x61, 0x61, 0x02, 0x06, 0x44, 0x06, 0x5F, 0x0A, 0x6B, 0x70, 0x05, 0x08},

	{0x00, DCS_CMD, SW_PACK2, 0x02, 0xB6, 0x25},

	{0x00, DCS_CMD, LW_PACK, 0x39, 0x37, 0x00, 0xD5, 0x00, 0x00, 0x00, 0x00, 0x0A, 0x00, 0x01, 0x22, 0x00, 0x33, 0xCC, 0x00, 0xAA, 0xBB, 0x01, 0x23, 0x45, 0x67, 0x9A, 0xBC, 0x45, 0x67, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x01, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x3C, 0x01},

	{0x00, DCS_CMD, SW_PACK2, 0x02, 0xCC, 0x09},

	{0x00, DCS_CMD, LW_PACK, 0x07, 0x05, 0x00, 0xBF, 0x06, 0x02, 0x10, 0x04},

	{0x00, DCS_CMD, LW_PACK, 0x07, 0x05, 0x00, 0xC7, 0x00, 0x10, 0x00, 0x10},


	{0X00, DCS_CMD, LW_PACK, 0X2d, 0x2b, 0x00, 0xE0, 0x00, 0x08, 0x0D, 0x2B, 0x31, 0x3F, 0x1A, 0x36, 0x05, 0x0B, 0x0E, 0x11, 0x13, 0x11, 0x12, 0x11, 0x19, 0x00, 0x08, 0x0D, 0x2B, 0x31, 0x3F, 0x1A, 0x36, 0x05, 0x0B, 0x0E, 0x11, 0x13, 0x11, 0x12, 0x11, 0x19, 0x09, 0x16, 0x07, 0x12, 0x09, 0x16, 0x07, 0x12},

	{0x00, DCS_CMD, LW_PACK, 0x05, 0x03, 0x00, 0xC0, 0x0C, 0x17},

	{0x00, DCS_CMD, LW_PACK, 0x05, 0x03, 0x00, 0xC6, 0x08, 0x08},

	{0X00, DCS_CMD, SW_PACK2, 0x02, 0xD4, 0x32},

	// SLEEP OUT  PacketHeader[0x05 0x11 0x00],than: delay 150ms
	{0X96, DCS_CMD, SW_PACK1, 0x01, 0x11},

	{0x14, DCS_CMD, LW_PACK, 0x06, 0x04, 0x00, 0x29, 0x00, 0xFF, 0x10},
	// Display ON   packet header  [0x05 0x11 0x00 xx]  -- cmd with no data
	//{0x14, DCS_CMD, SW_PACK1, 0x01, 0x29},

};

static u8 lcd_cmds_suspend[][ROW_LINE] = {
	{0x0A, DCS_CMD, SW_PACK1, 0x01, 0x28},
	{0x78, DCS_CMD, SW_PACK1, 0x01, 0x10},
};

static u8 lcd_cmds_resume[][ROW_LINE] = {

	{0x00, DCS_CMD, LW_PACK, 0x06, 0x04, 0x00, 0xB9, 0XFF, 0X83, 0X94},

	{0x00, DCS_CMD, LW_PACK, 0x05, 0x03, 0x00, 0xBA, 0x13, 0x82},

	// set B1 (POWER)  delay 20ms
	{0x00, DCS_CMD, LW_PACK, 0x14, 0X12, 0x00, 0xB1, 0x01, 0x00, 0x04, 0xC4, 0x03, 0x12, 0xF1, 0x24, 0x2C, 0x3F, 0x3F, 0x57, 0x02, 0x00, 0xE6, 0xE2, 0xA6},
	// SET B2(DISPLAY)
	{0x00, DCS_CMD, LW_PACK, 0x09, 0x07, 0x00, 0xB2, 0x00, 0xC8, 0x0E, 0x30, 0x00, 0x33},
	// SET B4(CYC)
	{0x00, DCS_CMD, LW_PACK, 0x22, 0x20, 0x00, 0xB4, 0x80, 0x04, 0x32, 0x10, 0x08, 0x54, 0x15, 0x0F, 0x22, 0x10, 0x08, 0x47, 0x53, 0x54, 0x0A, 0x4B, 0x53, 0x54, 0x02, 0x61, 0x61, 0x02, 0x06, 0x44, 0x06, 0x5F, 0x0A, 0x6B, 0x70, 0x05, 0x08},

	{0x00, DCS_CMD, SW_PACK2, 0x02, 0xB6, 0x25},

	{0x00, DCS_CMD, LW_PACK, 0x39, 0x37, 0x00, 0xD5, 0x00, 0x00, 0x00, 0x00, 0x0A, 0x00, 0x01, 0x22, 0x00, 0x33, 0xCC, 0x00, 0xAA, 0xBB, 0x01, 0x23, 0x45, 0x67, 0x9A, 0xBC, 0x45, 0x67, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x01, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x3C, 0x01},

	{0x00, DCS_CMD, SW_PACK2, 0x02, 0xCC, 0x09},

	{0x00, DCS_CMD, LW_PACK, 0x07, 0x05, 0x00, 0xBF, 0x06, 0x02, 0x10, 0x04},

	{0x00, DCS_CMD, LW_PACK, 0x07, 0x05, 0x00, 0xC7, 0x00, 0x10, 0x00, 0x10},


	{0X00, DCS_CMD, LW_PACK, 0X2d, 0x2b, 0x00, 0xE0, 0x00, 0x08, 0x0D, 0x2B, 0x31, 0x3F, 0x1A, 0x36, 0x05, 0x0B, 0x0E, 0x11, 0x13, 0x11, 0x12, 0x11, 0x19, 0x00, 0x08, 0x0D, 0x2B, 0x31, 0x3F, 0x1A, 0x36, 0x05, 0x0B, 0x0E, 0x11, 0x13, 0x11, 0x12, 0x11, 0x19, 0x09, 0x16, 0x07, 0x12, 0x09, 0x16, 0x07, 0x12},

	{0x00, DCS_CMD, LW_PACK, 0x05, 0x03, 0x00, 0xC0, 0x0C, 0x17},

	{0x00, DCS_CMD, LW_PACK, 0x05, 0x03, 0x00, 0xC6, 0x08, 0x08},

	{0X00, DCS_CMD, SW_PACK2, 0x02, 0xD4, 0x32},

	// SLEEP OUT  PacketHeader[0x05 0x11 0x00],than: delay 150ms
	{0X96, DCS_CMD, SW_PACK1, 0x01, 0x11},

	{0x14, DCS_CMD, LW_PACK, 0x06, 0x04, 0x00, 0x29, 0x00, 0xFF, 0x10},
	// Display ON   packet header  [0x05 0x11 0x00 xx]  -- cmd with no data
	//{0x14, DCS_CMD, SW_PACK1, 0x01, 0x29},

};

static u8 lcd_pre_read_id[][ROW_LINE] = {
	//{0x00, DCS_CMD, LW_PACK, 0x06, 0x04, 0x00, 0xB9, 0xFF, 0x83, 0x94},
	//{0x00, DCS_CMD, LW_PACK, 0x10, 0x0E, 0x00, 0xBA, 0x33, 0x83, 0xA8, 0xAD, 0xB6, 0x00, 0x00, 0x40, 0x10, 0xFF, 0x0F, 0x00, 0x80},
	{0x00, DCS_CMD, LW_PACK, 0x06, 0x04, 0x00, 0xB9, 0xFF, 0x83, 0x94},
	{0x00, DCS_CMD, SW_PACK2, 0x02, 0xFE, 0xF4},
	{0x00, DCS_CMD, SW_PACK1, 0x01, 0xFF},
};
static struct common_id_info lcd_common_id_info[] = {
	{DCS_CMD, {0x83, 0x94, 0x1A}, 3, 0x04},
};
static struct common_id_info lcd_common_esd_info[] = {
	{DCS_CMD, {0x1C}, 1, 0x0A},
};
static int lcd_truly_h8394a_power(struct comipfb_info *fbi, int onoff)
{
	int gpio_rst = fbi->pdata->gpio_rst;

	if (gpio_rst < 0) {
		pr_err("no reset pin found\n");
		return -ENXIO;
	}

	gpio_request(gpio_rst, "LCD Reset");

	if (onoff) {
		gpio_direction_output(gpio_rst, 0);
		pmic_voltage_set(PMIC_POWER_LCD_IO, 0, PMIC_POWER_VOLTAGE_ENABLE);
		pmic_voltage_set(PMIC_POWER_LCD_CORE, 0, PMIC_POWER_VOLTAGE_ENABLE);
		mdelay(50);
		gpio_direction_output(gpio_rst, 1);
		mdelay(10);
		gpio_direction_output(gpio_rst, 0);
		mdelay(10);
		gpio_direction_output(gpio_rst, 1);
		mdelay(180);
	} else {
		gpio_direction_output(gpio_rst, 0);
		pmic_voltage_set(PMIC_POWER_LCD_CORE, 0, PMIC_POWER_VOLTAGE_DISABLE);
		pmic_voltage_set(PMIC_POWER_LCD_IO, 0, PMIC_POWER_VOLTAGE_DISABLE);
		mdelay(10);
	}

	gpio_free(gpio_rst);

	return 0;
}

static int lcd_truly_h8394a_reset(struct comipfb_info *fbi)
{
	int gpio_rst = fbi->pdata->gpio_rst;

	if (gpio_rst >= 0) {
		gpio_request(gpio_rst, "LCD Reset");
		gpio_direction_output(gpio_rst, 1);
		mdelay(10);
		gpio_direction_output(gpio_rst, 0);
		mdelay(10);
		gpio_direction_output(gpio_rst, 1);
		mdelay(180);
		gpio_free(gpio_rst);
	}
	return 0;
}

static int lcd_truly_h8394a_suspend(struct comipfb_info *fbi)
{
	int ret=0;
	struct comipfb_dev_timing_mipi *mipi;

	mipi = &(fbi->cdev->timing.mipi);

	if (mipi->display_mode == MIPI_VIDEO_MODE) {
		mipi_dsih_hal_mode_config(fbi, 1);
	}

	comipfb_if_mipi_dev_cmds(fbi, &fbi->cdev->cmds_suspend);

	mdelay(20);
	mipi_dsih_dphy_enable_hs_clk(fbi, 0);

	mipi_dsih_dphy_reset(fbi, 0);
	mipi_dsih_dphy_shutdown(fbi, 0);

	return ret;
}

static int lcd_truly_h8394a_resume(struct comipfb_info *fbi)
{
	int ret=0;
	struct comipfb_dev_timing_mipi *mipi;

	mipi = &(fbi->cdev->timing.mipi);

	mipi_dsih_dphy_shutdown(fbi, 1);
	mipi_dsih_dphy_reset(fbi, 1);

	//if (fbi->cdev->reset)
	//	fbi->cdev->reset(fbi);

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

/*frame rate 57*/
struct comipfb_dev lcd_truly_h8394a_dev = {
	.name = "lcd_truly_h8394a",
	.interface_info = COMIPFB_MIPI_IF,
	.lcd_id = LCD_ID_TRULY_H8394A,
	.refresh_en = 1,
	.bpp = 32,
	.xres = 720,
	.yres = 1280,
	.flags = 0,
	.pclk = 60000000,
	.timing = {
		.mipi = {
			.hs_freq = 52000,
			.lp_freq = 13000,		//KHZ
			.no_lanes = 4,
			.display_mode = MIPI_VIDEO_MODE,
			.im_pin_val = 1,
			.color_mode = {
				.color_bits = COLOR_CODE_24BIT,
			},
			.videomode_info = {
				.hsync = 10,
				.hbp = 20,
				.hfp = 50,
				.vsync = 4,
				.vbp = 12,
				.vfp = 14,
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
				.te_en = 0,
				.te_sync_en = 0,
			},
			.ext_info = {
				.eotp_tx_en = 0,
			},
		},
	},
	.panel_id_info = {
		.id_info = lcd_common_id_info,
		.num_id_info = 1,
		.prepare_cmd = {ARRAY_AND_SIZE(lcd_pre_read_id)},
	},
	.cmds_init = {ARRAY_AND_SIZE(lcd_cmds_init)},
	.cmds_suspend = {ARRAY_AND_SIZE(lcd_cmds_suspend)},
	.cmds_resume = {ARRAY_AND_SIZE(lcd_cmds_resume)},
	.power = lcd_truly_h8394a_power,
	.reset = lcd_truly_h8394a_reset,
	.suspend = lcd_truly_h8394a_suspend,
	.resume = lcd_truly_h8394a_resume,
#ifdef CONFIG_FB_COMIP_ESD
	.esd_id_info = {
		.id_info = lcd_common_esd_info,
		.num_id_info = 1,
	},
#endif
};

static int __init lcd_truly_h8394a_init(void)
{
	return comipfb_dev_register(&lcd_truly_h8394a_dev);
}

subsys_initcall(lcd_truly_h8394a_init);
