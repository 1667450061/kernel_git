#include "comipfb.h"
#include "comipfb_dev.h"
#include "mipi_cmd.h"
#include "mipi_interface.h"

static u8 backlight_cmds[][ROW_LINE] = {
        {0x00, DCS_CMD, SW_PACK2, 0x02, 0x51, 0xBE},
};

//[0]: delay after transfer; [1]:count of data; [2]: word count ls; [3]:word count ms; [4]...: data for transfering
static u8 lcd_cmds_init[][ROW_LINE] = {
/****Start Initial Sequence ***/
	{0x00, DCS_CMD, LW_PACK, 0x06, 0x04, 0x00, 0xB9, 0xFF, 0x83, 0x69},
	{0x00, DCS_CMD, LW_PACK, 0x16, 0x14, 0x00, 0xB1, 0x01, 0x00, 0x34, 0x04, 0x00, 0x12, 0x12, 0x35, 0x3C, 0x3F, 0x3F, 0x01, 0x22, 0x01, 0xE6, 0xE6, 0xE6, 0xE6, 0xE6},
	{0x00, DCS_CMD, LW_PACK, 0x12, 0x10, 0x00, 0xB2, 0x00, 0x23, 0x03, 0x03, 0x70, 0x00, 0xFF, 0x06, 0x00, 0x00, 0x00, 0x03, 0x03, 0x00, 0x01}, 
	{0x00, DCS_CMD, LW_PACK, 0x08, 0x06, 0x00, 0xB4, 0x03, 0x10, 0x80, 0x06, 0x02},
	{0x00, DCS_CMD, LW_PACK, 0x05, 0x03, 0x00, 0xB6, 0x55, 0x55},
	{0x0A, DCS_CMD, SW_PACK2, 0x02, 0xCC, 0x00},
	{0x00, DCS_CMD, LW_PACK, 0x1D, 0x1B, 0x00, 0xD5, 0x00, 0x02, 0x00, 0x00, 0x01, 0x04,0x20,0x70,0x11,0x13,0x00,0x11,0x00,0x46,0x00,0x57,0x01,0x00,0x44,0x57,0x44,0x46,0x07,0x0F,0x02,0x03},
	{0x00, DCS_CMD, LW_PACK, 0x25, 0x23, 0x00, 0xE0, 0x0F,0x1C,0x1F,0x10,0x10,0x27,0x27,0x35,0x07,0x0E,0x10,0x15,0x17,0x15,0x15,0x12,0x17,0x0F,0x1C,0x1F,0x10,0x10,0x27,0x27,0x35,0x07,0x0E,0x10,0x15,0x17,0x15,0x15,0x12,0x17},
	{0x00, DCS_CMD, SW_PACK2, 0x02, 0x3A, 0x77},
	{0x00, DCS_CMD, LW_PACK, 0x10, 0x0E, 0x00, 0xBA, 0x00,0xA0,0xC6,0x00,0x0A,0x00,0x10,0x30,0x6F,0x02,0x11,0x58,0x40},
	{0x00, DCS_CMD, LW_PACK, 0x0C, 0x0A, 0x00, 0xC9, 0x3E, 0x00, 0x00, 0x01, 0x0F, 0x08, 0x1E, 0x1E, 0x00},
	{0x00, DCS_CMD, SW_PACK2, 0x02, 0x51, 0x00},
	{0x00, DCS_CMD, SW_PACK2, 0x02, 0x53, 0x24},
	{0x00, DCS_CMD, SW_PACK2, 0x02, 0x55, 0x01},
	{0xC8, DCS_CMD, SW_PACK1, 0x01, 0x11},
	{0x24, DCS_CMD, SW_PACK1, 0x01, 0x29},
};

static u8 lcd_cmds_suspend[][ROW_LINE] = {
	{0x64, DCS_CMD, SW_PACK1, 0x01, 0x28},
	{0xff, DCS_CMD, SW_PACK1, 0x01, 0x10},	//TODO delay is 400ms.
};

static u8 lcd_cmds_resume[][ROW_LINE] = {
	{0x00, DCS_CMD, LW_PACK, 0x06, 0x04, 0x00, 0xB9, 0xFF, 0x83, 0x69},
	{0x00, DCS_CMD, LW_PACK, 0x16, 0x14, 0x00, 0xB1, 0x01, 0x00, 0x34, 0x04, 0x00, 0x12, 0x12, 0x35, 0x3C, 0x3F, 0x3F, 0x01, 0x22, 0x01, 0xE6, 0xE6, 0xE6, 0xE6, 0xE6},
	{0x00, DCS_CMD, LW_PACK, 0x12, 0x10, 0x00, 0xB2, 0x00, 0x23, 0x03, 0x03, 0x70, 0x00, 0xFF, 0x06, 0x00, 0x00, 0x00, 0x03, 0x03, 0x00, 0x01}, 
	{0x00, DCS_CMD, LW_PACK, 0x08, 0x06, 0x00, 0xB4, 0x03, 0x10, 0x80, 0x06, 0x02},
	{0x00, DCS_CMD, LW_PACK, 0x05, 0x03, 0x00, 0xB6, 0x55, 0x55},
	{0x0A, DCS_CMD, SW_PACK2, 0x02, 0xCC, 0x00},
	{0x00, DCS_CMD, LW_PACK, 0x1D, 0x1B, 0x00, 0xD5, 0x00, 0x02, 0x00, 0x00, 0x01, 0x04,0x20,0x70,0x11,0x13,0x00,0x11,0x00,0x46,0x00,0x57,0x01,0x00,0x44,0x57,0x44,0x46,0x07,0x0F,0x02,0x03},
	{0x00, DCS_CMD, LW_PACK, 0x25, 0x23, 0x00, 0xE0, 0x0F,0x1C,0x1F,0x10,0x10,0x27,0x27,0x35,0x07,0x0E,0x10,0x15,0x17,0x15,0x15,0x12,0x17,0x0F,0x1C,0x1F,0x10,0x10,0x27,0x27,0x35,0x07,0x0E,0x10,0x15,0x17,0x15,0x15,0x12,0x17},
	{0x00, DCS_CMD, SW_PACK2, 0x02, 0x3A, 0x77},
	{0x00, DCS_CMD, LW_PACK, 0x10, 0x0E, 0x00, 0xBA, 0x00,0xA0,0xC6,0x00,0x0A,0x00,0x10,0x30,0x6F,0x02,0x11,0x58,0x40},
	{0x00, DCS_CMD, LW_PACK, 0x0C, 0x0A, 0x00, 0xC9, 0x3E, 0x00, 0x00, 0x01, 0x0F, 0x08, 0x1E, 0x1E, 0x00},
	{0x00, DCS_CMD, SW_PACK2, 0x02, 0x51, 0x00},
	{0x00, DCS_CMD, SW_PACK2, 0x02, 0x53, 0x24},
	{0x00, DCS_CMD, SW_PACK2, 0x02, 0x55, 0x01},
	{0xC8, DCS_CMD, SW_PACK1, 0x01, 0x11},
	{0x14, DCS_CMD, SW_PACK1, 0x01, 0x29},
};

