#include "comipfb.h"
#include "comipfb_dev.h"
#include "mipi_cmd.h"
#include "mipi_interface.h"
#include <plat/comip-pmic.h>

static u8 backlight_cmds[][ROW_LINE] = {
  {0x00,GEN_CMD, SW_PACK2, 0x02, 0x51, 0xBE},
};
//[0]: delay after transfer; [1]:count of data; [2]: word count ls; [3]:word count ms; [4]...: data for transfering
static u8 lcd_cmds_init[][ROW_LINE] = 
{
	{0x00, GEN_CMD, SW_PACK2, 0x02, 0x00, 0x00},		// SET ext
	{0x00, GEN_CMD, LW_PACK, 0x06, 0x04, 0x00, 0xFF, 0x12 ,0x83 ,0x01},	// SET password

	{0x00, GEN_CMD, SW_PACK2, 0x02, 0x00, 0x80},
	{0x00, GEN_CMD, LW_PACK, 0x05, 0x03, 0x00, 0xFF ,0x12 ,0x83},		//Orise mode enable

	{0x00, GEN_CMD, SW_PACK2, 0x02, 0x00, 0x80},
	{0x00, GEN_CMD, LW_PACK, 0x0C, 0x0A, 0x00, 0xC0, 0x00, 0x64, 0x00, 0x10, 0x10, 0x00, 0x64, 0x10, 0x10},		//TCON parameters Seting

	{0x00, GEN_CMD, SW_PACK2, 0x02, 0x00, 0x90},
	{0x00, GEN_CMD, LW_PACK, 0x09, 0x07, 0x00, 0xC0, 0x00, 0x5C, 0x00, 0x01, 0x00, 0x04},	////panal parameters Seting

	{0x00, GEN_CMD, SW_PACK2, 0x02, 0x00, 0xB3},
	{0x00, GEN_CMD, LW_PACK, 0x05, 0x03, 0x00, 0xC0, 0x00, 0x55},		// column inversion

	{0x00, GEN_CMD, SW_PACK2, 0x02, 0x00, 0x81},
	{0x00, GEN_CMD, SW_PACK2, 0x02, 0xC1, 0x66},		//Frame Rate Sating

	{0x00, GEN_CMD, SW_PACK2, 0x02, 0x00, 0x90},
	{0x00, GEN_CMD, SW_PACK2, 0x02, 0xC4, 0x49},		// clock delay for data latch

	//{0x00, GEN_CMD, SW_PACK2, 0x02, 0x00, 0xA6},
	//{0x00, GEN_CMD, SW_PACK2, 0x02, 0xB3, 0x0B},		// Z inversion

	{0x00, GEN_CMD, SW_PACK2, 0x02, 0x00, 0xA0},
	{0x00, GEN_CMD, LW_PACK, 0x11, 0x0F, 0x00, 0xC4, 0x05, 0x10, 0x04, 0x02, 0x05, 0x15, 0x1A, 0x05, 0x10, 0x05, 0x02, 0x05, 0x15, 0x1A},

	{0x00, GEN_CMD, SW_PACK2, 0x02, 0x00, 0xB0},
	{0x00, GEN_CMD, LW_PACK, 0x05, 0x03, 0x00, 0xC4, 0x00, 0x00},	

	{0x00, GEN_CMD, SW_PACK2, 0x02, 0x00, 0x91},
	{0x00, GEN_CMD, LW_PACK, 0x05, 0x03, 0x00, 0xC5, 0x47, 0xD0},		//A6 VGHS[3:0] VGLS[3:0] ;  C0 VGH,VGL ratio setting

	{0x00, GEN_CMD, SW_PACK2, 0x02, 0x00, 0x00},
	{0x00, GEN_CMD, LW_PACK, 0x05, 0x03, 0x00, 0xD8, 0xb6, 0xb6},		//VGMP/VGMN Seting  C7 5V

	{0x00, GEN_CMD, SW_PACK2, 0x02, 0x00, 0x00},
	{0x00, GEN_CMD, SW_PACK2, 0x02, 0xD9, 0x2b},	//VCOM  0X3F

	{0x00, GEN_CMD, SW_PACK2, 0x02, 0x00, 0xB0},
	{0x00, GEN_CMD, LW_PACK, 0x05, 0x03, 0x00, 0xC5, 0x04, 0x38},		// VDD_18V=1.7V/LVDSVDD=1.55V

	{0x00, GEN_CMD, SW_PACK2, 0x02, 0x00, 0xBB},	//vddi detection level :1.45v
	{0x00, GEN_CMD, SW_PACK2, 0x02, 0xC5, 0x80},	//LVD voltage setting

	{0x00, GEN_CMD, SW_PACK2, 0x02, 0x00, 0x82},
	{0x00, GEN_CMD, SW_PACK2, 0x02, 0xC4, 0x02},	//chopper function

	{0x00, GEN_CMD, SW_PACK2, 0x02, 0x00, 0xC6},
	{0x00, GEN_CMD, SW_PACK2, 0x02, 0xB0, 0x03},	//mpi debounce

	{0x00, GEN_CMD, SW_PACK2, 0x02, 0x00, 0x00},	//Gamma Seting  positive
	{0x00, GEN_CMD, LW_PACK, 0x13, 0x11, 0x00, 0xE1, 0x01, 0x0E, 0x14, 0x0e, 0x07, 0x10, 0x0B, 0x09, 0x06, 0x0A, 0x0D, 0x06, 0x0E, 0x12, 0x0C, 0x09},

	{0x00, GEN_CMD, SW_PACK2, 0x02, 0x00, 0x00},	//Gamma Seting  Nagitive
	{0x00, GEN_CMD, LW_PACK, 0x13, 0x11, 0x00, 0xE2, 0x09, 0x0E, 0x14, 0x0e, 0x07, 0x10, 0x0B, 0x09, 0x06, 0x0A, 0x0D, 0x06, 0x0E, 0x12, 0x0C, 0x01},

	{0x00, GEN_CMD, SW_PACK2, 0x02, 0x00, 0x00},	//control settings
	{0x00, GEN_CMD, SW_PACK2, 0x02, 0xD0, 0x40},

	{0x00, GEN_CMD, SW_PACK2, 0x02, 0x00, 0x00},
	{0x00, GEN_CMD, LW_PACK, 0x05, 0x03, 0x00, 0xD1, 0x00, 0x00},

	{0x00, GEN_CMD, SW_PACK2, 0x02, 0x00, 0x80},
	{0x00, GEN_CMD, LW_PACK, 0x0e, 0x0c, 0x00, 0xCB, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},

	{0x00, GEN_CMD, SW_PACK2, 0x02, 0x00, 0x90},
	{0x00, GEN_CMD, LW_PACK, 0x12, 0x10, 0x00, 0xCB, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},

	{0x00, GEN_CMD, SW_PACK2, 0x02, 0x00, 0xA0},
	{0x00, GEN_CMD, LW_PACK, 0x12, 0x10, 0x00, 0xCB, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},

	{0x00, GEN_CMD, SW_PACK2, 0x02, 0x00, 0xB0},
	{0x00, GEN_CMD, LW_PACK, 0x12, 0x10, 0x00, 0xCB, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},

	{0x00, GEN_CMD, SW_PACK2, 0x02, 0x00, 0xC0},
	{0x00, GEN_CMD, LW_PACK, 0x12, 0x10, 0x00, 0xCB, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},

	{0x00, GEN_CMD, SW_PACK2, 0x02, 0x00, 0xD0},
	{0x00, GEN_CMD, LW_PACK, 0x12, 0x10, 0x00, 0xCB, 0x00, 0x00, 0x00, 0x05, 0x05, 0x00, 0x00, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x00, 0x00},

	{0x00, GEN_CMD, SW_PACK2, 0x02, 0x00, 0xE0},
	{0x00, GEN_CMD, LW_PACK, 0x11, 0x0F, 0x00, 0xCB, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x05, 0x05, 0x00, 0x00},

	{0x00, GEN_CMD, SW_PACK2, 0x02, 0x00, 0xF0},
	{0x00, GEN_CMD, LW_PACK, 0x0E, 0x0C, 0x00, 0xCB, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF},

	{0x00, GEN_CMD, SW_PACK2, 0x02, 0x00, 0x80},	//Panel pad mapping control
	{0x00, GEN_CMD, LW_PACK, 0x12, 0x10, 0x00, 0xCC, 0x07, 0x05, 0x0F, 0x0D, 0x0B, 0x09, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},

	{0x00, GEN_CMD, SW_PACK2, 0x02, 0x00, 0x90},
	{0x00, GEN_CMD, LW_PACK, 0x12, 0x10, 0x00, 0xCC, 0x00, 0x00, 0x00, 0x01, 0x03, 0x00, 0x00, 0x08, 0x06, 0x10, 0x0E, 0x0C, 0x0A, 0x00, 0x00},

	{0x00, GEN_CMD, SW_PACK2, 0x02, 0x00, 0xA0},
	{0x00, GEN_CMD, LW_PACK, 0x11, 0x0F, 0x00, 0xCC, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x04, 0x00, 0x00},

	{0x00, GEN_CMD, SW_PACK2, 0x02, 0x00, 0xB0},
	{0x00, GEN_CMD, LW_PACK, 0x12, 0x10, 0x00, 0xCC, 0x02, 0x04, 0x0E, 0x10, 0x0A, 0x0C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},

	{0x00, GEN_CMD, SW_PACK2, 0x02, 0x00, 0xC0},
	{0x00, GEN_CMD, LW_PACK, 0x12, 0x10, 0x00, 0xCC, 0x00, 0x00, 0x00, 0x08, 0x06, 0x00, 0x00, 0x01, 0x03, 0x0D, 0x0F, 0x09, 0x0B, 0x00, 0x00},

	{0x00, GEN_CMD, SW_PACK2, 0x02, 0x00, 0xD0},
	{0x00, GEN_CMD, LW_PACK, 0x11, 0x0F, 0x00, 0xCC,0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x05, 0x00, 0x00},

	{0x00, GEN_CMD, SW_PACK2, 0x02, 0x00, 0x80},
	{0x00, GEN_CMD, LW_PACK, 0x0F, 0x0D, 0x00, 0xCE, 0x87, 0x03, 0x10, 0x86, 0x03, 0x10, 0x85, 0x03, 0x10, 0x84, 0x03, 0x10},

	{0x00, GEN_CMD, SW_PACK2, 0x02, 0x00, 0x90},
	{0x00, GEN_CMD, LW_PACK, 0x0F, 0x0D, 0x00, 0xCE, 0x34, 0xFC, 0x10, 0x34, 0xFD, 0x10, 0x34, 0xFE, 0x10, 0x34, 0xFF, 0x10},

	{0x00, GEN_CMD, SW_PACK2, 0x02, 0x00, 0xA0},
	{0x00, GEN_CMD, LW_PACK, 0x11, 0x0F, 0x00, 0xCE, 0x38, 0x05, 0x04, 0xFD, 0x00, 0x10, 0x00, 0x38, 0x04, 0x04, 0xFE, 0x00, 0x10, 0x00},

	{0x00, GEN_CMD, SW_PACK2, 0x02, 0x00, 0xB0},
	{0x00, GEN_CMD, LW_PACK, 0x11, 0x0F, 0x00, 0xCE, 0x38, 0x03, 0x04, 0xFF, 0x00, 0x10, 0x00, 0x38, 0x02, 0x05, 0x00, 0x00, 0x10, 0x00},

	{0x00, GEN_CMD, SW_PACK2, 0x02, 0x00, 0xC0},
	{0x00, GEN_CMD, LW_PACK, 0x11, 0x0F, 0x00, 0xCE, 0x38, 0x01, 0x05, 0x01, 0x00, 0x10, 0x00, 0x38, 0x00, 0x05, 0x02, 0x00, 0x10, 0x00},

	{0x00, GEN_CMD, SW_PACK2, 0x02, 0x00, 0xD0},
	{0x00, GEN_CMD, LW_PACK, 0x11, 0x0F, 0x00, 0xCE, 0x30, 0x00, 0x05, 0x03, 0x00, 0x10, 0x00, 0x30, 0x01, 0x05, 0x04, 0x00, 0x10, 0x00},

	{0x00, GEN_CMD, SW_PACK2, 0x02, 0x00, 0x80},
	{0x00, GEN_CMD, LW_PACK, 0x11, 0x0F, 0x00, 0xCF, 0x30, 0x02, 0x05, 0x05, 0x00, 0x10, 0x00, 0x30, 0x03, 0x05, 0x06, 0x00, 0x10, 0x00},

	{0x00, GEN_CMD, SW_PACK2, 0x02, 0x00, 0x90},
	{0x00, GEN_CMD, LW_PACK, 0x11, 0x0F, 0x00, 0xCF, 0x30, 0x04, 0x05, 0x07, 0x00, 0x10, 0x00, 0x30, 0x05, 0x05, 0x08, 0x00, 0x10, 0x00},

	{0x00, GEN_CMD, SW_PACK2, 0x02, 0x00, 0xA0},
	{0x00, GEN_CMD, LW_PACK, 0x11, 0x0F, 0x00, 0xCF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},

	{0x00, GEN_CMD, SW_PACK2, 0x02, 0x00, 0xB0},
	{0x00, GEN_CMD, LW_PACK, 0x11, 0x0F, 0x00, 0xCF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},

	{0x00, GEN_CMD, SW_PACK2, 0x02, 0x00, 0xC0},
	{0x00, GEN_CMD, LW_PACK, 0x0E, 0x0C, 0x00, 0xCF, 0x01, 0x01, 0x20, 0x20, 0x00, 0x00, 0x01, 0x82, 0x01, 0x10, 0x10},

	{0x00, GEN_CMD, SW_PACK2, 0x02, 0x00, 0xB5},
	{0x00, GEN_CMD, LW_PACK, 0x09, 0x07, 0x00, 0xC5, 0x0C, 0x01, 0xFF, 0x0C, 0x01, 0xFF},

	{0x00, GEN_CMD, SW_PACK2, 0x02, 0x00, 0x90},
	{0x00, GEN_CMD, LW_PACK, 0x07, 0x05, 0x00, 0xF5, 0x02, 0x11, 0x02, 0x11},	// power IC setting

	{0x00, GEN_CMD, SW_PACK2, 0x02, 0x00, 0x90},
	{0x00, GEN_CMD, SW_PACK2, 0x02, 0xC5, 0x50},	//external power ic mode

	{0x00, GEN_CMD, SW_PACK2, 0x02, 0x00, 0x94},
	{0x00, GEN_CMD, SW_PACK2, 0x02, 0xC5, 0x66},	//  pump1/pump2 set pump clock ratio 110:1/8 line

	{0x00, GEN_CMD, SW_PACK2, 0x02, 0x00, 0xB2},
	{0x00, GEN_CMD, LW_PACK, 0x05, 0x03, 0x00, 0xF5, 0x00, 0x00},	//VGLO1/VGL02 disable

	{0x00, GEN_CMD, SW_PACK2, 0x02, 0x00, 0xB4},
	{0x00, GEN_CMD, LW_PACK, 0x05, 0x03, 0x00, 0xF5, 0x00, 0x00},	

	{0x00, GEN_CMD, SW_PACK2, 0x02, 0x00, 0xB6},
	{0x00, GEN_CMD, LW_PACK, 0x05, 0x03, 0x00, 0xF5, 0x00, 0x00},	

	{0x00, GEN_CMD, SW_PACK2, 0x02, 0x00, 0xB8},
	{0x00, GEN_CMD, LW_PACK, 0x05, 0x03, 0x00, 0xF5, 0x00, 0x00},	

	{0x00, GEN_CMD, SW_PACK2, 0x02, 0x00, 0x94},
	{0x00, GEN_CMD, SW_PACK2, 0x02, 0xF5, 0x02},	//VCL ON

	{0x00, GEN_CMD, SW_PACK2, 0x02, 0x00, 0xBA},
	{0x00, GEN_CMD, SW_PACK2, 0x02, 0xF5, 0x03},	//VSP ON

	{0x00, GEN_CMD, SW_PACK2, 0x02, 0x00, 0xB4},
	{0x00, GEN_CMD, SW_PACK2, 0x02, 0xC5, 0xC0},	//VGLO1/2 pull low settings



	{0x00, GEN_CMD, SW_PACK2, 0x02, 0x00, 0xA0},
	{0x00, GEN_CMD, SW_PACK2, 0x02, 0xC1, 0x00},

/*********************************************************************/
/*for VCOM drop bug*/
	{0x00, GEN_CMD, SW_PACK2, 0x02, 0x00, 0x80},	//
	{0x00, GEN_CMD, SW_PACK2, 0x02, 0xC4, 0x30},

	{0x00, GEN_CMD, SW_PACK2, 0x02, 0x00, 0x8B},	//
	{0x00, GEN_CMD, SW_PACK2, 0x02, 0xC4, 0x00},

	{0x00, GEN_CMD, SW_PACK2, 0x02, 0x00, 0x90},	////clock delay for data latch 0x49->0x52
	{0x00, GEN_CMD, SW_PACK2, 0x02, 0xC4, 0x52},

	{0x00, GEN_CMD, SW_PACK2, 0x02, 0x00, 0xB9},	//Speed Up 
	{0x00, GEN_CMD, SW_PACK2, 0x02, 0xB0, 0x51},

	{0x00, GEN_CMD, SW_PACK2, 0x02, 0x00, 0x82},	//chopper 
	{0x00, GEN_CMD, SW_PACK2, 0x02, 0xC4, 0x02},

	{0x00, GEN_CMD, SW_PACK2, 0x02, 0x00, 0xB0},	//VDD_18V adjust
	{0x00, GEN_CMD, LW_PACK, 0x05, 0x03, 0x00, 0xC5,0x04,0x38},

	{0x00, GEN_CMD, SW_PACK2, 0x02, 0x00, 0x94},	//VCL on
	{0x00, GEN_CMD, SW_PACK2, 0x02, 0xF5, 0x02},

	{0x00, GEN_CMD, SW_PACK2, 0x02, 0x00, 0xBA},	//VSP on
	{0x00, GEN_CMD, SW_PACK2, 0x02, 0xF5, 0x03},

	{0x00, GEN_CMD, SW_PACK2, 0x02, 0x00, 0xc6},	//Read Debounce
	{0x00, GEN_CMD, SW_PACK2, 0x02, 0xb0, 0x03},

	{0x00, GEN_CMD, SW_PACK2, 0x02, 0x00, 0xA0},	//Time out off 
	{0x00, GEN_CMD, SW_PACK2, 0x02, 0xC1, 0x02},

	{0x00, GEN_CMD, SW_PACK2, 0x02, 0x00, 0xc3},	//Sample hold all on
	{0x00, GEN_CMD, SW_PACK2, 0x02, 0xf5, 0x81},

	{0x00, GEN_CMD, SW_PACK2, 0x02, 0x00, 0xB1},
	{0x00, GEN_CMD, SW_PACK2, 0x02, 0xc6, 0x05},
/************************************************************************/

	{0x00, GEN_CMD, SW_PACK2, 0x02, 0x00, 0x00},
	{0x00, GEN_CMD, LW_PACK, 0x06, 0x04, 0x00, 0xFF, 0xFF, 0xFF, 0xFF},	

	//{0x00,DCS_CMD, SW_PACK1, 0x01, 0x35},//TE On
	{0x00,DCS_CMD, SW_PACK2, 0x02, 0x35, 0x00},//TE On
	{0x78,DCS_CMD, SW_PACK1, 0x01, 0x11},
	{0x0A,DCS_CMD, SW_PACK1, 0x01, 0x29},
 };

