#include "comipfb.h"
#include "comipfb_dev.h"
#include "mipi_cmd.h"
#include "mipi_interface.h"

static u8 backlight_cmds[][ROW_LINE] = {
	{0x00, GEN_CMD, SW_PACK2, 0x02, 0x51, 0xBE},
};

//[0]: delay after transfer; [1]:count of data; [2]: word count ls; [3]:word count ms; [4]...: data for transfering
static u8 lcd_cmds_init[][ROW_LINE] = {
#if 1
	/****Start Initial Sequence ***/
	{0, GEN_CMD, LW_PACK, 0x07, 0x05,0x00, 0xFF,0xAA,0x55,0xA5,0x80},

	// pump sequence
	{0, GEN_CMD, SW_PACK2, 0x02, 0xF4,0x00},
	{0, GEN_CMD, LW_PACK, 0x0c, 0x0a,0x00, 0xF8,0x10,0x00,0x00,0x00,0x00,0x02,0x10,0x40,0x50},
	//{0, GEN_CMD, LW_PACK, 0x06, 0x04,0x00, 0xF7,0x08,0x02,0xEF},

	//CMD2 page0 enable
	{0, GEN_CMD, LW_PACK, 0x08, 0x06,0x00, 0xF0,0x55,0xAA,0x52,0x08,0x00},
	{0, GEN_CMD, LW_PACK, 0x05, 0x03,0x00, 0xB1,0x72,0x11},
	//{0, GEN_CMD, LW_PACK, 0x05, 0x03,0x00, 0xB1,0x72,0x11},
	{0, GEN_CMD, SW_PACK2, 0x02, 0xB2,0x25},
	{0, GEN_CMD, LW_PACK, 0x08, 0x06,0x00, 0xBD,0x02,0x67,0x20,0x20,0x00},
	{0, GEN_CMD, LW_PACK, 0x08, 0x06,0x00, 0xBE,0x02,0x67,0x20,0x20,0x03},

	//CMD2 page1 enable
	{0, GEN_CMD, LW_PACK, 0x08, 0x06,0x00, 0xF0,0x55,0xAA,0x52,0x08,0x01},

	//0120 LGD modify VGH = 17.6V free pump
	{0, GEN_CMD, LW_PACK, 0x05, 0x03,0x00, 0xB3,0x35,0x35},

	//0120 LGD modify VGL = -14.4V
	{0, GEN_CMD, LW_PACK, 0x05, 0x03,0x00, 0xB4,0x25,0x25},

	//HV regulator off only VGLX
	{0, GEN_CMD, SW_PACK2, 0x02, 0xCA,0x80},

	//0120 LGD modify VCOM -2.175V
	{0, GEN_CMD, SW_PACK2, 0x02, 0xBE,0x96},
	{0, GEN_CMD, SW_PACK2, 0x02, 0xBF,0x96},
	{0, GEN_CMD, SW_PACK2, 0x02, 0xD2,0x96},
	{0, GEN_CMD, SW_PACK2, 0x02, 0xD3,0x96},

	//CMD2 page2 enable
	{0, GEN_CMD, LW_PACK, 0x08, 0x06,0x00, 0xF0,0x55,0xAA,0x52,0x08,0x02},
	{0, GEN_CMD, LW_PACK, 0x13, 0x11,0x00, 0xB0,0x00,0x00,0x00,0x20,0x00,0x50,0x00,0x7C,0x00,0x8C,0x00,0x90,0x00,0x94,0x00,0xB4},
	{0, GEN_CMD, LW_PACK, 0x13, 0x11,0x00, 0xB1,0x00,0xE8,0x01,0x2A,0x01,0x5A,0x01,0xAC,0x01,0xEE,0x01,0xF0,0x02,0x2E,0x02,0x6F},
	{0, GEN_CMD, LW_PACK, 0x13, 0x11,0x00, 0xB2,0x02,0x99,0x02,0xD9,0x03,0x04,0x03,0x46,0x03,0x77,0x03,0x94,0x03,0x9F,0x03,0xAC},
	{0, GEN_CMD, LW_PACK, 0x07, 0x05,0x00, 0xB3,0x03,0xBA,0x03,0xC0},
	{0, GEN_CMD, LW_PACK, 0x13, 0x11,0x00, 0xB4,0x00,0x00,0x00,0x20,0x00,0x50,0x00,0x7C,0x00,0x8C,0x00,0x90,0x00,0x94,0x00,0xB4},
	{0, GEN_CMD, LW_PACK, 0x13, 0x11,0x00, 0xB5,0x00,0xE8,0x01,0x2A,0x01,0x5A,0x01,0xAC,0x01,0xEE,0x01,0xF0,0x02,0x2E,0x02,0x6F},
	{0, GEN_CMD, LW_PACK, 0x13, 0x11,0x00, 0xB6,0x02,0x99,0x02,0xD9,0x03,0x04,0x03,0x46,0x03,0x77,0x03,0x94,0x03,0x9F,0x03,0xAC},
	{0, GEN_CMD, LW_PACK, 0x07, 0x05,0x00, 0xB7,0x03,0xBA,0x03,0xC0},
	{0, GEN_CMD, LW_PACK, 0x13, 0x11,0x00, 0xB8,0x00,0x00,0x00,0x20,0x00,0x50,0x00,0x7C,0x00,0x8C,0x00,0x90,0x00,0x94,0x00,0xB4},
	{0, GEN_CMD, LW_PACK, 0x13, 0x11,0x00, 0xB9,0x00,0xE8,0x01,0x2A,0x01,0x5A,0x01,0xAC,0x01,0xEE,0x01,0xF0,0x02,0x2E,0x02,0x6F},
	{0, GEN_CMD, LW_PACK, 0x13, 0x11,0x00, 0xBA,0x02,0x99,0x02,0xD9,0x03,0x04,0x03,0x46,0x03,0x77,0x03,0x94,0x03,0x9F,0x03,0xAC},
	{0, GEN_CMD, LW_PACK, 0x07, 0x05,0x00, 0xBB,0x03,0xBA,0x03,0xC0},
	{0, GEN_CMD, LW_PACK, 0x13, 0x11,0x00, 0xBC,0x00,0x00,0x00,0x20,0x00,0x50,0x00,0x7C,0x00,0x8C,0x00,0x90,0x00,0x94,0x00,0xB4},
	{0, GEN_CMD, LW_PACK, 0x13, 0x11,0x00, 0xBD,0x00,0xE8,0x01,0x2A,0x01,0x5A,0x01,0xAC,0x01,0xEE,0x01,0xF0,0x02,0x2E,0x02,0x6F},
	{0, GEN_CMD, LW_PACK, 0x13, 0x11,0x00, 0xBE,0x02,0x99,0x02,0xD9,0x03,0x04,0x03,0x46,0x03,0x77,0x03,0x94,0x03,0x9F,0x03,0xAC},
	{0, GEN_CMD, LW_PACK, 0x07, 0x05,0x00, 0xBF,0x03,0xBA,0x03,0xC0},
	{0, GEN_CMD, LW_PACK, 0x13, 0x11,0x00, 0xC0,0x00,0x00,0x00,0x20,0x00,0x50,0x00,0x7C,0x00,0x8C,0x00,0x90,0x00,0x94,0x00,0xB4},
	{0, GEN_CMD, LW_PACK, 0x13, 0x11,0x00, 0xC1,0x00,0xE8,0x01,0x2A,0x01,0x5A,0x01,0xAC,0x01,0xEE,0x01,0xF0,0x02,0x2E,0x02,0x6F},
	{0, GEN_CMD, LW_PACK, 0x13, 0x11,0x00, 0xC2,0x02,0x99,0x02,0xD9,0x03,0x04,0x03,0x46,0x03,0x77,0x03,0x94,0x03,0x9F,0x03,0xAC},
	{0, GEN_CMD, LW_PACK, 0x07, 0x05,0x00, 0xC3,0x03,0xBA,0x03,0xC0},
	{0, GEN_CMD, LW_PACK, 0x13, 0x11,0x00, 0xC4,0x00,0x00,0x00,0x20,0x00,0x50,0x00,0x7C,0x00,0x8C,0x00,0x90,0x00,0x94,0x00,0xB4},
	{0, GEN_CMD, LW_PACK, 0x13, 0x11,0x00, 0xC5,0x00,0xE8,0x01,0x2A,0x01,0x5A,0x01,0xAC,0x01,0xEE,0x01,0xF0,0x02,0x2E,0x02,0x6F},
	{0, GEN_CMD, LW_PACK, 0x13, 0x11,0x00, 0xC6,0x02,0x99,0x02,0xD9,0x03,0x04,0x03,0x46,0x03,0x77,0x03,0x94,0x03,0x9F,0x03,0xAC},
	{0, GEN_CMD, LW_PACK, 0x07, 0x05,0x00, 0xC7,0x03,0xBA,0x03,0xC0},

	//CMD2 page3 enable
	{0, GEN_CMD, LW_PACK, 0x08, 0x06,0x00, 0xF0,0x55,0xAA,0x52,0x08,0x03},

	{0, GEN_CMD, LW_PACK, 0x05, 0x03,0x00, 0xB0,0x20,0x00},
	{0, GEN_CMD, LW_PACK, 0x05, 0x03,0x00, 0xB1,0x20,0x00},
	{0, GEN_CMD, LW_PACK, 0x08, 0x06,0x00, 0xB2,0x15,0x00,0x17,0x00,0x00},
	{0, GEN_CMD, LW_PACK, 0x08, 0x06,0x00, 0xB3,0x15,0x00,0x17,0x00,0x00},
	{0, GEN_CMD, LW_PACK, 0x08, 0x06,0x00, 0xB4,0x05,0x00,0x17,0x00,0x00},
	{0, GEN_CMD, LW_PACK, 0x08, 0x06,0x00, 0xB5,0x15,0x00,0x17,0x00,0x00},
	{0, GEN_CMD, LW_PACK, 0x08, 0x06,0x00, 0xB6,0x05,0x00,0x17,0x00,0x00},
	{0, GEN_CMD, LW_PACK, 0x08, 0x06,0x00, 0xB7,0x05,0x00,0x17,0x00,0x00},
	{0, GEN_CMD, LW_PACK, 0x08, 0x06,0x00, 0xB8,0x05,0x00,0x17,0x00,0x00},
	{0, GEN_CMD, LW_PACK, 0x08, 0x06,0x00, 0xB9,0x05,0x00,0x17,0x00,0x00},
	{0, GEN_CMD, LW_PACK, 0x08, 0x06,0x00, 0xBA,0x53,0x10,0x19,0x00,0x00},
	{0, GEN_CMD, LW_PACK, 0x08, 0x06,0x00, 0xBB,0x53,0x10,0x19,0x00,0x00},
	{0, GEN_CMD, LW_PACK, 0x08, 0x06,0x00, 0xBC,0x53,0x00,0x1A,0x00,0x00},
	{0, GEN_CMD, LW_PACK, 0x08, 0x06,0x00, 0xBD,0x53,0x10,0x1A,0x00,0x00},
	{0, GEN_CMD, LW_PACK, 0x07, 0x05,0x00, 0xC0,0x00,0x34,0x00,0x00},
	{0, GEN_CMD, LW_PACK, 0x07, 0x05,0x00, 0xC1,0x00,0x00,0x34,0x00},
	{0, GEN_CMD, LW_PACK, 0x07, 0x05,0x00, 0xC2,0x00,0x00,0x34,0x00},
	{0, GEN_CMD, LW_PACK, 0x07, 0x05,0x00, 0xC3,0x00,0x00,0x34,0x00},
	{0, GEN_CMD, SW_PACK2, 0x02, 0xC4,0x60},
	{0, GEN_CMD, SW_PACK2, 0x02, 0xC5,0xC0},
	{0, GEN_CMD, SW_PACK2, 0x02, 0xC6,0x00},
	{0, GEN_CMD, SW_PACK2, 0x02, 0xC7,0x00},

	//CMD2 page5 enable
	{0, GEN_CMD, LW_PACK, 0x08, 0x06,0x00, 0xF0,0x55,0xAA,0x52,0x08,0x05},

	{0, GEN_CMD, SW_PACK2, 0x02, 0xE5,0x00},
	{0, GEN_CMD, SW_PACK2, 0x02, 0xED,0x30},
	{0, GEN_CMD, LW_PACK, 0x05, 0x03,0x00, 0xB0,0x17,0x06},
	{0, GEN_CMD, SW_PACK2, 0x02, 0xB8,0x0C},
	{0, GEN_CMD, LW_PACK, 0x08, 0x06,0x00, 0xBD,0x03,0x03,0x01,0x03,0x03},
	{0, GEN_CMD, LW_PACK, 0x05, 0x03,0x00, 0xB1,0x17,0x06},
	{0, GEN_CMD, LW_PACK, 0x05, 0x03,0x00, 0xB9,0x00,0x03},
	{0, GEN_CMD, LW_PACK, 0x05, 0x03,0x00, 0xB2,0x17,0x06},
	{0, GEN_CMD, LW_PACK, 0x05, 0x03,0x00, 0xBA,0x00,0x01},
	{0, GEN_CMD, LW_PACK, 0x05, 0x03,0x00, 0xB3,0x17,0x06},
	{0, GEN_CMD, LW_PACK, 0x05, 0x03,0x00, 0xBB,0x0A,0x03},
	{0, GEN_CMD, LW_PACK, 0x05, 0x03,0x00, 0xB4,0x17,0x06},
	{0, GEN_CMD, LW_PACK, 0x05, 0x03,0x00, 0xB5,0x17,0x06},
	{0, GEN_CMD, LW_PACK, 0x05, 0x03,0x00, 0xB6,0x14,0x03},
	{0, GEN_CMD, LW_PACK, 0x05, 0x03,0x00, 0xB7,0x00,0x00},
	{0, GEN_CMD, LW_PACK, 0x05, 0x03,0x00, 0xBC,0x02,0x03},
	{0, GEN_CMD, SW_PACK2, 0x02, 0xE5,0x06},
	{0, GEN_CMD, SW_PACK2, 0x02, 0xE6,0x06},
	{0, GEN_CMD, SW_PACK2, 0x02, 0xE7,0x06},
	{0, GEN_CMD, SW_PACK2, 0x02, 0xE8,0x06},
	{0, GEN_CMD, SW_PACK2, 0x02, 0xE9,0x06},
	{0, GEN_CMD, SW_PACK2, 0x02, 0xEA,0x06},
	{0, GEN_CMD, SW_PACK2, 0x02, 0xEB,0x00},
	{0, GEN_CMD, SW_PACK2, 0x02, 0xEC,0x00},
	{0, GEN_CMD, SW_PACK2, 0x02, 0xC2,0xA6},
	{0, GEN_CMD, SW_PACK2, 0x02, 0xC3,0x05},
        {0, GEN_CMD, SW_PACK2, 0x02, 0x6F,0x13},
        {0, GEN_CMD, SW_PACK2, 0x02, 0xF7,0x00},
	//{0, GEN_CMD, SW_PACK2, 0x02, 0xC0,0x07},
	//{0, GEN_CMD, SW_PACK2, 0x02, 0xC1,0x06},
	//STV ahead one line check with customer
	{0, GEN_CMD, SW_PACK2, 0x02, 0xC0,0x06},
	{0, GEN_CMD, SW_PACK2, 0x02, 0xC1,0x05},

	{0, GEN_CMD, SW_PACK2, 0x02, 0xC4,0xA6},
	{0, GEN_CMD, SW_PACK2, 0x02, 0xC5,0xA6},
	{0, GEN_CMD, SW_PACK2, 0x02, 0xC6,0xA6},
	{0, GEN_CMD, SW_PACK2, 0x02, 0xC7,0xA6},
	{0, GEN_CMD, LW_PACK, 0x05, 0x03,0x00, 0xC8,0x05,0x20},
	{0, GEN_CMD, LW_PACK, 0x05, 0x03,0x00, 0xC9,0x04,0x20},
	{0, GEN_CMD, LW_PACK, 0x05, 0x03,0x00, 0xCA,0x01,0x25},
	{0, GEN_CMD, LW_PACK, 0x05, 0x03,0x00, 0xCB,0x01,0x60},
	{0, GEN_CMD, LW_PACK, 0x08, 0x06,0x00, 0xD1,0x00,0x35,0x01,0x07,0x10},
	{0, GEN_CMD, LW_PACK, 0x08, 0x06,0x00, 0xD2,0x10,0x35,0x02,0x03,0x10},
	{0, GEN_CMD, LW_PACK, 0x08, 0x06,0x00, 0xD3,0x20,0x00,0x43,0x07,0x10},
	{0, GEN_CMD, LW_PACK, 0x08, 0x06,0x00, 0xD4,0x30,0x00,0x43,0x07,0x10},
	{0, GEN_CMD, LW_PACK, 0x0a, 0x08,0x00, 0xD0,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
	{0, GEN_CMD, LW_PACK, 0x0e, 0x0c,0x00, 0xD5,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
	{0, GEN_CMD, LW_PACK, 0x0e, 0x0c,0x00, 0xD6,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
	{0, GEN_CMD, LW_PACK, 0x0e, 0x0c,0x00, 0xD7,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
	{0, GEN_CMD, LW_PACK, 0x08, 0x06,0x00, 0xD8,0x00,0x00,0x00,0x00,0x00},
	{0, GEN_CMD, LW_PACK, 0x06, 0x04,0x00, 0xCC,0x00,0x00,0x01},
	{0, GEN_CMD, LW_PACK, 0x06, 0x04,0x00, 0xCD,0x00,0x00,0x01},
	{0, GEN_CMD, LW_PACK, 0x06, 0x04,0x00, 0xCE,0x00,0x00,0x02},
	{0, GEN_CMD, LW_PACK, 0x06, 0x04,0x00, 0xCF,0x00,0x00,0x02},

	//CMD2 page6 enable
	{0, GEN_CMD, LW_PACK, 0x08, 0x06,0x00, 0xF0,0x55,0xAA,0x52,0x08,0x06},

	{0, GEN_CMD, LW_PACK, 0x08, 0x06,0x00, 0xF0,0x55,0xAA,0x52,0x08,0x06},
	{0, GEN_CMD, LW_PACK, 0x05, 0x03,0x00, 0xB0,0x31,0x31},
	{0, GEN_CMD, LW_PACK, 0x05, 0x03,0x00, 0xB1,0x31,0x31},
	{0, GEN_CMD, LW_PACK, 0x05, 0x03,0x00, 0xB2,0x2D,0x2E},
	{0, GEN_CMD, LW_PACK, 0x05, 0x03,0x00, 0xB3,0x31,0x34},
	{0, GEN_CMD, LW_PACK, 0x05, 0x03,0x00, 0xB4,0x29,0x2A},
	{0, GEN_CMD, LW_PACK, 0x05, 0x03,0x00, 0xB5,0x16,0x19},
	{0, GEN_CMD, LW_PACK, 0x05, 0x03,0x00, 0xB6,0x18,0x17},
	{0, GEN_CMD, LW_PACK, 0x05, 0x03,0x00, 0xB7,0x02,0x03},
	{0, GEN_CMD, LW_PACK, 0x05, 0x03,0x00, 0xB8,0x08,0x31},
	{0, GEN_CMD, LW_PACK, 0x05, 0x03,0x00, 0xB9,0x34,0x33},
	{0, GEN_CMD, LW_PACK, 0x05, 0x03,0x00, 0xBA,0x33,0x34},
	{0, GEN_CMD, LW_PACK, 0x05, 0x03,0x00, 0xBB,0x31,0x08},
	{0, GEN_CMD, LW_PACK, 0x05, 0x03,0x00, 0xBC,0x01,0x00},
	{0, GEN_CMD, LW_PACK, 0x05, 0x03,0x00, 0xBD,0x11,0x12},
	{0, GEN_CMD, LW_PACK, 0x05, 0x03,0x00, 0xBE,0x13,0x10},
	{0, GEN_CMD, LW_PACK, 0x05, 0x03,0x00, 0xBF,0x2A,0x29},
	{0, GEN_CMD, LW_PACK, 0x05, 0x03,0x00, 0xC0,0x34,0x31},
	{0, GEN_CMD, LW_PACK, 0x05, 0x03,0x00, 0xC1,0x2E,0x2D},
	{0, GEN_CMD, LW_PACK, 0x05, 0x03,0x00, 0xC2,0x31,0x31},
	{0, GEN_CMD, LW_PACK, 0x05, 0x03,0x00, 0xC3,0x31,0x31},
	{0, GEN_CMD, LW_PACK, 0x05, 0x03,0x00, 0xE5,0x00,0x00},
	{0, GEN_CMD, LW_PACK, 0x05, 0x03,0x00, 0xC4,0x31,0x31},
	{0, GEN_CMD, LW_PACK, 0x05, 0x03,0x00, 0xC5,0x31,0x31},
	{0, GEN_CMD, LW_PACK, 0x05, 0x03,0x00, 0xC6,0x2E,0x2D},
	{0, GEN_CMD, LW_PACK, 0x05, 0x03,0x00, 0xC7,0x31,0x34},
	{0, GEN_CMD, LW_PACK, 0x05, 0x03,0x00, 0xC8,0x29,0x2A},
	{0, GEN_CMD, LW_PACK, 0x05, 0x03,0x00, 0xC9,0x17,0x18},
	{0, GEN_CMD, LW_PACK, 0x05, 0x03,0x00, 0xCA,0x19,0x16},
	{0, GEN_CMD, LW_PACK, 0x05, 0x03,0x00, 0xCB,0x03,0x02},
	{0, GEN_CMD, LW_PACK, 0x05, 0x03,0x00, 0xCC,0x08,0x31},
	{0, GEN_CMD, LW_PACK, 0x05, 0x03,0x00, 0xCD,0x34,0x33},
	{0, GEN_CMD, LW_PACK, 0x05, 0x03,0x00, 0xCE,0x33,0x34},
	{0, GEN_CMD, LW_PACK, 0x05, 0x03,0x00, 0xCF,0x31,0x08},
	{0, GEN_CMD, LW_PACK, 0x05, 0x03,0x00, 0xD0,0x00,0x01},
	{0, GEN_CMD, LW_PACK, 0x05, 0x03,0x00, 0xD1,0x10,0x13},
	{0, GEN_CMD, LW_PACK, 0x05, 0x03,0x00, 0xD2,0x12,0x11},
	{0, GEN_CMD, LW_PACK, 0x05, 0x03,0x00, 0xD3,0x2A,0x29},
	{0, GEN_CMD, LW_PACK, 0x05, 0x03,0x00, 0xD4,0x34,0x31},
	{0, GEN_CMD, LW_PACK, 0x05, 0x03,0x00, 0xD5,0x2D,0x2E},
	{0, GEN_CMD, LW_PACK, 0x05, 0x03,0x00, 0xD6,0x31,0x31},
	{0, GEN_CMD, LW_PACK, 0x05, 0x03,0x00, 0xD7,0x31,0x31},
	{0, GEN_CMD, LW_PACK, 0x05, 0x03,0x00, 0xE6,0x31,0x31},
	{0, GEN_CMD, LW_PACK, 0x08, 0x06,0x00, 0xD8,0x00,0x00,0x00,0x00,0x00},
	{0, GEN_CMD, LW_PACK, 0x08, 0x06,0x00, 0xD9,0x00,0x00,0x00,0x00,0x00},
	{0, GEN_CMD, SW_PACK2, 0x02, 0xE7,0x00},

	//CMD2 page0 enable                                                                                 
	//{0, GEN_CMD, LW_PACK, 0x08, 0x06,0x00, 0xF0,0x55,0xAA,0x52,0x08,0x00},                             
	//Bist function
	//{0, GEN_CMD, LW_PACK, 0x07, 0x05,0x00, 0xEE,0x87,0x78,0x02,0x40},

	// Row resolution
	{0, GEN_CMD, LW_PACK, 0x07, 0x05,0x00, 0x2A,0x00,0x00,0x02,0xFF},
	//CCMOFF
	//CCMRUN
	{0, GEN_CMD, SW_PACK2, 0x02, 0x35,0x00},
	{120, GEN_CMD, SW_PACK1, 0x01, 0x11},
	{0, GEN_CMD, SW_PACK1, 0x01, 0x29},
#else
	{0, GEN_CMD, LW_PACK, 0x08, 0x06,0x00, 0xF0,0x55,0xAA,0x52,0x08,0x00},
	{0, GEN_CMD, LW_PACK, 0x07, 0x05,0x00, 0xEE,0x87,0x78,0x02,0x40},
	{0, GEN_CMD, LW_PACK, 0x05, 0x03,0x00, 0xEF,0x07,0xFF},
#endif
};

static u8 lcd_cmds_suspend[][ROW_LINE] = {
	{0x64, GEN_CMD, SW_PACK1, 0x01, 0x28},
	{0xff, GEN_CMD, SW_PACK1, 0x01, 0x10},	//TODO delay is 400ms.
};

static u8 lcd_cmds_resume[][ROW_LINE] = {
/****Start Initial Sequence ***/
	{0, GEN_CMD, LW_PACK, 0x07, 0x05,0x00, 0xFF,0xAA,0x55,0xA5,0x80},

	// pump sequence
	{0, GEN_CMD, SW_PACK2, 0x02, 0xF4,0x00},
	{0, GEN_CMD, LW_PACK, 0x0c, 0x0a,0x00, 0xF8,0x10,0x00,0x00,0x00,0x00,0x02,0x10,0x40,0x50},
	//{0, GEN_CMD, LW_PACK, 0x06, 0x04,0x00, 0xF7,0x08,0x02,0xEF},

	//CMD2 page0 enable
	{0, GEN_CMD, LW_PACK, 0x08, 0x06,0x00, 0xF0,0x55,0xAA,0x52,0x08,0x00},
	{0, GEN_CMD, LW_PACK, 0x05, 0x03,0x00, 0xB1,0x72,0x11},
	//{0, GEN_CMD, LW_PACK, 0x05, 0x03,0x00, 0xB1,0x72,0x11},
	{0, GEN_CMD, SW_PACK2, 0x02, 0xB2,0x25},
	{0, GEN_CMD, LW_PACK, 0x08, 0x06,0x00, 0xBD,0x02,0x67,0x20,0x20,0x00},
	{0, GEN_CMD, LW_PACK, 0x08, 0x06,0x00, 0xBE,0x02,0x67,0x20,0x20,0x03},

	//CMD2 page1 enable
	{0, GEN_CMD, LW_PACK, 0x08, 0x06,0x00, 0xF0,0x55,0xAA,0x52,0x08,0x01},

	//0120 LGD modify VGH = 17.6V free pump
	{0, GEN_CMD, LW_PACK, 0x05, 0x03,0x00, 0xB3,0x35,0x35},

	//0120 LGD modify VGL = -14.4V
	{0, GEN_CMD, LW_PACK, 0x05, 0x03,0x00, 0xB4,0x25,0x25},

	//HV regulator off only VGLX
	{0, GEN_CMD, SW_PACK2, 0x02, 0xCA,0x80},

	//0120 LGD modify VCOM -2.175V
	{0, GEN_CMD, SW_PACK2, 0x02, 0xBE,0x96},
	{0, GEN_CMD, SW_PACK2, 0x02, 0xBF,0x96},
	{0, GEN_CMD, SW_PACK2, 0x02, 0xD2,0x96},
	{0, GEN_CMD, SW_PACK2, 0x02, 0xD3,0x96},

	//CMD2 page2 enable
	{0, GEN_CMD, LW_PACK, 0x08, 0x06,0x00, 0xF0,0x55,0xAA,0x52,0x08,0x02},
	{0, GEN_CMD, LW_PACK, 0x13, 0x11,0x00, 0xB0,0x00,0x00,0x00,0x20,0x00,0x50,0x00,0x7C,0x00,0x8C,0x00,0x90,0x00,0x94,0x00,0xB4},
	{0, GEN_CMD, LW_PACK, 0x13, 0x11,0x00, 0xB1,0x00,0xE8,0x01,0x2A,0x01,0x5A,0x01,0xAC,0x01,0xEE,0x01,0xF0,0x02,0x2E,0x02,0x6F},
	{0, GEN_CMD, LW_PACK, 0x13, 0x11,0x00, 0xB2,0x02,0x99,0x02,0xD9,0x03,0x04,0x03,0x46,0x03,0x77,0x03,0x94,0x03,0x9F,0x03,0xAC},
	{0, GEN_CMD, LW_PACK, 0x07, 0x05,0x00, 0xB3,0x03,0xBA,0x03,0xC0},
	{0, GEN_CMD, LW_PACK, 0x13, 0x11,0x00, 0xB4,0x00,0x00,0x00,0x20,0x00,0x50,0x00,0x7C,0x00,0x8C,0x00,0x90,0x00,0x94,0x00,0xB4},
	{0, GEN_CMD, LW_PACK, 0x13, 0x11,0x00, 0xB5,0x00,0xE8,0x01,0x2A,0x01,0x5A,0x01,0xAC,0x01,0xEE,0x01,0xF0,0x02,0x2E,0x02,0x6F},
	{0, GEN_CMD, LW_PACK, 0x13, 0x11,0x00, 0xB6,0x02,0x99,0x02,0xD9,0x03,0x04,0x03,0x46,0x03,0x77,0x03,0x94,0x03,0x9F,0x03,0xAC},
	{0, GEN_CMD, LW_PACK, 0x07, 0x05,0x00, 0xB7,0x03,0xBA,0x03,0xC0},
	{0, GEN_CMD, LW_PACK, 0x13, 0x11,0x00, 0xB8,0x00,0x00,0x00,0x20,0x00,0x50,0x00,0x7C,0x00,0x8C,0x00,0x90,0x00,0x94,0x00,0xB4},
	{0, GEN_CMD, LW_PACK, 0x13, 0x11,0x00, 0xB9,0x00,0xE8,0x01,0x2A,0x01,0x5A,0x01,0xAC,0x01,0xEE,0x01,0xF0,0x02,0x2E,0x02,0x6F},
	{0, GEN_CMD, LW_PACK, 0x13, 0x11,0x00, 0xBA,0x02,0x99,0x02,0xD9,0x03,0x04,0x03,0x46,0x03,0x77,0x03,0x94,0x03,0x9F,0x03,0xAC},
	{0, GEN_CMD, LW_PACK, 0x07, 0x05,0x00, 0xBB,0x03,0xBA,0x03,0xC0},
	{0, GEN_CMD, LW_PACK, 0x13, 0x11,0x00, 0xBC,0x00,0x00,0x00,0x20,0x00,0x50,0x00,0x7C,0x00,0x8C,0x00,0x90,0x00,0x94,0x00,0xB4},
	{0, GEN_CMD, LW_PACK, 0x13, 0x11,0x00, 0xBD,0x00,0xE8,0x01,0x2A,0x01,0x5A,0x01,0xAC,0x01,0xEE,0x01,0xF0,0x02,0x2E,0x02,0x6F},
	{0, GEN_CMD, LW_PACK, 0x13, 0x11,0x00, 0xBE,0x02,0x99,0x02,0xD9,0x03,0x04,0x03,0x46,0x03,0x77,0x03,0x94,0x03,0x9F,0x03,0xAC},
	{0, GEN_CMD, LW_PACK, 0x07, 0x05,0x00, 0xBF,0x03,0xBA,0x03,0xC0},
	{0, GEN_CMD, LW_PACK, 0x13, 0x11,0x00, 0xC0,0x00,0x00,0x00,0x20,0x00,0x50,0x00,0x7C,0x00,0x8C,0x00,0x90,0x00,0x94,0x00,0xB4},
	{0, GEN_CMD, LW_PACK, 0x13, 0x11,0x00, 0xC1,0x00,0xE8,0x01,0x2A,0x01,0x5A,0x01,0xAC,0x01,0xEE,0x01,0xF0,0x02,0x2E,0x02,0x6F},
	{0, GEN_CMD, LW_PACK, 0x13, 0x11,0x00, 0xC2,0x02,0x99,0x02,0xD9,0x03,0x04,0x03,0x46,0x03,0x77,0x03,0x94,0x03,0x9F,0x03,0xAC},
	{0, GEN_CMD, LW_PACK, 0x07, 0x05,0x00, 0xC3,0x03,0xBA,0x03,0xC0},
	{0, GEN_CMD, LW_PACK, 0x13, 0x11,0x00, 0xC4,0x00,0x00,0x00,0x20,0x00,0x50,0x00,0x7C,0x00,0x8C,0x00,0x90,0x00,0x94,0x00,0xB4},
	{0, GEN_CMD, LW_PACK, 0x13, 0x11,0x00, 0xC5,0x00,0xE8,0x01,0x2A,0x01,0x5A,0x01,0xAC,0x01,0xEE,0x01,0xF0,0x02,0x2E,0x02,0x6F},
	{0, GEN_CMD, LW_PACK, 0x13, 0x11,0x00, 0xC6,0x02,0x99,0x02,0xD9,0x03,0x04,0x03,0x46,0x03,0x77,0x03,0x94,0x03,0x9F,0x03,0xAC},
	{0, GEN_CMD, LW_PACK, 0x07, 0x05,0x00, 0xC7,0x03,0xBA,0x03,0xC0},

	//CMD2 page3 enable
	{0, GEN_CMD, LW_PACK, 0x08, 0x06,0x00, 0xF0,0x55,0xAA,0x52,0x08,0x03},

	{0, GEN_CMD, LW_PACK, 0x05, 0x03,0x00, 0xB0,0x20,0x00},
	{0, GEN_CMD, LW_PACK, 0x05, 0x03,0x00, 0xB1,0x20,0x00},
	{0, GEN_CMD, LW_PACK, 0x08, 0x06,0x00, 0xB2,0x15,0x00,0x17,0x00,0x00},
	{0, GEN_CMD, LW_PACK, 0x08, 0x06,0x00, 0xB3,0x15,0x00,0x17,0x00,0x00},
	{0, GEN_CMD, LW_PACK, 0x08, 0x06,0x00, 0xB4,0x05,0x00,0x17,0x00,0x00},
	{0, GEN_CMD, LW_PACK, 0x08, 0x06,0x00, 0xB5,0x15,0x00,0x17,0x00,0x00},
	{0, GEN_CMD, LW_PACK, 0x08, 0x06,0x00, 0xB6,0x05,0x00,0x17,0x00,0x00}, 
	{0, GEN_CMD, LW_PACK, 0x08, 0x06,0x00, 0xB7,0x05,0x00,0x17,0x00,0x00},
	{0, GEN_CMD, LW_PACK, 0x08, 0x06,0x00, 0xB8,0x05,0x00,0x17,0x00,0x00},
	{0, GEN_CMD, LW_PACK, 0x08, 0x06,0x00, 0xB9,0x05,0x00,0x17,0x00,0x00},
	{0, GEN_CMD, LW_PACK, 0x08, 0x06,0x00, 0xBA,0x53,0x10,0x19,0x00,0x00},
	{0, GEN_CMD, LW_PACK, 0x08, 0x06,0x00, 0xBB,0x53,0x10,0x19,0x00,0x00},
	{0, GEN_CMD, LW_PACK, 0x08, 0x06,0x00, 0xBC,0x53,0x00,0x1A,0x00,0x00},
	{0, GEN_CMD, LW_PACK, 0x08, 0x06,0x00, 0xBD,0x53,0x10,0x1A,0x00,0x00},
	{0, GEN_CMD, LW_PACK, 0x07, 0x05,0x00, 0xC0,0x00,0x34,0x00,0x00},
	{0, GEN_CMD, LW_PACK, 0x07, 0x05,0x00, 0xC1,0x00,0x00,0x34,0x00},
	{0, GEN_CMD, LW_PACK, 0x07, 0x05,0x00, 0xC2,0x00,0x00,0x34,0x00},
	{0, GEN_CMD, LW_PACK, 0x07, 0x05,0x00, 0xC3,0x00,0x00,0x34,0x00},
	{0, GEN_CMD, SW_PACK2, 0x02, 0xC4,0x60},
	{0, GEN_CMD, SW_PACK2, 0x02, 0xC5,0xC0},
	{0, GEN_CMD, SW_PACK2, 0x02, 0xC6,0x00},
	{0, GEN_CMD, SW_PACK2, 0x02, 0xC7,0x00},

	//CMD2 page5 enable
	{0, GEN_CMD, LW_PACK, 0x08, 0x06,0x00, 0xF0,0x55,0xAA,0x52,0x08,0x05},

	{0, GEN_CMD, SW_PACK2, 0x02, 0xE5,0x00},
	{0, GEN_CMD, SW_PACK2, 0x02, 0xED,0x30},
	{0, GEN_CMD, LW_PACK, 0x05, 0x03,0x00, 0xB0,0x17,0x06},
	{0, GEN_CMD, SW_PACK2, 0x02, 0xB8,0x0C},
	{0, GEN_CMD, LW_PACK, 0x08, 0x06,0x00, 0xBD,0x03,0x03,0x01,0x03,0x03},
	{0, GEN_CMD, LW_PACK, 0x05, 0x03,0x00, 0xB1,0x17,0x06},
	{0, GEN_CMD, LW_PACK, 0x05, 0x03,0x00, 0xB9,0x00,0x03},
	{0, GEN_CMD, LW_PACK, 0x05, 0x03,0x00, 0xB2,0x17,0x06},
	{0, GEN_CMD, LW_PACK, 0x05, 0x03,0x00, 0xBA,0x00,0x01},
	{0, GEN_CMD, LW_PACK, 0x05, 0x03,0x00, 0xB3,0x17,0x06},
	{0, GEN_CMD, LW_PACK, 0x05, 0x03,0x00, 0xBB,0x0A,0x03},
	{0, GEN_CMD, LW_PACK, 0x05, 0x03,0x00, 0xB4,0x17,0x06},
	{0, GEN_CMD, LW_PACK, 0x05, 0x03,0x00, 0xB5,0x17,0x06},
	{0, GEN_CMD, LW_PACK, 0x05, 0x03,0x00, 0xB6,0x14,0x03},
	{0, GEN_CMD, LW_PACK, 0x05, 0x03,0x00, 0xB7,0x00,0x00},
	{0, GEN_CMD, LW_PACK, 0x05, 0x03,0x00, 0xBC,0x02,0x03},
	{0, GEN_CMD, SW_PACK2, 0x02, 0xE5,0x06},
	{0, GEN_CMD, SW_PACK2, 0x02, 0xE6,0x06},
	{0, GEN_CMD, SW_PACK2, 0x02, 0xE7,0x06},
	{0, GEN_CMD, SW_PACK2, 0x02, 0xE8,0x06},
	{0, GEN_CMD, SW_PACK2, 0x02, 0xE9,0x06},
	{0, GEN_CMD, SW_PACK2, 0x02, 0xEA,0x06},
	{0, GEN_CMD, SW_PACK2, 0x02, 0xEB,0x00},
	{0, GEN_CMD, SW_PACK2, 0x02, 0xEC,0x00},
	{0, GEN_CMD, SW_PACK2, 0x02, 0xC2,0xA6},
	{0, GEN_CMD, SW_PACK2, 0x02, 0xC3,0x05},
	//{0, GEN_CMD, SW_PACK2, 0x02, 0xC0,0x07},
	//{0, GEN_CMD, SW_PACK2, 0x02, 0xC1,0x06},
	//STV ahead one line check with customer
	{0, GEN_CMD, SW_PACK2, 0x02, 0xC0,0x06},
	{0, GEN_CMD, SW_PACK2, 0x02, 0xC1,0x05},

	{0, GEN_CMD, SW_PACK2, 0x02, 0xC4,0xA6},
	{0, GEN_CMD, SW_PACK2, 0x02, 0xC5,0xA6},
	{0, GEN_CMD, SW_PACK2, 0x02, 0xC6,0xA6},
	{0, GEN_CMD, SW_PACK2, 0x02, 0xC7,0xA6},
	{0, GEN_CMD, LW_PACK, 0x05, 0x03,0x00, 0xC8,0x05,0x20},
	{0, GEN_CMD, LW_PACK, 0x05, 0x03,0x00, 0xC9,0x04,0x20},
	{0, GEN_CMD, LW_PACK, 0x05, 0x03,0x00, 0xCA,0x01,0x25},
	{0, GEN_CMD, LW_PACK, 0x05, 0x03,0x00, 0xCB,0x01,0x60},
	{0, GEN_CMD, LW_PACK, 0x08, 0x06,0x00, 0xD1,0x00,0x35,0x01,0x07,0x10},
	{0, GEN_CMD, LW_PACK, 0x08, 0x06,0x00, 0xD2,0x10,0x35,0x02,0x03,0x10},
	{0, GEN_CMD, LW_PACK, 0x08, 0x06,0x00, 0xD3,0x20,0x00,0x43,0x07,0x10},
	{0, GEN_CMD, LW_PACK, 0x08, 0x06,0x00, 0xD4,0x30,0x00,0x43,0x07,0x10},
	{0, GEN_CMD, LW_PACK, 0x0a, 0x08,0x00, 0xD0,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
	{0, GEN_CMD, LW_PACK, 0x0e, 0x0c,0x00, 0xD5,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
	{0, GEN_CMD, LW_PACK, 0x0e, 0x0c,0x00, 0xD6,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
	{0, GEN_CMD, LW_PACK, 0x0e, 0x0c,0x00, 0xD7,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
	{0, GEN_CMD, LW_PACK, 0x08, 0x06,0x00, 0xD8,0x00,0x00,0x00,0x00,0x00},
	{0, GEN_CMD, LW_PACK, 0x06, 0x04,0x00, 0xCC,0x00,0x00,0x01},
	{0, GEN_CMD, LW_PACK, 0x06, 0x04,0x00, 0xCD,0x00,0x00,0x01},
	{0, GEN_CMD, LW_PACK, 0x06, 0x04,0x00, 0xCE,0x00,0x00,0x02},
	{0, GEN_CMD, LW_PACK, 0x06, 0x04,0x00, 0xCF,0x00,0x00,0x02},

	//CMD2 page6 enable
	{0, GEN_CMD, LW_PACK, 0x08, 0x06,0x00, 0xF0,0x55,0xAA,0x52,0x08,0x06},

	{0, GEN_CMD, LW_PACK, 0x08, 0x06,0x00, 0xF0,0x55,0xAA,0x52,0x08,0x06},
	{0, GEN_CMD, LW_PACK, 0x05, 0x03,0x00, 0xB0,0x31,0x31},
	{0, GEN_CMD, LW_PACK, 0x05, 0x03,0x00, 0xB1,0x31,0x31},
	{0, GEN_CMD, LW_PACK, 0x05, 0x03,0x00, 0xB2,0x2D,0x2E},
	{0, GEN_CMD, LW_PACK, 0x05, 0x03,0x00, 0xB3,0x31,0x34},
	{0, GEN_CMD, LW_PACK, 0x05, 0x03,0x00, 0xB4,0x29,0x2A},
	{0, GEN_CMD, LW_PACK, 0x05, 0x03,0x00, 0xB5,0x16,0x19},
	{0, GEN_CMD, LW_PACK, 0x05, 0x03,0x00, 0xB6,0x18,0x17},
	{0, GEN_CMD, LW_PACK, 0x05, 0x03,0x00, 0xB7,0x02,0x03},
	{0, GEN_CMD, LW_PACK, 0x05, 0x03,0x00, 0xB8,0x08,0x31},
	{0, GEN_CMD, LW_PACK, 0x05, 0x03,0x00, 0xB9,0x34,0x33},
	{0, GEN_CMD, LW_PACK, 0x05, 0x03,0x00, 0xBA,0x33,0x34},
	{0, GEN_CMD, LW_PACK, 0x05, 0x03,0x00, 0xBB,0x31,0x08},
	{0, GEN_CMD, LW_PACK, 0x05, 0x03,0x00, 0xBC,0x01,0x00},
	{0, GEN_CMD, LW_PACK, 0x05, 0x03,0x00, 0xBD,0x11,0x12},
	{0, GEN_CMD, LW_PACK, 0x05, 0x03,0x00, 0xBE,0x13,0x10},
	{0, GEN_CMD, LW_PACK, 0x05, 0x03,0x00, 0xBF,0x2A,0x29},
	{0, GEN_CMD, LW_PACK, 0x05, 0x03,0x00, 0xC0,0x34,0x31},
	{0, GEN_CMD, LW_PACK, 0x05, 0x03,0x00, 0xC1,0x2E,0x2D},
	{0, GEN_CMD, LW_PACK, 0x05, 0x03,0x00, 0xC2,0x31,0x31},
	{0, GEN_CMD, LW_PACK, 0x05, 0x03,0x00, 0xC3,0x31,0x31},
	{0, GEN_CMD, LW_PACK, 0x05, 0x03,0x00, 0xE5,0x00,0x00},
	{0, GEN_CMD, LW_PACK, 0x05, 0x03,0x00, 0xC4,0x31,0x31},
	{0, GEN_CMD, LW_PACK, 0x05, 0x03,0x00, 0xC5,0x31,0x31},
	{0, GEN_CMD, LW_PACK, 0x05, 0x03,0x00, 0xC6,0x2E,0x2D},
	{0, GEN_CMD, LW_PACK, 0x05, 0x03,0x00, 0xC7,0x31,0x34},
	{0, GEN_CMD, LW_PACK, 0x05, 0x03,0x00, 0xC8,0x29,0x2A},
	{0, GEN_CMD, LW_PACK, 0x05, 0x03,0x00, 0xC9,0x17,0x18},
	{0, GEN_CMD, LW_PACK, 0x05, 0x03,0x00, 0xCA,0x19,0x16},
	{0, GEN_CMD, LW_PACK, 0x05, 0x03,0x00, 0xCB,0x03,0x02},
	{0, GEN_CMD, LW_PACK, 0x05, 0x03,0x00, 0xCC,0x08,0x31},
	{0, GEN_CMD, LW_PACK, 0x05, 0x03,0x00, 0xCD,0x34,0x33},
	{0, GEN_CMD, LW_PACK, 0x05, 0x03,0x00, 0xCE,0x33,0x34},
	{0, GEN_CMD, LW_PACK, 0x05, 0x03,0x00, 0xCF,0x31,0x08},
	{0, GEN_CMD, LW_PACK, 0x05, 0x03,0x00, 0xD0,0x00,0x01},
	{0, GEN_CMD, LW_PACK, 0x05, 0x03,0x00, 0xD1,0x10,0x13},
	{0, GEN_CMD, LW_PACK, 0x05, 0x03,0x00, 0xD2,0x12,0x11},
	{0, GEN_CMD, LW_PACK, 0x05, 0x03,0x00, 0xD4,0x34,0x31},
	{0, GEN_CMD, LW_PACK, 0x05, 0x03,0x00, 0xD5,0x2D,0x2E},
	{0, GEN_CMD, LW_PACK, 0x05, 0x03,0x00, 0xD6,0x31,0x31},
	{0, GEN_CMD, LW_PACK, 0x05, 0x03,0x00, 0xD7,0x31,0x31},
	{0, GEN_CMD, LW_PACK, 0x05, 0x03,0x00, 0xE6,0x31,0x31},
	{0, GEN_CMD, LW_PACK, 0x08, 0x06,0x00, 0xD8,0x00,0x00,0x00,0x00,0x00},
	{0, GEN_CMD, LW_PACK, 0x08, 0x06,0x00, 0xD9,0x00,0x00,0x00,0x00,0x00},
	{0, GEN_CMD, SW_PACK2, 0x02, 0xE7,0x00},
	//CMD2 page0 enable
	//{0, GEN_CMD, LW_PACK, 0x08, 0x06,0x00, 0xF0,0x55,0xAA,0x52,0x08,0x00},                             
	//Bist function
	//{0, GEN_CMD, LW_PACK, 0x07, 0x05,0x00, 0xEE,0x87,0x78,0x02,0x40},

	// Row resolution
	{0, GEN_CMD, LW_PACK, 0x07, 0x05,0x00, 0x2A,0x00,0x00,0x02,0xFF},
	//CCMOFF
	//CCMRUN
	{0, GEN_CMD, SW_PACK2, 0x02, 0x35,0x00},
	{120, GEN_CMD, SW_PACK1, 0x01, 0x11},
	{0, GEN_CMD, SW_PACK1, 0x01, 0x29},
};

static int lcd_tm_nt35520_reset(struct comipfb_info *fbi)
{
	int gpio_rst = fbi->pdata->gpio_rst;

	if (gpio_rst >= 0) {
		gpio_request(gpio_rst, "LCD Reset");
		gpio_direction_output(gpio_rst, 1);
		mdelay(10);
		gpio_direction_output(gpio_rst, 0);
		mdelay(20);
		gpio_direction_output(gpio_rst, 1);
		mdelay(10);
		gpio_free(gpio_rst);
	}
	return 0;
}
EXPORT_SYMBOL(lcd_tm_nt35520_reset);

static int lcd_tm_nt35520_suspend(struct comipfb_info *fbi)
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
EXPORT_SYMBOL(lcd_tm_nt35520_suspend);

static int lcd_tm_nt35520_resume(struct comipfb_info *fbi)
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
	} else
		ret = comipfb_if_mipi_dev_cmds(fbi, &fbi->cdev->cmds_resume);
#else
	ret = comipfb_if_mipi_dev_cmds(fbi, &fbi->cdev->cmds_resume);
#endif
	//msleep(20);// must >20 test find
	mipi_dsih_dphy_enable_hs_clk(fbi, 1);
	mipi_dsih_video_mode(fbi, 1);

	return ret;
}
EXPORT_SYMBOL(lcd_tm_nt35520_resume);

struct comipfb_dev lcd_tm_nt35520_dev = {
	.name = "lcd_tm_nt35520",
	.control_id = 0,
	.screen_num = 0,
	.interface_info = COMIPFB_MIPI_IF,
	.default_use = 1,
	.bpp = 32,
	.xres = 768,
	.yres = 1280,
	.flags = 0,
	.pclk = 62400000,
	.refresh = 0,
	.timing = {
		.mipi = {
			.reference_freq = 26000,	//KHZ
			.output_freq = 69000,		//Kbyte must less than 43000
			.no_lanes = 4,
			.lcdc_mipi_if_mode = COLOR_CODE_24BIT,
			.hsync = 15,
			.hbp = 30,
			.hfp = 50,
			.vsync = 4,
			.vbp = 16,
			.vfp = 12,
		},
	},
	.cmds_init = {ARRAY_AND_SIZE(lcd_cmds_init)},
	.cmds_suspend = {ARRAY_AND_SIZE(lcd_cmds_suspend)},
	.cmds_resume = {ARRAY_AND_SIZE(lcd_cmds_resume)},
	.reset = lcd_tm_nt35520_reset,
	.suspend = lcd_tm_nt35520_suspend,
	.resume = lcd_tm_nt35520_resume,
	.backlight_info = {{ARRAY_AND_SIZE(backlight_cmds)},
					.brightness_bit = 5,
				},
};

static int __init lcd_tm_nt35520_init(void)
{
	return comipfb_dev_register(&lcd_tm_nt35520_dev);
}

subsys_initcall(lcd_tm_nt35520_init);