static int lcd_yt_h8369a_reset(struct comipfb_info *fbi)
{
	int gpio_rst = fbi->pdata->gpio_rst;

	if (gpio_rst >= 0) {
		gpio_request(gpio_rst, "LCD Reset");
		gpio_direction_output(gpio_rst, 1);
		mdelay(10);
		gpio_direction_output(gpio_rst, 0);
		mdelay(10);
		gpio_direction_output(gpio_rst, 1);
		mdelay(20);
		gpio_free(gpio_rst);
	}
	return 0;
}
EXPORT_SYMBOL(lcd_yt_h8369a_reset);

static int lcd_yt_h8369a_suspend(struct comipfb_info *fbi)
{
	int ret=0;
	
	if (!(fbi->pdata->flags & COMIPFB_SLEEP_POWEROFF))
		ret = comipfb_if_mipi_dev_cmds(fbi, &fbi->cdev->cmds_suspend);
	mdelay(20); /*20ms test find*/
	
	mipi_dsih_dphy_enable_hs_clk(fbi, 0);
	if (fbi->cdev->reset)
		fbi->cdev->reset(fbi);
		
	mipi_dsih_dphy_enter_ulps(fbi, ENTER_ULPS);
	msleep(5);
	
	mipi_dsih_dphy_reset(fbi, 0);
	mipi_dsih_dphy_shutdown(fbi, 0);
	msleep(10);
	
	return ret;
}
EXPORT_SYMBOL(lcd_yt_h8369a_suspend);

static int lcd_yt_h8369a_resume(struct comipfb_info *fbi)
{
	int ret=0;
	
	mipi_dsih_dphy_shutdown(fbi, 1);
	mipi_dsih_dphy_reset(fbi, 1);
	mdelay(15);//must >=15
	
	mipi_dsih_dphy_exit_ulps(fbi, EXIT_ULPS);
	if (fbi->pdata->flags & COMIPFB_SLEEP_POWEROFF) {
		/* Reset device. */
		if (fbi->cdev->reset)
    			fbi->cdev->reset(fbi);
    		ret = comipfb_if_mipi_dev_cmds(fbi, &fbi->cdev->cmds_init);
  }
  
	mipi_dsih_cmd_mode(fbi, 1);
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
	//msleep(20);// must >20 test find
	mipi_dsih_dphy_enable_hs_clk(fbi, 1);
	mipi_dsih_video_mode(fbi, 1);
	
	return ret;
}
EXPORT_SYMBOL(lcd_yt_h8369a_resume);
struct comipfb_dev lcd_yt_h8369a_dev = {
	.name = "lcd_yt_h8369a",
	.control_id = 0,
	.screen_num = 0,
	.interface_info = COMIPFB_MIPI_IF,
	.default_use = 1,
	.bpp = 32,
	.xres = 480,
	.yres = 800,
	.flags = 0,
	.pclk = 24000000,
	.refresh = 0,
	.timing = {
		.mipi = {
			.reference_freq = 26000,	//KHZ
			.output_freq = 42000,		//Kbyte must less than 43000
			.no_lanes = 2,
			.lcdc_mipi_if_mode = COLOR_CODE_24BIT,
			.hsync = 15,
			.hbp = 15,
			.hfp = 12,
			.vsync = 4,
			.vbp = 7,
			.vfp = 8,
		},
	},
	.cmds_init = {ARRAY_AND_SIZE(lcd_cmds_init)},
	.cmds_suspend = {ARRAY_AND_SIZE(lcd_cmds_suspend)},
	.cmds_resume = {ARRAY_AND_SIZE(lcd_cmds_resume)},
	.reset = lcd_yt_h8369a_reset,
	.suspend = lcd_yt_h8369a_suspend,
	.resume = lcd_yt_h8369a_resume,
	.backlight_info = {ARRAY_AND_SIZE(backlight_cmds),
				.brightness_bit = 5,
				},
};

static int __init lcd_yt_h8369a_init(void)
{
	return comipfb_dev_register(&lcd_yt_h8369a_dev);
}

subsys_initcall(lcd_yt_h8369a_init);