static u8 lcd_cmds_suspend[][ROW_LINE] = {
	{0x64, GEN_CMD, SW_PACK1, 0x01, 0x28},
	{0xff, GEN_CMD, SW_PACK1, 0x01, 0x10},
};

static u8 lcd_cmds_resume[][ROW_LINE] = 
{
	{0x00, GEN_CMD, SW_PACK2, 0x02, 0x00, 0x00},		// SET ext
	{0x00, GEN_CMD, LW_PACK, 0x06, 0x04, 0x00, 0xFF, 0x12 ,0x83 ,0x01},	// SET password

	{0x00, GEN_CMD, SW_PACK2, 0x02, 0x00, 0x80},
	{0x00, GEN_CMD, LW_PACK, 0x05, 0x03, 0x00, 0xFF ,0x12 ,0x83},		//Orise mode enable

	{0x00, GEN_CMD, SW_PACK2, 0x02, 0x00, 0x80},
	{0x00, GEN_CMD, LW_PACK, 0x0C, 0x0A, 0x00, 0xC0, 0x00, 0x64, 0x00, 0x10, 0x10, 0x00, 0x64, 0x10, 0x10},		//TCON parameters Seting

	{0x00, GEN_CMD, SW_PACK2, 0x02, 0x00, 0x90},
	{0x00, GEN_CMD, LW_PACK, 0x09, 0x07, 0x00, 0xC0, 0x00, 0x5C, 0x00, 0x01, 0x00, 0x04},	////panal parameters Seting

	{0x00, GEN_CMD, SW_PACK2, 0x02, 0x00, 0xB3},
	{0x00, GEN_CMD, LW_PACK, 0x05, 0x03, 0x00, 0xC0, 0x00, 0x55},		// column inversion

	{0x00, GEN_CMD, SW_PACK2, 0x02, 0x00, 0x81},
	{0x00, GEN_CMD, SW_PACK2, 0x02, 0xC1, 0x66},		//Frame Rate Sating

	{0x00, GEN_CMD, SW_PACK2, 0x02, 0x00, 0x90},
	{0x00, GEN_CMD, SW_PACK2, 0x02, 0xC4, 0x49},		// clock delay for data latch

	//{0x00, GEN_CMD, SW_PACK2, 0x02, 0x00, 0xA6},
	//{0x00, GEN_CMD, SW_PACK2, 0x02, 0xB3, 0x0B},		// Z inversion

	{0x00, GEN_CMD, SW_PACK2, 0x02, 0x00, 0xA0},
	{0x00, GEN_CMD, LW_PACK, 0x11, 0x0F, 0x00, 0xC4, 0x05, 0x10, 0x04, 0x02, 0x05, 0x15, 0x1A, 0x05, 0x10, 0x05, 0x02, 0x05, 0x15, 0x1A},

	{0x00, GEN_CMD, SW_PACK2, 0x02, 0x00, 0xB0},
	{0x00, GEN_CMD, LW_PACK, 0x05, 0x03, 0x00, 0xC4, 0x00, 0x00},	

	{0x00, GEN_CMD, SW_PACK2, 0x02, 0x00, 0x91},
	{0x00, GEN_CMD, LW_PACK, 0x05, 0x03, 0x00, 0xC5, 0x47, 0xD0},		//A6 VGHS[3:0] VGLS[3:0] ;  C0 VGH,VGL ratio setting

	{0x00, GEN_CMD, SW_PACK2, 0x02, 0x00, 0x00},
	{0x00, GEN_CMD, LW_PACK, 0x05, 0x03, 0x00, 0xD8, 0xb6, 0xb6},		//VGMP/VGMN Seting  C7 5V

	{0x00, GEN_CMD, SW_PACK2, 0x02, 0x00, 0x00},
	{0x00, GEN_CMD, SW_PACK2, 0x02, 0xD9, 0x2b},	//VCOM  0X3F

	{0x00, GEN_CMD, SW_PACK2, 0x02, 0x00, 0xB0},
	{0x00, GEN_CMD, LW_PACK, 0x05, 0x03, 0x00, 0xC5, 0x04, 0x38},		// VDD_18V=1.7V/LVDSVDD=1.55V

	{0x00, GEN_CMD, SW_PACK2, 0x02, 0x00, 0xBB},	//vddi detection level :1.45v
	{0x00, GEN_CMD, SW_PACK2, 0x02, 0xC5, 0x80},	//LVD voltage setting

	{0x00, GEN_CMD, SW_PACK2, 0x02, 0x00, 0x82},
	{0x00, GEN_CMD, SW_PACK2, 0x02, 0xC4, 0x02},	//chopper function

	{0x00, GEN_CMD, SW_PACK2, 0x02, 0x00, 0xC6},
	{0x00, GEN_CMD, SW_PACK2, 0x02, 0xB0, 0x03},	//mpi debounce

	{0x00, GEN_CMD, SW_PACK2, 0x02, 0x00, 0x00},	//Gamma Seting  positive
	{0x00, GEN_CMD, LW_PACK, 0x13, 0x11, 0x00, 0xE1, 0x01, 0x0E, 0x14, 0x0e, 0x07, 0x10, 0x0B, 0x09, 0x06, 0x0A, 0x0D, 0x06, 0x0E, 0x12, 0x0C, 0x09},

	{0x00, GEN_CMD, SW_PACK2, 0x02, 0x00, 0x00},	//Gamma Seting  Nagitive
	{0x00, GEN_CMD, LW_PACK, 0x13, 0x11, 0x00, 0xE2, 0x09, 0x0E, 0x14, 0x0e, 0x07, 0x10, 0x0B, 0x09, 0x06, 0x0A, 0x0D, 0x06, 0x0E, 0x12, 0x0C, 0x01},

	{0x00, GEN_CMD, SW_PACK2, 0x02, 0x00, 0x00},	//control settings
	{0x00, GEN_CMD, SW_PACK2, 0x02, 0xD0, 0x40},

	{0x00, GEN_CMD, SW_PACK2, 0x02, 0x00, 0x00},
	{0x00, GEN_CMD, LW_PACK, 0x05, 0x03, 0x00, 0xD1, 0x00, 0x00},

	{0x00, GEN_CMD, SW_PACK2, 0x02, 0x00, 0x80},
	{0x00, GEN_CMD, LW_PACK, 0x0e, 0x0c, 0x00, 0xCB, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},

	{0x00, GEN_CMD, SW_PACK2, 0x02, 0x00, 0x90},
	{0x00, GEN_CMD, LW_PACK, 0x12, 0x10, 0x00, 0xCB, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},

	{0x00, GEN_CMD, SW_PACK2, 0x02, 0x00, 0xA0},
	{0x00, GEN_CMD, LW_PACK, 0x12, 0x10, 0x00, 0xCB, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},

	{0x00, GEN_CMD, SW_PACK2, 0x02, 0x00, 0xB0},
	{0x00, GEN_CMD, LW_PACK, 0x12, 0x10, 0x00, 0xCB, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},

	{0x00, GEN_CMD, SW_PACK2, 0x02, 0x00, 0xC0},
	{0x00, GEN_CMD, LW_PACK, 0x12, 0x10, 0x00, 0xCB, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},

	{0x00, GEN_CMD, SW_PACK2, 0x02, 0x00, 0xD0},
	{0x00, GEN_CMD, LW_PACK, 0x12, 0x10, 0x00, 0xCB, 0x00, 0x00, 0x00, 0x05, 0x05, 0x00, 0x00, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x00, 0x00},

	{0x00, GEN_CMD, SW_PACK2, 0x02, 0x00, 0xE0},
	{0x00, GEN_CMD, LW_PACK, 0x11, 0x0F, 0x00, 0xCB, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x05, 0x05, 0x00, 0x00},

	{0x00, GEN_CMD, SW_PACK2, 0x02, 0x00, 0xF0},
	{0x00, GEN_CMD, LW_PACK, 0x0E, 0x0C, 0x00, 0xCB, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF},

	{0x00, GEN_CMD, SW_PACK2, 0x02, 0x00, 0x80},	//Panel pad mapping control
	{0x00, GEN_CMD, LW_PACK, 0x12, 0x10, 0x00, 0xCC, 0x07, 0x05, 0x0F, 0x0D, 0x0B, 0x09, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},

	{0x00, GEN_CMD, SW_PACK2, 0x02, 0x00, 0x90},
	{0x00, GEN_CMD, LW_PACK, 0x12, 0x10, 0x00, 0xCC, 0x00, 0x00, 0x00, 0x01, 0x03, 0x00, 0x00, 0x08, 0x06, 0x10, 0x0E, 0x0C, 0x0A, 0x00, 0x00},

	{0x00, GEN_CMD, SW_PACK2, 0x02, 0x00, 0xA0},
	{0x00, GEN_CMD, LW_PACK, 0x11, 0x0F, 0x00, 0xCC, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x04, 0x00, 0x00},

	{0x00, GEN_CMD, SW_PACK2, 0x02, 0x00, 0xB0},
	{0x00, GEN_CMD, LW_PACK, 0x12, 0x10, 0x00, 0xCC, 0x02, 0x04, 0x0E, 0x10, 0x0A, 0x0C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},

	{0x00, GEN_CMD, SW_PACK2, 0x02, 0x00, 0xC0},
	{0x00, GEN_CMD, LW_PACK, 0x12, 0x10, 0x00, 0xCC, 0x00, 0x00, 0x00, 0x08, 0x06, 0x00, 0x00, 0x01, 0x03, 0x0D, 0x0F, 0x09, 0x0B, 0x00, 0x00},

	{0x00, GEN_CMD, SW_PACK2, 0x02, 0x00, 0xD0},
	{0x00, GEN_CMD, LW_PACK, 0x11, 0x0F, 0x00, 0xCC,0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x05, 0x00, 0x00},

	{0x00, GEN_CMD, SW_PACK2, 0x02, 0x00, 0x80},
	{0x00, GEN_CMD, LW_PACK, 0x0F, 0x0D, 0x00, 0xCE, 0x87, 0x03, 0x10, 0x86, 0x03, 0x10, 0x85, 0x03, 0x10, 0x84, 0x03, 0x10},

	{0x00, GEN_CMD, SW_PACK2, 0x02, 0x00, 0x90},
	{0x00, GEN_CMD, LW_PACK, 0x0F, 0x0D, 0x00, 0xCE, 0x34, 0xFC, 0x10, 0x34, 0xFD, 0x10, 0x34, 0xFE, 0x10, 0x34, 0xFF, 0x10},

	{0x00, GEN_CMD, SW_PACK2, 0x02, 0x00, 0xA0},
	{0x00, GEN_CMD, LW_PACK, 0x11, 0x0F, 0x00, 0xCE, 0x38, 0x05, 0x04, 0xFD, 0x00, 0x10, 0x00, 0x38, 0x04, 0x04, 0xFE, 0x00, 0x10, 0x00},

	{0x00, GEN_CMD, SW_PACK2, 0x02, 0x00, 0xB0},
	{0x00, GEN_CMD, LW_PACK, 0x11, 0x0F, 0x00, 0xCE, 0x38, 0x03, 0x04, 0xFF, 0x00, 0x10, 0x00, 0x38, 0x02, 0x05, 0x00, 0x00, 0x10, 0x00},

	{0x00, GEN_CMD, SW_PACK2, 0x02, 0x00, 0xC0},
	{0x00, GEN_CMD, LW_PACK, 0x11, 0x0F, 0x00, 0xCE, 0x38, 0x01, 0x05, 0x01, 0x00, 0x10, 0x00, 0x38, 0x00, 0x05, 0x02, 0x00, 0x10, 0x00},

	{0x00, GEN_CMD, SW_PACK2, 0x02, 0x00, 0xD0},
	{0x00, GEN_CMD, LW_PACK, 0x11, 0x0F, 0x00, 0xCE, 0x30, 0x00, 0x05, 0x03, 0x00, 0x10, 0x00, 0x30, 0x01, 0x05, 0x04, 0x00, 0x10, 0x00},

	{0x00, GEN_CMD, SW_PACK2, 0x02, 0x00, 0x80},
	{0x00, GEN_CMD, LW_PACK, 0x11, 0x0F, 0x00, 0xCF, 0x30, 0x02, 0x05, 0x05, 0x00, 0x10, 0x00, 0x30, 0x03, 0x05, 0x06, 0x00, 0x10, 0x00},

	{0x00, GEN_CMD, SW_PACK2, 0x02, 0x00, 0x90},
	{0x00, GEN_CMD, LW_PACK, 0x11, 0x0F, 0x00, 0xCF, 0x30, 0x04, 0x05, 0x07, 0x00, 0x10, 0x00, 0x30, 0x05, 0x05, 0x08, 0x00, 0x10, 0x00},

	{0x00, GEN_CMD, SW_PACK2, 0x02, 0x00, 0xA0},
	{0x00, GEN_CMD, LW_PACK, 0x11, 0x0F, 0x00, 0xCF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},

	{0x00, GEN_CMD, SW_PACK2, 0x02, 0x00, 0xB0},
	{0x00, GEN_CMD, LW_PACK, 0x11, 0x0F, 0x00, 0xCF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},

	{0x00, GEN_CMD, SW_PACK2, 0x02, 0x00, 0xC0},
	{0x00, GEN_CMD, LW_PACK, 0x0E, 0x0C, 0x00, 0xCF, 0x01, 0x01, 0x20, 0x20, 0x00, 0x00, 0x01, 0x82, 0x01, 0x10, 0x10},

	{0x00, GEN_CMD, SW_PACK2, 0x02, 0x00, 0xB5},
	{0x00, GEN_CMD, LW_PACK, 0x09, 0x07, 0x00, 0xC5, 0x0C, 0x01, 0xFF, 0x0C, 0x01, 0xFF},

	{0x00, GEN_CMD, SW_PACK2, 0x02, 0x00, 0x90},
	{0x00, GEN_CMD, LW_PACK, 0x07, 0x05, 0x00, 0xF5, 0x02, 0x11, 0x02, 0x11},	// power IC setting

	{0x00, GEN_CMD, SW_PACK2, 0x02, 0x00, 0x90},
	{0x00, GEN_CMD, SW_PACK2, 0x02, 0xC5, 0x50},	//external power ic mode

	{0x00, GEN_CMD, SW_PACK2, 0x02, 0x00, 0x94},
	{0x00, GEN_CMD, SW_PACK2, 0x02, 0xC5, 0x66},	//  pump1/pump2 set pump clock ratio 110:1/8 line

	{0x00, GEN_CMD, SW_PACK2, 0x02, 0x00, 0xB2},
	{0x00, GEN_CMD, LW_PACK, 0x05, 0x03, 0x00, 0xF5, 0x00, 0x00},	//VGLO1/VGL02 disable

	{0x00, GEN_CMD, SW_PACK2, 0x02, 0x00, 0xB4},
	{0x00, GEN_CMD, LW_PACK, 0x05, 0x03, 0x00, 0xF5, 0x00, 0x00},	

	{0x00, GEN_CMD, SW_PACK2, 0x02, 0x00, 0xB6},
	{0x00, GEN_CMD, LW_PACK, 0x05, 0x03, 0x00, 0xF5, 0x00, 0x00},	

	{0x00, GEN_CMD, SW_PACK2, 0x02, 0x00, 0xB8},
	{0x00, GEN_CMD, LW_PACK, 0x05, 0x03, 0x00, 0xF5, 0x00, 0x00},	

	{0x00, GEN_CMD, SW_PACK2, 0x02, 0x00, 0x94},
	{0x00, GEN_CMD, SW_PACK2, 0x02, 0xF5, 0x02},	//VCL ON

	{0x00, GEN_CMD, SW_PACK2, 0x02, 0x00, 0xBA},
	{0x00, GEN_CMD, SW_PACK2, 0x02, 0xF5, 0x03},	//VSP ON

	{0x00, GEN_CMD, SW_PACK2, 0x02, 0x00, 0xB4},
	{0x00, GEN_CMD, SW_PACK2, 0x02, 0xC5, 0xC0},	//VGLO1/2 pull low settings



	{0x00, GEN_CMD, SW_PACK2, 0x02, 0x00, 0xA0},
	{0x00, GEN_CMD, SW_PACK2, 0x02, 0xC1, 0x00},

/*********************************************************************/
/*for VCOM drop bug*/
	{0x00, GEN_CMD, SW_PACK2, 0x02, 0x00, 0x80},	//
	{0x00, GEN_CMD, SW_PACK2, 0x02, 0xC4, 0x30},

	{0x00, GEN_CMD, SW_PACK2, 0x02, 0x00, 0x8B},	//
	{0x00, GEN_CMD, SW_PACK2, 0x02, 0xC4, 0x00},

	{0x00, GEN_CMD, SW_PACK2, 0x02, 0x00, 0x90},	////clock delay for data latch 0x49->0x52
	{0x00, GEN_CMD, SW_PACK2, 0x02, 0xC4, 0x52},

	{0x00, GEN_CMD, SW_PACK2, 0x02, 0x00, 0xB9},	//Speed Up 
	{0x00, GEN_CMD, SW_PACK2, 0x02, 0xB0, 0x51},

	{0x00, GEN_CMD, SW_PACK2, 0x02, 0x00, 0x82},	//chopper 
	{0x00, GEN_CMD, SW_PACK2, 0x02, 0xC4, 0x02},

	{0x00, GEN_CMD, SW_PACK2, 0x02, 0x00, 0xB0},	//VDD_18V adjust
	{0x00, GEN_CMD, LW_PACK, 0x05, 0x03, 0x00, 0xC5,0x04,0x38},

	{0x00, GEN_CMD, SW_PACK2, 0x02, 0x00, 0x94},	//VCL on
	{0x00, GEN_CMD, SW_PACK2, 0x02, 0xF5, 0x02},

	{0x00, GEN_CMD, SW_PACK2, 0x02, 0x00, 0xBA},	//VSP on
	{0x00, GEN_CMD, SW_PACK2, 0x02, 0xF5, 0x03},

	{0x00, GEN_CMD, SW_PACK2, 0x02, 0x00, 0xc6},	//Read Debounce
	{0x00, GEN_CMD, SW_PACK2, 0x02, 0xb0, 0x03},

	{0x00, GEN_CMD, SW_PACK2, 0x02, 0x00, 0xA0},	//Time out off 
	{0x00, GEN_CMD, SW_PACK2, 0x02, 0xC1, 0x02},

	{0x00, GEN_CMD, SW_PACK2, 0x02, 0x00, 0xc3},	//Sample hold all on
	{0x00, GEN_CMD, SW_PACK2, 0x02, 0xf5, 0x81},

	{0x00, GEN_CMD, SW_PACK2, 0x02, 0x00, 0xB1},
	{0x00, GEN_CMD, SW_PACK2, 0x02, 0xc6, 0x05},
/************************************************************************/

	{0x00, GEN_CMD, SW_PACK2, 0x02, 0x00, 0x00},
	{0x00, GEN_CMD, LW_PACK, 0x06, 0x04, 0x00, 0xFF, 0xFF, 0xFF, 0xFF},	

	//{0x00,DCS_CMD, SW_PACK1, 0x01, 0x35},//TE On
	{0x00,DCS_CMD, SW_PACK2, 0x02, 0x35, 0x00},//TE On
	{0x78,DCS_CMD, SW_PACK1, 0x01, 0x11},
	{0x0A,DCS_CMD, SW_PACK1, 0x01, 0x29},
 };
static struct common_id_info lcd_common_id_info[] = {
	{DCS_CMD, {0x40}, 1, 0xDA},
};
static struct common_id_info lcd_common_esd_info[] = {
	{DCS_CMD, {0x40}, 1, 0xDA},
};

static int lcd_ivo_otm1283a_power(struct comipfb_info *fbi, int onoff)
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
		mdelay(10);
		pmic_voltage_set(PMIC_POWER_LCD_CORE, 0, PMIC_POWER_VOLTAGE_ENABLE);
		mdelay(10);
		gpio_direction_output(gpio_rst, 1);
		mdelay(1);
		gpio_direction_output(gpio_rst, 0);
		mdelay(50);
		gpio_direction_output(gpio_rst, 1);
		mdelay(100);
	} else {
		pmic_voltage_set(PMIC_POWER_LCD_CORE, 0, PMIC_POWER_VOLTAGE_DISABLE);
		pmic_voltage_set(PMIC_POWER_LCD_IO, 0, PMIC_POWER_VOLTAGE_DISABLE);
		gpio_direction_output(gpio_rst, 0);
		mdelay(10);
	}

	gpio_free(gpio_rst);

	return 0;
}

static int lcd_ivo_otm1283a_reset(struct comipfb_info *fbi)
{
	int gpio_rst = fbi->pdata->gpio_rst;

	if (gpio_rst >= 0) {
		gpio_request(gpio_rst, "LCD Reset");
		gpio_direction_output(gpio_rst, 1);
		mdelay(1);
		gpio_direction_output(gpio_rst, 0);
		mdelay(50);
		gpio_direction_output(gpio_rst, 1);
		mdelay(5);
		gpio_free(gpio_rst);
	}

	return 0;
}

static int lcd_ivo_otm1283a_suspend(struct comipfb_info *fbi)
{
	int ret=0;
	struct comipfb_dev_timing_mipi *mipi;

	mipi = &(fbi->cdev->timing.mipi);

	if (mipi->display_mode == MIPI_VIDEO_MODE) {
		mipi_dsih_hal_mode_config(fbi, 1);
	}

	//if (!(fbi->pdata->flags & COMIPFB_SLEEP_POWEROFF))
		ret = comipfb_if_mipi_dev_cmds(fbi, &fbi->cdev->cmds_suspend);
	msleep(20);
	mipi_dsih_dphy_enable_hs_clk(fbi, 0);
	if(fbi->cdev->reset)
		fbi->cdev->reset(fbi);

	mipi_dsih_dphy_reset(fbi, 0);
	mipi_dsih_dphy_shutdown(fbi, 0);
	
	return ret;
}

static int lcd_ivo_otm1283a_resume(struct comipfb_info *fbi)
{
	int ret=0;
	struct comipfb_dev_timing_mipi *mipi;

	mipi = &(fbi->cdev->timing.mipi);

	mipi_dsih_dphy_shutdown(fbi, 1);
	mipi_dsih_dphy_reset(fbi, 1);

	//if (fbi->cdev->reset)
	//	fbi->cdev->reset(fbi);

	ret = comipfb_if_mipi_dev_cmds(fbi, &fbi->cdev->cmds_resume);

	msleep(20);
	if (mipi->display_mode == MIPI_VIDEO_MODE) {
		mipi_dsih_hal_mode_config(fbi, 0);
	}
	mipi_dsih_dphy_enable_hs_clk(fbi, 1);
	
	return ret;
}

struct comipfb_dev lcd_ivo_otm1283a_dev = {
	.name = "lcd_ivo_otm1283a",
	.interface_info = COMIPFB_MIPI_IF,
	.lcd_id = LCD_ID_IVO_OTM1283A,
	.refresh_en = 1,
	.bpp = 32,
	.xres = 720,
	.yres = 1280,
	.flags = 0,
	.pclk = 60000000,//52000000
	.timing = {
		.mipi = {
			.hs_freq = 52000,//39000,		//Kbyte
			.lp_freq = 13000,		//KHZ
			.no_lanes = 4,
			.display_mode = MIPI_VIDEO_MODE,
			.im_pin_val = 1,
			.color_mode = {
				.color_bits = COLOR_CODE_24BIT,
			},
			.videomode_info = {
				.hsync = 8,
				.hbp = 48,
				.hfp = 52,
				.vsync = 6,
				.vbp = 15,
				.vfp = 16,
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
	.panel_id_info = {
		.id_info = lcd_common_id_info,
		.num_id_info = 1,
	},
	.cmds_init = {ARRAY_AND_SIZE(lcd_cmds_init)},
	.cmds_suspend = {ARRAY_AND_SIZE(lcd_cmds_suspend)},
	.cmds_resume = {ARRAY_AND_SIZE(lcd_cmds_resume)},
	.power = lcd_ivo_otm1283a_power,
	.reset = lcd_ivo_otm1283a_reset,
	.suspend = lcd_ivo_otm1283a_suspend,
	.resume = lcd_ivo_otm1283a_resume,
#ifdef CONFIG_FB_COMIP_ESD
	.esd_id_info = {
		.id_info = lcd_common_esd_info,
		.num_id_info = 1,
	},
#endif

	.backlight_info = {
			{ARRAY_AND_SIZE(backlight_cmds)},
		.brightness_bit = 8,
	},
};

static int __init lcd_ivo_otm1283a_init(void)
{
  return comipfb_dev_register(&lcd_ivo_otm1283a_dev);
}

subsys_initcall(lcd_ivo_otm1283a_init);
