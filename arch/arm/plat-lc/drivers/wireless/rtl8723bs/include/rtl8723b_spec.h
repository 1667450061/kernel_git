/******************************************************************************
 *
 * Copyright(c) 2007 - 2011 Realtek Corporation. All rights reserved.
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of version 2 of the GNU General Public License as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110, USA
 *
 *******************************************************************************/
#ifndef __RTL8723B_SPEC_H__
#define __RTL8723B_SPEC_H__

#include <drv_conf.h>

#ifndef BIT
#define BIT(x)		(1 << (x))
#endif

#define BIT0		0x00000001
#define BIT1		0x00000002
#define BIT2		0x00000004
#define BIT3		0x00000008
#define BIT4		0x00000010
#define BIT5		0x00000020
#define BIT6		0x00000040
#define BIT7		0x00000080
#define BIT8		0x00000100
#define BIT9		0x00000200
#define BIT10	0x00000400
#define BIT11	0x00000800
#define BIT12	0x00001000
#define BIT13	0x00002000
#define BIT14	0x00004000
#define BIT15	0x00008000
#define BIT16	0x00010000
#define BIT17	0x00020000
#define BIT18	0x00040000
#define BIT19	0x00080000
#define BIT20	0x00100000
#define BIT21	0x00200000
#define BIT22	0x00400000
#define BIT23	0x00800000
#define BIT24	0x01000000
#define BIT25	0x02000000
#define BIT26	0x04000000
#define BIT27	0x08000000
#define BIT28	0x10000000
#define BIT29	0x20000000
#define BIT30	0x40000000
#define BIT31	0x80000000

//============================================================
//       8192C Regsiter offset definition
//============================================================

#define		HAL_PS_TIMER_INT_DELAY	50		//  50 microseconds
#define		HAL_92C_NAV_UPPER_UNIT	128		// micro-second

#define MAC_ADDR_LEN					6
// 8188E PKT_BUFF_ACCESS_CTRL value
#define TXPKT_BUF_SELECT				0x69
#define RXPKT_BUF_SELECT				0xA5
#define DISABLE_TRXPKT_BUF_ACCESS	0x0

#define HAL_8723B_NAV_UPPER_UNIT		128		// micro-second

//-----------------------------------------------------
//
//	0x0000h ~ 0x00FFh	System Configuration
//
//-----------------------------------------------------
#define REG_SYS_ISO_CTRL			0x0000
#define REG_SYS_FUNC_EN			0x0002
#define REG_APS_FSMCO				0x0004
#define REG_SYS_CLKR				0x0008
#define REG_9346CR					0x000A
#define REG_EE_VPD					0x000C
#define REG_AFE_MISC				0x0010
#define REG_SPS0_CTRL				0x0011
#define REG_SPS_OCP_CFG			0x0018
#define REG_RSV_CTRL				0x001C
#define REG_RF_CTRL					0x001F
#define REG_LDOA15_CTRL			0x0020
#define REG_LDOV12D_CTRL			0x0021
#define REG_LDOHCI12_CTRL			0x0022
#define REG_LPLDO_CTRL				0x0023
#define REG_AFE_XTAL_CTRL			0x0024
#define REG_AFE_PLL_CTRL			0x0028
#define REG_MAC_PHY_CTRL			0x002c //for 92d, DMDP,SMSP,DMSP contrl
#define REG_EFUSE_CTRL				0x0030
#define REG_EFUSE_TEST				0x0034
#define REG_BT_WIFI_ANTENNA_SWITCH_8723B	0x0038
#define REG_CAL_TIMER				0x003C
#define REG_ACLK_MON				0x003E
#define REG_GPIO_MUXCFG			0x0040
#define REG_GPIO_IO_SEL				0x0042
#define REG_MAC_PINMUX_CFG		0x0043
#define REG_GPIO_PIN_CTRL			0x0044
#define REG_GPIO_INTM				0x0048
#define REG_LEDCFG0					0x004C
#define REG_LEDCFG1					0x004D
#define REG_LEDCFG2					0x004E
#define REG_LEDCFG3					0x004F
#define REG_LEDCFG					REG_LEDCFG2
#define REG_FSIMR					0x0050
#define REG_FSISR					0x0054
#define REG_HSIMR					0x0058
#define REG_HSISR					0x005c
#define REG_GPIO_PIN_CTRL_2		0x0060 // RTL8723 WIFI/BT/GPS Multi-Function GPIO Pin Control.
#define REG_GPIO_IO_SEL_2			0x0062 // RTL8723 WIFI/BT/GPS Multi-Function GPIO Select.
#define REG_PAD_CTRL1_8723B		0x0064
#define REG_MULTI_FUNC_CTRL		0x0068 // RTL8723 WIFI/BT/GPS Multi-Function control source.
#define REG_AFE_CTRL_4_8723B		0x0078
#define REG_MCUFWDL				0x0080
#define REG_HMEBOX_DBG_1_8723B	0x008A
#define REG_HMEBOX_DBG_2_8723B	0x008C
#define REG_HMEBOX_DBG_3_8723B	0x008E
#define REG_HOST_SUSP_CNT			0x00BC	// Host suspend counter on FPGA platform
#define REG_EFUSE_ACCESS			0x00CF	// Efuse access protection for RTL8723
#define REG_BIST_SCAN				0x00D0
#define REG_BIST_RPT				0x00D4
#define REG_BIST_ROM_RPT			0x00D8
#define REG_USB_SIE_INTF			0x00E0
#define REG_PCIE_MIO_INTF			0x00E4
#define REG_PCIE_MIO_INTD			0x00E8
#define REG_HPON_FSM				0x00EC
#define REG_SYS_CFG					0x00F0
#define REG_GPIO_OUTSTS			0x00F4	// For RTL8723 only.
#define REG_TYPE_ID					0x00FC

//-----------------------------------------------------
//
//	0x0100h ~ 0x01FFh	MACTOP General Configuration
//
//-----------------------------------------------------
#define REG_CR						0x0100
#define REG_PBP						0x0104
#define REG_TRXDMA_CTRL			0x010C
#define REG_TRXFF_BNDY				0x0114
#define REG_TRXFF_STATUS			0x0118
#define REG_RXFF_PTR				0x011C
#define REG_HIMR					0x0120
#define REG_HISR					0x0124
#define REG_HIMRE					0x0128
#define REG_HISRE					0x012C
#define REG_CPWM					0x012F
#define REG_FWIMR					0x0130
#define REG_FWISR					0x0134
#define REG_FTIMR			0x0138
#define REG_PKTBUF_DBG_CTRL		0x0140
#define REG_PKTBUF_DBG_DATA_L		0x0144
#define REG_PKTBUF_DBG_DATA_H	0x0148

#define REG_TC0_CTRL				0x0150
#define REG_TC1_CTRL				0x0154
#define REG_TC2_CTRL				0x0158
#define REG_TC3_CTRL				0x015C
#define REG_TC4_CTRL				0x0160
#define REG_TCUNIT_BASE			0x0164
#define REG_MBIST_START			0x0174
#define REG_MBIST_DONE				0x0178
#define REG_MBIST_FAIL				0x017C
#define REG_C2HEVT_CMD_ID_8723B	0x01A0
#define REG_C2HEVT_CMD_LEN_8723B	0x01AE
#define REG_C2HEVT_CLEAR			0x01AF
#define REG_C2HEVT_MSG_TEST		0x01B8
#define REG_MCUTST_1				0x01c0
#define REG_WOWLAN_WAKE_REASON_8723B 0x01C7
#define REG_FMETHR					0x01C8
#define REG_HMETFR					0x01CC
#define REG_HMEBOX_0				0x01D0
#define REG_HMEBOX_1				0x01D4
#define REG_HMEBOX_2				0x01D8
#define REG_HMEBOX_3				0x01DC

#define REG_LLT_INIT				0x01E0
#define REG_BB_ACCEESS_CTRL		0x01E8
#define REG_BB_ACCESS_DATA		0x01EC

#define REG_HMEBOX_EXT0_8723B			0x01F0
#define REG_HMEBOX_EXT1_8723B			0x01F4
#define REG_HMEBOX_EXT2_8723B			0x01F8
#define REG_HMEBOX_EXT3_8723B			0x01FC

//-----------------------------------------------------
//
//	0x0200h ~ 0x027Fh	TXDMA Configuration
//
//-----------------------------------------------------
#define REG_RQPN					0x0200
#define REG_FIFOPAGE				0x0204
#define REG_TDECTRL					0x0208
#define REG_TXDMA_OFFSET_CHK		0x020C
#define REG_TXDMA_STATUS			0x0210
#define REG_RQPN_NPQ				0x0214
#define REG_TDECTRL1				0x0228


//-----------------------------------------------------
//
//	0x0280h ~ 0x02FFh	RXDMA Configuration
//
//-----------------------------------------------------
#define REG_RXDMA_AGG_PG_TH		0x0280
#define REG_RXPKT_NUM				0x0284
#define REG_RXDMA_STATUS			0x0288
#define REG_RXDMA_MODE_CTRL		0x0290


//-----------------------------------------------------
//
//	0x0300h ~ 0x03FFh	PCIe
//
//-----------------------------------------------------
#define	REG_PCIE_CTRL_REG			0x0300
#define	REG_INT_MIG				0x0304	// Interrupt Migration
#define	REG_BCNQ_DESA				0x0308	// TX Beacon Descriptor Address
#define	REG_HQ_DESA				0x0310	// TX High Queue Descriptor Address
#define	REG_MGQ_DESA				0x0318	// TX Manage Queue Descriptor Address
#define	REG_VOQ_DESA				0x0320	// TX VO Queue Descriptor Address
#define	REG_VIQ_DESA				0x0328	// TX VI Queue Descriptor Address
#define	REG_BEQ_DESA				0x0330	// TX BE Queue Descriptor Address
#define	REG_BKQ_DESA				0x0338	// TX BK Queue Descriptor Address
#define	REG_RX_DESA				0x0340	// RX Queue	Descriptor Address
#define	REG_DBI					0x0348	// Backdoor REG for Access Configuration
#define	REG_MDIO					0x0354	// MDIO for Access PCIE PHY
#define	REG_DBG_SEL				0x0360	// Debug Selection Register
#define	REG_PCIE_HRPWM			0x0361	//PCIe RPWM
#define	REG_PCIE_HCPWM			0x0363	//PCIe CPWM
#define	REG_UART_CTRL				0x0364	// UART	Control
#define	REG_UART_TX_DESA			0x0370	// UART TX Descriptor Address
#define	REG_UART_RX_DESA			0x0378	// UART Rx Descriptor Address


// spec version 11
//-----------------------------------------------------
//
//	0x0400h ~ 0x047Fh	Protocol Configuration
//
//-----------------------------------------------------
#define REG_VOQ_INFORMATION			0x0400
#define REG_VIQ_INFORMATION			0x0404
#define REG_BEQ_INFORMATION			0x0408
#define REG_BKQ_INFORMATION			0x040C
#define REG_MGQ_INFORMATION			0x0410
#define REG_HGQ_INFORMATION			0x0414
#define REG_BCNQ_INFORMATION			0x0418
#define REG_TXPKT_EMPTY 			0x041A


#define REG_CPU_MGQ_INFORMATION		0x041C
#define REG_FWHW_TXQ_CTRL				0x0420
#define REG_HWSEQ_CTRL					0x0423
#define REG_TXPKTBUF_BCNQ_BDNY		0x0424
#define REG_TXPKTBUF_MGQ_BDNY		0x0425
#define REG_LIFETIME_EN				0x0426
#define REG_MULTI_BCNQ_OFFSET			0x0427
#define REG_SPEC_SIFS					0x0428
#define REG_RL							0x042A
#define REG_DARFRC						0x0430
#define REG_RARFRC						0x0438
#define REG_RRSR						0x0440

#define REG_ARFR0						0x0444
#define REG_ARFR1						0x044C
#define REG_BCNQ1_BDNY					0x0457
#define REG_ARFR2						0x048C
#define REG_ARFR3						0x0494
#define REG_ARFR4						0x049C
#define REG_ARFR5						0x04A4

#define REG_AGGLEN_LMT					0x0458
#define REG_AMPDU_MIN_SPACE			0x045C
#define REG_TXPKTBUF_WMAC_LBK_BF_HD	0x045D
#define REG_FAST_EDCA_CTRL				0x0460
#define REG_RD_RESP_PKT_TH				0x0463
#define REG_INIRTS_RATE_SEL			0x0480
#define REG_DATA_SC_8723B			0x0483

#define REG_INIDATA_RATE_SEL			0x0484


#define REG_HMEBOX_DBG_0_8723B	0x049D
#define REG_POWER_STATUS				0x04A4
#define REG_POWER_STAGE1				0x04B4
#define REG_POWER_STAGE2				0x04B8
#define REG_PKT_VO_VI_LIFE_TIME		0x04C0
#define REG_PKT_BE_BK_LIFE_TIME		0x04C2
#define REG_STBC_SETTING				0x04C4
#define REG_PROT_MODE_CTRL			0x04C8
#define REG_MAX_AGGR_NUM				0x04CA
#define REG_RTS_MAX_AGGR_NUM			0x04CB
#define REG_BAR_MODE_CTRL				0x04CC
#define REG_RA_TRY_RATE_AGG_LMT		0x04CF
#define REG_EARLY_MODE_CONTROL		0x04D0
#define REG_NQOS_SEQ					0x04DC
#define REG_QOS_SEQ					0x04DE
#define REG_NEED_CPU_HANDLE			0x04E0
#define REG_PKT_LOSE_RPT				0x04E1
#define REG_PTCL_ERR_STATUS			0x04E2
#define REG_DUMMY						0x04FC



//-----------------------------------------------------
//
//	0x0500h ~ 0x05FFh	EDCA Configuration
//
//-----------------------------------------------------
#define REG_EDCA_VO_PARAM			0x0500
#define REG_EDCA_VI_PARAM			0x0504
#define REG_EDCA_BE_PARAM			0x0508
#define REG_EDCA_BK_PARAM			0x050C
#define REG_BCNTCFG					0x0510
#define REG_PIFS						0x0512
#define REG_RDG_PIFS				0x0513
#define REG_SIFS_CCK				0x0514
#define REG_SIFS_OFDM				0x0516
#define REG_SIFS_CTX				0x0514
#define REG_SIFS_TRX				0x0516
#define REG_TSFTR_SYN_OFFSET		0x0518
#define REG_AGGR_BREAK_TIME		0x051A
#define REG_SLOT					0x051B
#define REG_TX_PTCL_CTRL			0x0520
#define REG_TXPAUSE					0x0522
#define REG_DIS_TXREQ_CLR			0x0523
#define REG_RD_CTRL					0x0524
#define REG_TBTT_PROHIBIT			0x0540
#define REG_RD_NAV_NXT				0x0544
#define REG_NAV_PROT_LEN			0x0546
#define REG_BCN_CTRL				0x0550
#define REG_BCN_CTRL_1				0x0551
#define REG_MBID_NUM				0x0552
#define REG_DUAL_TSF_RST			0x0553
#define REG_BCN_INTERVAL			0x0554	// The same as REG_MBSSID_BCN_SPACE
#define REG_MBSSID_BCN_SPACE		0x0554
#define REG_DRVERLYINT				0x0558
#define REG_BCNDMATIM				0x0559
#define REG_ATIMWND				0x055A
#define REG_BCN_MAX_ERR			0x055D
#define REG_RXTSF_OFFSET_CCK		0x055E
#define REG_RXTSF_OFFSET_OFDM		0x055F
#define REG_TSFTR					0x0560
#define REG_TSFTR1					0x0568
#define REG_INIT_TSFTR				0x0564
#define REG_ATIMWND_1				0x0570
#define REG_SECONDARY_CCA_CTRL_8723B	0x0577
#define REG_PSTIMER					0x0580
#define REG_TIMER0					0x0584
#define REG_TIMER1					0x0588
#define REG_ACMHWCTRL				0x05C0
#define REG_ACMRSTCTRL				0x05C1
#define REG_ACMAVG					0x05C2
#define REG_VO_ADMTIME				0x05C4
#define REG_VI_ADMTIME				0x05C6
#define REG_BE_ADMTIME				0x05C8
#define REG_EDCA_RANDOM_GEN		0x05CC
#define REG_SCH_TXCMD				0x05D0

//#define REG_FW_TSF_SYNC_CNT				0x04A0
#define REG_FW_RESET_TSF_CNT_1				0x05FC
#define REG_FW_RESET_TSF_CNT_0				0x05FD
#define REG_FW_BCN_DIS_CNT				0x05FE

//-----------------------------------------------------
//
//	0x0600h ~ 0x07FFh	WMAC Configuration
//
//-----------------------------------------------------
#define REG_APSD_CTRL				0x0600
#define REG_BWOPMODE				0x0603
#define REG_TCR						0x0604
#define REG_RCR						0x0608
#define REG_RX_PKT_LIMIT			0x060C
#define REG_RX_DLK_TIME			0x060D
#define REG_RX_DRVINFO_SZ			0x060F

#define REG_MACID					0x0610
#define REG_BSSID					0x0618
#define REG_MAR						0x0620
#define REG_MBIDCAMCFG				0x0628

#define REG_USTIME_EDCA			0x0638
#define REG_MAC_SPEC_SIFS			0x063A

// 20100719 Joseph: Hardware register definition change. (HW datasheet v54)
#define REG_R2T_SIFS				0x063C	// [15:8]SIFS_R2T_OFDM, [7:0]SIFS_R2T_CCK
#define REG_T2T_SIFS				0x063E	// [15:8]SIFS_T2T_OFDM, [7:0]SIFS_T2T_CCK
#define REG_ACKTO					0x0640
#define REG_CTS2TO					0x0641
#define REG_EIFS						0x0642

//WMA, BA, CCX
#define REG_NAV_CTRL				0x0650
#define REG_NAV_UPPER				0x0652	// unit of 128
#define REG_BACAMCMD				0x0654
#define REG_BACAMCONTENT			0x0658
#define REG_LBDLY					0x0660
#define REG_FWDLY					0x0661
#define REG_RXERR_RPT				0x0664
#define REG_WMAC_TRXPTCL_CTL		0x0668

// Security
#define REG_CAMCMD					0x0670
#define REG_CAMWRITE				0x0674
#define REG_CAMREAD				0x0678
#define REG_CAMDBG					0x067C
#define REG_SECCFG					0x0680

// Power
#define REG_WOW_CTRL				0x0690
#define REG_PSSTATUS				0x0691
#define REG_PS_RX_INFO				0x0692
#define REG_LPNAV_CTRL				0x0694
#define REG_WKFMCAM_CMD			0x0698
#define REG_WKFMCAM_RWD			0x069C
#define REG_RXFLTMAP0				0x06A0
#define REG_RXFLTMAP1				0x06A2
#define REG_RXFLTMAP2				0x06A4
#define REG_BCN_PSR_RPT			0x06A8
#define REG_CALB32K_CTRL			0x06AC
#define REG_PKT_MON_CTRL			0x06B4
#define REG_BT_COEX_TABLE			0x06C0
#define REG_WMAC_RESP_TXINFO		0x06D8

#define REG_MACID1					0x0700
#define REG_BSSID1					0x0708


//YJ,TODO
#define	REG_RFE_INV_8723B			0x92C
#define 	REG_RFE_CTRL89_8723B		0x930

//
//-----------------------------------------------------
//
//	0xFE00h ~ 0xFE55h	USB Configuration
//
//-----------------------------------------------------
#define REG_USB_INFO					0xFE17
#define REG_USB_SPECIAL_OPTION			0xFE55
#define REG_USB_DMA_AGG_TO			0xFE5B
#define REG_USB_AGG_TO				0xFE5C
#define REG_USB_AGG_TH				0xFE5D


// For normal chip
#define REG_NORMAL_SIE_VID			0xFE60		// 0xFE60~0xFE61
#define REG_NORMAL_SIE_PID			0xFE62		// 0xFE62~0xFE63
#define REG_NORMAL_SIE_OPTIONAL		0xFE64
#define REG_NORMAL_SIE_EP				0xFE65		// 0xFE65~0xFE67
#define REG_NORMAL_SIE_PHY			0xFE68		// 0xFE68~0xFE6B
#define REG_NORMAL_SIE_OPTIONAL2		0xFE6C
#define REG_NORMAL_SIE_GPS_EP			0xFE6D	// 0xFE6D, for RTL8723 only.
#define REG_NORMAL_SIE_MAC_ADDR		0xFE70		// 0xFE70~0xFE75
#define REG_NORMAL_SIE_STRING			0xFE80		// 0xFE80~0xFEDF


//-----------------------------------------------------
//
//	Redifine 8192C register definition for compatibility
//
//-----------------------------------------------------

// TODO: use these definition when using REG_xxx naming rule.
// NOTE: DO NOT Remove these definition. Use later.

#define	EFUSE_CTRL					REG_EFUSE_CTRL		// E-Fuse Control.
#define	EFUSE_TEST					REG_EFUSE_TEST		// E-Fuse Test.
#define	MSR							(REG_CR + 2)		// Media Status register
#define	ISR							REG_HISR_88E
#define	TSFR						REG_TSFTR			// Timing Sync Function Timer Register.

#define 	PBP							REG_PBP

// Redifine MACID register, to compatible prior ICs.
#define	IDR0						REG_MACID			// MAC ID Register, Offset 0x0050-0x0053
#define	IDR4						(REG_MACID + 4)		// MAC ID Register, Offset 0x0054-0x0055


//
// 9. Security Control Registers	(Offset: )
//
#define	RWCAM						REG_CAMCMD		//IN 8190 Data Sheet is called CAMcmd
#define	WCAMI						REG_CAMWRITE	// Software write CAM input content
#define	RCAMO						REG_CAMREAD		// Software read/write CAM config
#define	CAMDBG						REG_CAMDBG
#define	SECR						REG_SECCFG		//Security Configuration Register

// Unused register
#define	UnusedRegister				0x1BF
#define	DCAM						UnusedRegister
#define	PSR							UnusedRegister
#define 	BBAddr						UnusedRegister
#define	PhyDataR					UnusedRegister

// Min Spacing related settings.
#define	MAX_MSS_DENSITY_2T 			0x13
#define	MAX_MSS_DENSITY_1T 			0x0A

//----------------------------------------------------------------------------
//       8192C Cmd9346CR bits					(Offset 0xA, 16bit)
//----------------------------------------------------------------------------
#define	CmdEEPROM_En				BIT5	 // EEPROM enable when set 1
#define	CmdEERPOMSEL				BIT4 	// System EEPROM select, 0: boot from E-FUSE, 1: The EEPROM used is 9346
#define	Cmd9346CR_9356SEL			BIT4

//----------------------------------------------------------------------------
//       8192C GPIO MUX Configuration Register (offset 0x40, 4 byte)
//----------------------------------------------------------------------------
#define	GPIOSEL_GPIO					0
#define	GPIOSEL_ENBT					BIT5

//----------------------------------------------------------------------------
//       8192C GPIO PIN Control Register (offset 0x44, 4 byte)
//----------------------------------------------------------------------------
#define	GPIO_IN						REG_GPIO_PIN_CTRL		// GPIO pins input value
#define	GPIO_OUT					(REG_GPIO_PIN_CTRL+1)	// GPIO pins output value
#define	GPIO_IO_SEL					(REG_GPIO_PIN_CTRL+2)	// GPIO pins output enable when a bit is set to "1"; otherwise, input is configured.
#define	GPIO_MOD					(REG_GPIO_PIN_CTRL+3)

//----------------------------------------------------------------------------
//       8723/8188E Host System Interrupt Mask Register (offset 0x58, 32 byte)
//----------------------------------------------------------------------------
#define	HSIMR_GPIO12_0_INT_EN		BIT0
#define	HSIMR_SPS_OCP_INT_EN		BIT5
#define	HSIMR_RON_INT_EN			BIT6
#define	HSIMR_PDN_INT_EN			BIT7
#define	HSIMR_GPIO9_INT_EN		BIT25


//----------------------------------------------------------------------------
//       8723/8188E Host System Interrupt Status Register (offset 0x5C, 32 byte)
//----------------------------------------------------------------------------
#define	HSISR_GPIO12_0_INT			BIT0
#define	HSISR_SPS_OCP_INT			BIT5
#define	HSISR_RON_INT			BIT6
#define	HSISR_PDNINT					BIT7
#define	HSISR_GPIO9_INT			BIT25

// interrupt mask which needs to clear
#define MASK_HSISR_CLEAR		(HSISR_GPIO12_0_INT |\
								HSISR_SPS_OCP_INT |\
								HSISR_RON_INT |\
								HSISR_PDNINT |\
								HSISR_GPIO9_INT)


//----------------------------------------------------------------------------
//       8192C (MSR) Media Status Register	(Offset 0x4C, 8 bits)
//----------------------------------------------------------------------------
/*
Network Type
00: No link
01: Link in ad hoc network
10: Link in infrastructure network
11: AP mode
Default: 00b.
*/
#define	MSR_NOLINK					0x00
#define	MSR_ADHOC					0x01
#define	MSR_INFRA					0x02
#define	MSR_AP						0x03

//----------------------------------------------------------------------------
//       88EU (MSR) Media Status Register	(Offset 0x4C, 8 bits)
//----------------------------------------------------------------------------
#define	USB_INTR_CONTENT_C2H_OFFSET		0
#define	USB_INTR_CONTENT_CPWM1_OFFSET	16
#define	USB_INTR_CONTENT_CPWM2_OFFSET	20
#define	USB_INTR_CONTENT_HISR_OFFSET		48
#define	USB_INTR_CONTENT_HISRE_OFFSET	52


//
// 6. Adaptive Control Registers  (Offset: 0x0160 - 0x01CF)
//
//----------------------------------------------------------------------------
//       8192C Response Rate Set Register	(offset 0x181, 24bits)
//----------------------------------------------------------------------------
#define	RRSR_1M						BIT0
#define	RRSR_2M						BIT1
#define	RRSR_5_5M					BIT2
#define	RRSR_11M					BIT3
#define	RRSR_6M						BIT4
#define	RRSR_9M						BIT5
#define	RRSR_12M					BIT6
#define	RRSR_18M					BIT7
#define	RRSR_24M					BIT8
#define	RRSR_36M					BIT9
#define	RRSR_48M					BIT10
#define	RRSR_54M					BIT11
#define	RRSR_MCS0					BIT12
#define	RRSR_MCS1					BIT13
#define	RRSR_MCS2					BIT14
#define	RRSR_MCS3					BIT15
#define	RRSR_MCS4					BIT16
#define	RRSR_MCS5					BIT17
#define	RRSR_MCS6					BIT18
#define	RRSR_MCS7					BIT19

//----------------------------------------------------------------------------
//       8192C Response Rate Set Register	(offset 0x1BF, 8bits)
//----------------------------------------------------------------------------
// WOL bit information
#define	HAL92C_WOL_PTK_UPDATE_EVENT		BIT0
#define	HAL92C_WOL_GTK_UPDATE_EVENT		BIT1

//----------------------------------------------------------------------------
//       8192C BW_OPMODE bits					(Offset 0x203, 8bit)
//----------------------------------------------------------------------------
#define	BW_OPMODE_20MHZ			BIT2
#define	BW_OPMODE_5G				BIT1


//----------------------------------------------------------------------------
//       8192C CAM Config Setting (offset 0x250, 1 byte)
//----------------------------------------------------------------------------
#define	CAM_VALID					BIT15
#define	CAM_NOTVALID				0x0000
#define	CAM_USEDK					BIT5

#define	CAM_CONTENT_COUNT 		8

#define	CAM_NONE					0x0
#define	CAM_WEP40					0x01
#define	CAM_TKIP					0x02
#define	CAM_AES					0x04
#define	CAM_WEP104				0x05
#define	CAM_SMS4					0x6

#define	TOTAL_CAM_ENTRY			32
#define	HALF_CAM_ENTRY			16

#define	CAM_CONFIG_USEDK			_TRUE
#define	CAM_CONFIG_NO_USEDK		_FALSE

#define	CAM_WRITE					BIT16
#define	CAM_READ					0x00000000
#define	CAM_POLLINIG				BIT31

#define	SCR_UseDK					0x01
#define	SCR_TxSecEnable			0x02
#define	SCR_RxSecEnable			0x04

//
// 10. Power Save Control Registers	 (Offset: 0x0260 - 0x02DF)
//
#define	WOW_PMEN				BIT0 // Power management Enable.
#define	WOW_WOMEN			BIT1 // WoW function on or off.
#define	WOW_MAGIC				BIT2 // Magic packet
#define	WOW_UWF				BIT3 // Unicast Wakeup frame.

	//----------------------------------------------------------------------------
	//		 8192C (TXPAUSE) transmission pause 	(Offset 0x522, 8 bits)
	//----------------------------------------------------------------------------
// Note:
//	The the bits of stoping AC(VO/VI/BE/BK) queue in datasheet RTL8192S/RTL8192C are wrong,
//	the correct arragement is VO - Bit0, VI - Bit1, BE - Bit2, and BK - Bit3.
//	8723 and 88E may be not correct either in the eralier version. Confirmed with DD Tim.
// By Bruce, 2011-09-22.
#define		StopBecon			BIT6
#define		StopHigh				BIT5
#define		StopMgt				BIT4
#define		StopBK				BIT3
#define		StopBE				BIT2
#define		StopVI				BIT1
#define		StopVO				BIT0

//----------------------------------------------------------------------------
//       8192C (RCR) Receive Configuration Register	(Offset 0x608, 32 bits)
//----------------------------------------------------------------------------
#define	RCR_APPFCS					BIT31		//WMAC append FCS after pauload
#define	RCR_APP_MIC				BIT30		//
#define	RCR_APP_PHYSTS			BIT28//
#define	RCR_APP_ICV				BIT29       //
#define	RCR_APP_PHYST_RXFF		BIT28       //
#define	RCR_APP_BA_SSN			BIT27		//Accept BA SSN
#define	RCR_ENMBID					BIT24		//Enable Multiple BssId.
#define	RCR_LSIGEN					BIT23
#define	RCR_MFBEN					BIT22
#define	RCR_HTC_LOC_CTRL			BIT14       //MFC<--HTC=1 MFC-->HTC=0
#define	RCR_AMF					BIT13		//Accept management type frame
#define	RCR_ACF					BIT12		//Accept control type frame
#define	RCR_ADF					BIT11		//Accept data type frame
#define	RCR_AICV					BIT9		//Accept ICV error packet
#define	RCR_ACRC32					BIT8		//Accept CRC32 error packet
#define	RCR_CBSSID_BCN			BIT7		//Accept BSSID match packet (Rx beacon, probe rsp)
#define	RCR_CBSSID_DATA			BIT6		//Accept BSSID match packet (Data)
#define	RCR_CBSSID					RCR_CBSSID_DATA		//Accept BSSID match packet
#define	RCR_APWRMGT				BIT5		//Accept power management packet
#define	RCR_ADD3					BIT4		//Accept address 3 match packet
#define	RCR_AB						BIT3		//Accept broadcast packet
#define	RCR_AM						BIT2		//Accept multicast packet
#define	RCR_APM					BIT1		//Accept physical match packet
#define	RCR_AAP					BIT0		//Accept all unicast packet
#define	RCR_MXDMA_OFFSET			8
#define	RCR_FIFO_OFFSET			13

//-----------------------------------------------------
//
//	0xFE00h ~ 0xFE55h	USB Configuration
//
//-----------------------------------------------------
#define REG_USB_INFO					0xFE17
#define REG_USB_SPECIAL_OPTION			0xFE55
#define REG_USB_DMA_AGG_TO			0xFE5B
#define REG_USB_AGG_TO				0xFE5C
#define REG_USB_AGG_TH				0xFE5D

#define REG_USB_HRPWM				0xFE58
#define REG_USB_HCPWM				0xFE57
//============================================================================
//	8723 Regsiter Bit and Content definition
//============================================================================

//-----------------------------------------------------
//
//	0x0000h ~ 0x00FFh	System Configuration
//
//-----------------------------------------------------

//2 SPS0_CTRL
#define SW18_FPWM					BIT(3)


//2 SYS_ISO_CTRL
#define ISO_MD2PP					BIT(0)
#define ISO_UA2USB					BIT(1)
#define ISO_UD2CORE					BIT(2)
#define ISO_PA2PCIE					BIT(3)
#define ISO_PD2CORE					BIT(4)
#define ISO_IP2MAC					BIT(5)
#define ISO_DIOP						BIT(6)
#define ISO_DIOE						BIT(7)
#define ISO_EB2CORE					BIT(8)
#define ISO_DIOR						BIT(9)

#define PWC_EV25V					BIT(14)
#define PWC_EV12V					BIT(15)


//2 SYS_FUNC_EN
#define FEN_BBRSTB					BIT(0)
#define FEN_BB_GLB_RSTn			BIT(1)
#define FEN_USBA					BIT(2)
#define FEN_UPLL					BIT(3)
#define FEN_USBD					BIT(4)
#define FEN_DIO_PCIE				BIT(5)
#define FEN_PCIEA					BIT(6)
#define FEN_PPLL						BIT(7)
#define FEN_PCIED					BIT(8)
#define FEN_DIOE					BIT(9)
#define FEN_CPUEN					BIT(10)
#define FEN_DCORE					BIT(11)
#define FEN_ELDR					BIT(12)
#define FEN_DIO_RF					BIT(13)
#define FEN_HWPDN					BIT(14)
#define FEN_MREGEN					BIT(15)

//2 APS_FSMCO
#define PFM_LDALL					BIT(0)
#define PFM_ALDN					BIT(1)
#define PFM_LDKP					BIT(2)
#define PFM_WOWL					BIT(3)
#define EnPDN						BIT(4)
#define PDN_PL						BIT(5)
#define APFM_ONMAC					BIT(8)
#define APFM_OFF					BIT(9)
#define APFM_RSM					BIT(10)
#define AFSM_HSUS					BIT(11)
#define AFSM_PCIE					BIT(12)
#define APDM_MAC					BIT(13)
#define APDM_HOST					BIT(14)
#define APDM_HPDN					BIT(15)
#define EN_WLON						BIT(16)
#define SUS_HOST					BIT(17)
#define ROP_ALD						BIT(20)
#define ROP_PWR						BIT(21)
#define ROP_SPS						BIT(22)
#define SOP_MRST					BIT(25)
#define SOP_FUSE					BIT(26)
#define SOP_ABG						BIT(27)
#define SOP_AMB						BIT(28)
#define SOP_RCK						BIT(29)
#define SOP_A8M						BIT(30)
#define XOP_BTCK					BIT(31)

//2 SYS_CLKR
#define ANAD16V_EN					BIT(0)
#define ANA8M						BIT(1)
#define MACSLP						BIT(4)
#define LOADER_CLK_EN				BIT(5)
#define _80M_SSC_DIS				BIT(7)
#define _80M_SSC_EN_HO				BIT(8)
#define PHY_SSC_RSTB				BIT(9)
#define SEC_CLK_EN					BIT(10)
#define MAC_CLK_EN					BIT(11)
#define SYS_CLK_EN					BIT(12)
#define RING_CLK_EN					BIT(13)


//2 9346CR


#define 	EEDO					BIT(0)
#define 	EEDI					BIT(1)
#define 	EESK					BIT(2)
#define 	EECS					BIT(3)
//#define 	EERPROMSEL			BIT(4)
//#define 	EEPROM_EN			BIT(5)
#define		BOOT_FROM_EEPROM		BIT(4)
#define		EEPROM_EN				BIT(5)
#define 	EEM0					BIT(6)
#define 	EEM1					BIT(7)


//2 AFE_MISC
#define AFE_BGEN					BIT(0)
#define AFE_MBEN					BIT(1)
#define MAC_ID_EN					BIT(7)


//2 SPS0_CTRL


//2 SPS_OCP_CFG


//2 SYSON_REG_LOCK
#define WLOCK_ALL		BIT(0)
#define WLOCK_00		BIT(1)
#define WLOCK_04		BIT(2)
#define WLOCK_08		BIT(3)
#define WLOCK_40		BIT(4)
#define WLOCK_1C_B6		BIT(5)
#define R_DIS_PRST_1		BIT(6)
#define LOCK_ALL_EN		BIT(7)

//2 RSV_CTRL
#define WLOCK_ALL					BIT(0)
#define WLOCK_00					BIT(1)
#define WLOCK_04					BIT(2)
#define WLOCK_08					BIT(3)
#define WLOCK_40					BIT(4)
#define R_DIS_PRST_0				BIT(5)
#define R_DIS_PRST_1				BIT(6)
#define LOCK_ALL_EN					BIT(7)

//2 RF_CTRL
#define RF_EN						BIT(0)
#define RF_RSTB						BIT(1)
#define RF_SDMRSTB					BIT(2)



//2 LDOA15_CTRL
#define LDA15_EN					BIT(0)
#define LDA15_STBY					BIT(1)
#define LDA15_OBUF					BIT(2)
#define LDA15_REG_VOS				BIT(3)
#define _LDA15_VOADJ(x)				(((x) & 0x7) << 4)



//2 LDOV12D_CTRL
#define LDV12_EN					BIT(0)
#define LDV12_SDBY					BIT(1)
#define LPLDO_HSM					BIT(2)
#define LPLDO_LSM_DIS				BIT(3)
#define _LDV12_VADJ(x)				(((x) & 0xF) << 4)


//2 AFE_XTAL_CTRL
#define XTAL_EN						BIT(0)
#define XTAL_BSEL					BIT(1)
#define _XTAL_BOSC(x)				(((x) & 0x3) << 2)
#define _XTAL_CADJ(x)				(((x) & 0xF) << 4)
#define XTAL_GATE_USB				BIT(8)
#define _XTAL_USB_DRV(x)			(((x) & 0x3) << 9)
#define XTAL_GATE_AFE				BIT(11)
#define _XTAL_AFE_DRV(x)			(((x) & 0x3) << 12)
#define XTAL_RF_GATE				BIT(14)
#define _XTAL_RF_DRV(x)				(((x) & 0x3) << 15)
#define XTAL_GATE_DIG				BIT(17)
#define _XTAL_DIG_DRV(x)			(((x) & 0x3) << 18)
#define XTAL_BT_GATE				BIT(20)
#define _XTAL_BT_DRV(x)				(((x) & 0x3) << 21)
#define _XTAL_GPIO(x)				(((x) & 0x7) << 23)


#define CKDLY_AFE					BIT(26)
#define CKDLY_USB					BIT(27)
#define CKDLY_DIG					BIT(28)
#define CKDLY_BT					BIT(29)


//2 AFE_PLL_CTRL
#define APLL_EN						BIT(0)
#define APLL_320_EN					BIT(1)
#define APLL_FREF_SEL				BIT(2)
#define APLL_EDGE_SEL				BIT(3)
#define APLL_WDOGB					BIT(4)
#define APLL_LPFEN					BIT(5)

#define APLL_REF_CLK_13MHZ			0x1
#define APLL_REF_CLK_19_2MHZ		0x2
#define APLL_REF_CLK_20MHZ			0x3
#define APLL_REF_CLK_25MHZ			0x4
#define APLL_REF_CLK_26MHZ			0x5
#define APLL_REF_CLK_38_4MHZ		0x6
#define APLL_REF_CLK_40MHZ			0x7

#define APLL_320EN					BIT(14)
#define APLL_80EN					BIT(15)
#define APLL_1MEN					BIT(24)


//2 EFUSE_CTRL
#define ALD_EN						BIT(18)
#define EF_PD						BIT(19)
#define EF_FLAG						BIT(31)

//2 EFUSE_TEST (For RTL8723 partially)
#define EF_TRPT						BIT(7)
#define EF_CELL_SEL					(BIT(8)|BIT(9)) // 00: Wifi Efuse, 01: BT Efuse0, 10: BT Efuse1, 11: BT Efuse2
#define LDOE25_EN					BIT(31)
#define EFUSE_SEL(x)					(((x) & 0x3) << 8)
#define EFUSE_SEL_MASK				0x300
#define EFUSE_WIFI_SEL_0			0x0
#define EFUSE_BT_SEL_0				0x1
#define EFUSE_BT_SEL_1				0x2
#define EFUSE_BT_SEL_2				0x3

#define EFUSE_ACCESS_ON			0x69	// For RTL8723 only.
#define EFUSE_ACCESS_OFF			0x00	// For RTL8723 only.

//2 PWR_DATA

//2 CAL_TIMER

//2 ACLK_MON
#define RSM_EN						BIT(0)
#define Timer_EN						BIT(4)


//2 GPIO_MUXCFG
#define TRSW0EN						BIT(2)
#define TRSW1EN						BIT(3)
#define EROM_EN						BIT(4)
#define EnBT							BIT(5)
#define EnUart						BIT(8)
#define Uart_910						BIT(9)
#define EnPMAC						BIT(10)
#define SIC_SWRST					BIT(11)
#define EnSIC						BIT(12)
#define SIC_23						BIT(13)
#define EnHDP						BIT(14)
#define SIC_LBK						BIT(15)

//2 GPIO_PIN_CTRL

//2 GPIO_INTM

//2 LEDCFG
#define LED0PL 						BIT(4)
#define LED0DIS						BIT(7)
#define LED1DIS						BIT(15)
#define LED1PL 						BIT(12)

#define  SECCAM_CLR					BIT(30)


//2 MCUFWDL
#define MCUFWDL_EN					BIT(0)
#define MCUFWDL_RDY				BIT(1)
#define FWDL_ChkSum_rpt			BIT(2)
#define MACINI_RDY					BIT(3)
#define BBINI_RDY					BIT(4)
#define RFINI_RDY					BIT(5)
#define WINTINI_RDY					BIT(6)
#define CPRST						BIT(23)
#define RAM_DL_SEL				BIT7	// 1:RAM, 0:ROM

//2REG_HPON_FSM
#define BOND92CE_1T2R_CFG			BIT(22)

//2 REG_SYS_CFG
#define XCLK_VLD						BIT(0)
#define ACLK_VLD					BIT(1)
#define UCLK_VLD					BIT(2)
#define PCLK_VLD						BIT(3)
#define PCIRSTB						BIT(4)
#define V15_VLD						BIT(5)
#define TRP_B15V_EN					BIT(7)
#define SIC_IDLE						BIT(8)
#define BD_MAC2						BIT(9)
#define BD_MAC1						BIT(10)
#define IC_MACPHY_MODE				BIT(11)
#define CHIP_VER						(BIT(12)|BIT(13)|BIT(14)|BIT(15))
#define BT_FUNC						BIT(16)
#define VENDOR_ID					BIT(19)
#define PAD_HWPD_IDN				BIT(22)
#define RTL_ID						BIT(23)	// TestChip ID, 1:Test(RLE); 0:MP(RL)
#define SPS_SEL						BIT(24) // 1:LDO regulator mode; 0:Switching regulator mode
#define BD_PKG_SEL					BIT(25)
#define BD_HCI_SEL					BIT(26)
#define TYPE_ID						BIT(27)

#define CHIP_VER_RTL_MASK			0xF000	//Bit 12 ~ 15
#define CHIP_VER_RTL_SHIFT			12

//2REG_GPIO_OUTSTS (For RTL8723 only)
#define	EFS_HCI_SEL				(BIT(0)|BIT(1))
#define	PAD_HCI_SEL				(BIT(2)|BIT(3))
#define	HCI_SEL						(BIT(4)|BIT(5))
#define	PKG_SEL_HCI				BIT(6)
#define	FEN_GPS					BIT(7)
#define	FEN_BT						BIT(8)
#define	FEN_WL						BIT(9)
#define	FEN_PCI						BIT(10)
#define	FEN_USB					BIT(11)
#define	BTRF_HWPDN_N				BIT(12)
#define	WLRF_HWPDN_N				BIT(13)
#define	PDN_BT_N					BIT(14)
#define	PDN_GPS_N					BIT(15)
#define	BT_CTL_HWPDN				BIT(16)
#define	GPS_CTL_HWPDN				BIT(17)
#define	PPHY_SUSB					BIT(20)
#define	UPHY_SUSB					BIT(21)
#define	PCI_SUSEN					BIT(22)
#define	USB_SUSEN					BIT(23)
#define	RF_RL_ID					(BIT(31)|BIT(30)|BIT(29)|BIT(28))


//-----------------------------------------------------
//
//	0x0100h ~ 0x01FFh	MACTOP General Configuration
//
//-----------------------------------------------------

//2 Function Enable Registers
//2 CR
#define CALTMR_EN					BIT(10)

#define REG_LBMODE					(REG_CR + 3)

#define HCI_TXDMA_EN				BIT(0)
#define HCI_RXDMA_EN				BIT(1)
#define TXDMA_EN					BIT(2)
#define RXDMA_EN					BIT(3)
#define PROTOCOL_EN					BIT(4)
#define SCHEDULE_EN					BIT(5)
#define MACTXEN						BIT(6)
#define MACRXEN						BIT(7)
#define ENSWBCN						BIT(8)
#define ENSEC						BIT(9)

// Network type
#define _NETTYPE(x)					(((x) & 0x3) << 16)
#define MASK_NETTYPE				0x30000
#define NT_NO_LINK					0x0
#define NT_LINK_AD_HOC				0x1
#define NT_LINK_AP					0x2
#define NT_AS_AP					0x3

#define _LBMODE(x)					(((x) & 0xF) << 24)
#define MASK_LBMODE				0xF000000
#define LOOPBACK_NORMAL			0x0
#define LOOPBACK_IMMEDIATELY		0xB
#define LOOPBACK_MAC_DELAY		0x3
#define LOOPBACK_PHY				0x1
#define LOOPBACK_DMA				0x7


//2 PBP - Page Size Register
#define GET_RX_PAGE_SIZE(value)		((value) & 0xF)
#define GET_TX_PAGE_SIZE(value)		(((value) & 0xF0) >> 4)
#define _PSRX_MASK					0xF
#define _PSTX_MASK					0xF0
#define _PSRX(x)						(x)
#define _PSTX(x)						((x) << 4)

#define PBP_64						0x0
#define PBP_128						0x1
#define PBP_256						0x2
#define PBP_512						0x3
#define PBP_1024					0x4


//2 TX/RXDMA
#define RXDMA_ARBBW_EN			BIT(0)
#define RXSHFT_EN					BIT(1)
#define RXDMA_AGG_EN				BIT(2)
#define RXDMA_AGG_MODE_EN		BIT(1)
#define QS_VO_QUEUE				BIT(8)
#define QS_VI_QUEUE					BIT(9)
#define QS_BE_QUEUE				BIT(10)
#define QS_BK_QUEUE				BIT(11)
#define QS_MANAGER_QUEUE			BIT(12)
#define QS_HIGH_QUEUE				BIT(13)

#define HQSEL_VOQ					BIT(0)
#define HQSEL_VIQ					BIT(1)
#define HQSEL_BEQ					BIT(2)
#define HQSEL_BKQ					BIT(3)
#define HQSEL_MGTQ					BIT(4)
#define HQSEL_HIQ					BIT(5)

// For normal driver, 0x10C
#define _TXDMA_HIQ_MAP(x) 	 		(((x)&0x3) << 14)
#define _TXDMA_MGQ_MAP(x) 	 		(((x)&0x3) << 12)
#define _TXDMA_BKQ_MAP(x) 	 		(((x)&0x3) << 10)
#define _TXDMA_BEQ_MAP(x) 	 		(((x)&0x3) << 8 )
#define _TXDMA_VIQ_MAP(x) 	 		(((x)&0x3) << 6 )
#define _TXDMA_VOQ_MAP(x) 	 		(((x)&0x3) << 4 )

#define QUEUE_LOW					1
#define QUEUE_NORMAL				2
#define QUEUE_HIGH					3



//2 TRXFF_BNDY


//2 LLT_INIT
#define _LLT_NO_ACTIVE				0x0
#define _LLT_WRITE_ACCESS			0x1
#define _LLT_READ_ACCESS			0x2

#define _LLT_INIT_DATA(x)			((x) & 0xFF)
#define _LLT_INIT_ADDR(x)			(((x) & 0xFF) << 8)
#define _LLT_OP(x)					(((x) & 0x3) << 30)
#define _LLT_OP_VALUE(x)			(((x) >> 30) & 0x3)


//2 BB_ACCESS_CTRL
#define BB_WRITE_READ_MASK		(BIT(31) | BIT(30))
#define BB_WRITE_EN					BIT(30)
#define BB_READ_EN					BIT(31)
//#define BB_ADDR_MASK				0xFFF
//#define _BB_ADDR(x)					((x) & BB_ADDR_MASK)

//-----------------------------------------------------
//
//	0x0200h ~ 0x027Fh	TXDMA Configuration
//
//-----------------------------------------------------
//2 RQPN
#define _HPQ(x)						((x) & 0xFF)
#define _LPQ(x)						(((x) & 0xFF) << 8)
#define _PUBQ(x)						(((x) & 0xFF) << 16)
#define _NPQ(x)						((x) & 0xFF)			// NOTE: in RQPN_NPQ register


#define HPQ_PUBLIC_DIS				BIT(24)
#define LPQ_PUBLIC_DIS				BIT(25)
#define LD_RQPN						BIT(31)


//2 TDECTRL
#define BCN_VALID					BIT(16)
#define BCN_HEAD(x)					(((x) & 0xFF) << 8)
#define	BCN_HEAD_MASK				0xFF00

//2 TDECTL
#define BLK_DESC_NUM_SHIFT			4
#define BLK_DESC_NUM_MASK			0xF


//2 TXDMA_OFFSET_CHK
#define DROP_DATA_EN				BIT(9)


//-----------------------------------------------------
//
//	0x0280h ~ 0x02FFh	RXDMA Configuration
//
//-----------------------------------------------------
#ifdef CONFIG_WOWLAN
#define RXPKT_RELEASE_POLL		BIT(16)
#define RXDMA_IDLE				BIT(17)
#define RW_RELEASE_EN			BIT(18)
#endif

//-----------------------------------------------------
//
//	0x0400h ~ 0x047Fh	Protocol Configuration
//
//-----------------------------------------------------
//2 FWHW_TXQ_CTRL
#define EN_AMPDU_RTY_NEW			BIT(7)

//2 INIRTSMCS_SEL
#define _INIRTSMCS_SEL(x)			((x) & 0x3F)


//2 SPEC SIFS
#define _SPEC_SIFS_CCK(x)			((x) & 0xFF)
#define _SPEC_SIFS_OFDM(x)			(((x) & 0xFF) << 8)


//2 RRSR

#define RATE_REG_BITMAP_ALL			0xFFFFF

#define _RRSC_BITMAP(x)					((x) & 0xFFFFF)

#define _RRSR_RSC(x)						(((x) & 0x3) << 21)
#define RRSR_RSC_RESERVED				0x0
#define RRSR_RSC_UPPER_SUBCHANNEL	0x1
#define RRSR_RSC_LOWER_SUBCHANNEL	0x2
#define RRSR_RSC_DUPLICATE_MODE		0x3


//2 ARFR
#define USE_SHORT_G1				BIT(20)

//2 AGGLEN_LMT_L
#define _AGGLMT_MCS0(x)				((x) & 0xF)
#define _AGGLMT_MCS1(x)				(((x) & 0xF) << 4)
#define _AGGLMT_MCS2(x)				(((x) & 0xF) << 8)
#define _AGGLMT_MCS3(x)				(((x) & 0xF) << 12)
#define _AGGLMT_MCS4(x)				(((x) & 0xF) << 16)
#define _AGGLMT_MCS5(x)				(((x) & 0xF) << 20)
#define _AGGLMT_MCS6(x)				(((x) & 0xF) << 24)
#define _AGGLMT_MCS7(x)				(((x) & 0xF) << 28)


//2 RL
#define	RETRY_LIMIT_SHORT_SHIFT		8
#define	RETRY_LIMIT_LONG_SHIFT		0


//2 DARFRC
#define _DARF_RC1(x)				((x) & 0x1F)
#define _DARF_RC2(x)				(((x) & 0x1F) << 8)
#define _DARF_RC3(x)				(((x) & 0x1F) << 16)
#define _DARF_RC4(x)				(((x) & 0x1F) << 24)
// NOTE: shift starting from address (DARFRC + 4)
#define _DARF_RC5(x)				((x) & 0x1F)
#define _DARF_RC6(x)				(((x) & 0x1F) << 8)
#define _DARF_RC7(x)				(((x) & 0x1F) << 16)
#define _DARF_RC8(x)				(((x) & 0x1F) << 24)


//2 RARFRC
#define _RARF_RC1(x)				((x) & 0x1F)
#define _RARF_RC2(x)				(((x) & 0x1F) << 8)
#define _RARF_RC3(x)				(((x) & 0x1F) << 16)
#define _RARF_RC4(x)				(((x) & 0x1F) << 24)
// NOTE: shift starting from address (RARFRC + 4)
#define _RARF_RC5(x)				((x) & 0x1F)
#define _RARF_RC6(x)				(((x) & 0x1F) << 8)
#define _RARF_RC7(x)				(((x) & 0x1F) << 16)
#define _RARF_RC8(x)				(((x) & 0x1F) << 24)




//-----------------------------------------------------
//
//	0x0500h ~ 0x05FFh	EDCA Configuration
//
//-----------------------------------------------------



//2 EDCA setting
#define AC_PARAM_TXOP_LIMIT_OFFSET	16
#define AC_PARAM_ECW_MAX_OFFSET		12
#define AC_PARAM_ECW_MIN_OFFSET		8
#define AC_PARAM_AIFS_OFFSET			0


//2 EDCA_VO_PARAM
#define _AIFS(x)						(x)
#define _ECW_MAX_MIN(x)			((x) << 8)
#define _TXOP_LIMIT(x)				((x) << 16)


#define _BCNIFS(x)					((x) & 0xFF)
#define _BCNECW(x)					(((x) & 0xF))<< 8)


#define _LRL(x)						((x) & 0x3F)
#define _SRL(x)						(((x) & 0x3F) << 8)


//2 SIFS_CCK
#define _SIFS_CCK_CTX(x)			((x) & 0xFF)
#define _SIFS_CCK_TRX(x)			(((x) & 0xFF) << 8);


//2 SIFS_OFDM
#define _SIFS_OFDM_CTX(x)			((x) & 0xFF)
#define _SIFS_OFDM_TRX(x)			(((x) & 0xFF) << 8);


//2 TBTT PROHIBIT
#define _TBTT_PROHIBIT_HOLD(x)		(((x) & 0xFF) << 8)


//2 REG_RD_CTRL
#define DIS_EDCA_CNT_DWN			BIT(11)


//2 BCN_CTRL
#define DIS_ATIM					BIT(0)
#define DIS_BCNQ_SUB				BIT(1)
#define EN_TXBCN_RPT					BIT(2)
#define EN_BCN_FUNCTION				BIT(3)
#define DIS_TSF_UDT					BIT(4)

// The same function but different bit field.
#define	DIS_TSF_UDT0_NORMAL_CHIP	BIT(4)
#define	DIS_TSF_UDT0_TEST_CHIP		BIT(5)

//2 ACMHWCTRL
#define	AcmHw_HwEn					BIT(0)
#define	AcmHw_BeqEn					BIT(1)
#define	AcmHw_ViqEn					BIT(2)
#define	AcmHw_VoqEn					BIT(3)
#define	AcmHw_BeqStatus				BIT(4)
#define	AcmHw_ViqStatus				BIT(5)
#define	AcmHw_VoqStatus				BIT(6)



//-----------------------------------------------------
//
//	0x0600h ~ 0x07FFh	WMAC Configuration
//
//-----------------------------------------------------

//2 APSD_CTRL
#define APSDOFF						BIT(6)
#define APSDOFF_STATUS				BIT(7)


//2 BWOPMODE
#define BW_20MHZ					BIT(2)
//#define BW_OPMODE_20MHZ				BIT(2)	// For compability


#define RATE_BITMAP_ALL			0xFFFFF

// Only use CCK 1M rate for ACK
#define RATE_RRSR_CCK_ONLY_1M		0xFFFF1

//2 TCR
#define TSFRST						BIT(0)
#define DIS_GCLK						BIT(1)
#define PAD_SEL						BIT(2)
#define PWR_ST						BIT(6)
#define PWRBIT_OW_EN				BIT(7)
#define ACRC							BIT(8)
#define CFENDFORM					BIT(9)
#define ICV							BIT(10)

//2 RCR
#define AAP							BIT(0)
#define APM							BIT(1)
#define AM							BIT(2)
#define AB							BIT(3)
#define ADD3							BIT(4)
#define APWRMGT					BIT(5)
#define CBSSID						BIT(6)
#define CBSSID_BCN					BIT(7)
#define ACRC32						BIT(8)
#define AICV							BIT(9)
#define ADF							BIT(11)
#define ACF							BIT(12)
#define AMF							BIT(13)
#define HTC_LOC_CTRL				BIT(14)
#define UC_DATA_EN					BIT(16)
#define BM_DATA_EN					BIT(17)
#define MFBEN						BIT(22)
#define LSIGEN						BIT(23)
#define EnMBID						BIT(24)
#define APP_BASSN					BIT(27)
#define APP_PHYSTS					BIT(28)
#define APP_ICV						BIT(29)
#define APP_MIC						BIT(30)
#define APP_FCS						BIT(31)

//2 RX_PKT_LIMIT

//2 RX_DLK_TIME

//2 MBIDCAMCFG



//2 AMPDU_MIN_SPACE
#define _MIN_SPACE(x)				((x) & 0x7)
#define _SHORT_GI_PADDING(x)		(((x) & 0x1F) << 3)


//2 RXERR_RPT
#define RXERR_TYPE_OFDM_PPDU				0
#define RXERR_TYPE_OFDM_FALSE_ALARM		1
#define RXERR_TYPE_OFDM_MPDU_OK			2
#define RXERR_TYPE_OFDM_MPDU_FAIL		3
#define RXERR_TYPE_CCK_PPDU				4
#define RXERR_TYPE_CCK_FALSE_ALARM		5
#define RXERR_TYPE_CCK_MPDU_OK			6
#define RXERR_TYPE_CCK_MPDU_FAIL			7
#define RXERR_TYPE_HT_PPDU					8
#define RXERR_TYPE_HT_FALSE_ALARM		9
#define RXERR_TYPE_HT_MPDU_TOTAL			10
#define RXERR_TYPE_HT_MPDU_OK				11
#define RXERR_TYPE_HT_MPDU_FAIL			12
#define RXERR_TYPE_RX_FULL_DROP			15

#define RXERR_COUNTER_MASK				0xFFFFF
#define RXERR_RPT_RST						BIT(27)
#define _RXERR_RPT_SEL(type)				((type) << 28)


//2 SECCFG
#define	SCR_TxUseDK						BIT(0)			//Force Tx Use Default Key
#define	SCR_RxUseDK						BIT(1)			//Force Rx Use Default Key
#define	SCR_TxEncEnable					BIT(2)			//Enable Tx Encryption
#define	SCR_RxDecEnable					BIT(3)			//Enable Rx Decryption
#define	SCR_SKByA2							BIT(4)			//Search kEY BY A2
#define	SCR_NoSKMC							BIT(5)			//No Key Search Multicast
#define 	SCR_TXBCUSEDK					BIT(6)			// Force Tx Broadcast packets Use Default Key
#define 	SCR_RXBCUSEDK					BIT(7)			// Force Rx Broadcast packets Use Default Key


//-----------------------------------------------------
//
//	0xFE00h ~ 0xFE55h	RTL8723 SDIO Configuration
//
//-----------------------------------------------------

// I/O bus domain address mapping
#define SDIO_LOCAL_BASE				0x10250000
#define WLAN_IOREG_BASE				0x10260000
#define FIRMWARE_FIFO_BASE			0x10270000
#define TX_HIQ_BASE				0x10310000
#define TX_MIQ_BASE				0x10320000
#define TX_LOQ_BASE				0x10330000
#define RX_RX0FF_BASE				0x10340000

// SDIO host local register space mapping.
#define SDIO_LOCAL_MSK				0x0FFF
#define WLAN_IOREG_MSK				0x7FFF
#define WLAN_FIFO_MSK		      		0x1FFF	// Aggregation Length[12:0]
#define WLAN_RX0FF_MSK			      	0x0003

#define SDIO_WITHOUT_REF_DEVICE_ID		0	// Without reference to the SDIO Device ID
#define SDIO_LOCAL_DEVICE_ID			0	// 0b[16], 000b[15:13]
#define WLAN_TX_HIQ_DEVICE_ID			4	// 0b[16], 100b[15:13]
#define WLAN_TX_MIQ_DEVICE_ID			5	// 0b[16], 101b[15:13]
#define WLAN_TX_LOQ_DEVICE_ID			6	// 0b[16], 110b[15:13]
#define WLAN_RX0FF_DEVICE_ID			7	// 0b[16], 111b[15:13]
#define WLAN_IOREG_DEVICE_ID			8	// 1b[16]

// SDIO Tx Free Page Index
#define HI_QUEUE_IDX				0
#define MID_QUEUE_IDX				1
#define LOW_QUEUE_IDX				2
#define PUBLIC_QUEUE_IDX			3

#define SDIO_MAX_TX_QUEUE			3		// HIQ, MIQ and LOQ
#define SDIO_MAX_RX_QUEUE			1

#define SDIO_REG_TX_CTRL			0x0000 // SDIO Tx Control
#define SDIO_REG_HIMR				0x0014 // SDIO Host Interrupt Mask
#define SDIO_REG_HISR				0x0018 // SDIO Host Interrupt Service Routine
#define SDIO_REG_HCPWM				0x0019 // HCI Current Power Mode
#define SDIO_REG_RX0_REQ_LEN			0x001C // RXDMA Request Length
#define SDIO_REG_FREE_TXPG			0x0020 // Free Tx Buffer Page
#define SDIO_REG_HCPWM1				0x0024 // HCI Current Power Mode 1
#define SDIO_REG_HCPWM2				0x0026 // HCI Current Power Mode 2
#define SDIO_REG_HTSFR_INFO			0x0030 // HTSF Informaion
#define SDIO_REG_HRPWM1				0x0080 // HCI Request Power Mode 1
#define SDIO_REG_HRPWM2				0x0082 // HCI Request Power Mode 2
#define SDIO_REG_HPS_CLKR			0x0084 // HCI Power Save Clock
#define SDIO_REG_HSUS_CTRL			0x0086 // SDIO HCI Suspend Control
#define SDIO_REG_HIMR_ON			0x0090 // SDIO Host Extension Interrupt Mask Always
#define SDIO_REG_HISR_ON			0x0091 // SDIO Host Extension Interrupt Status Always

#define SDIO_HIMR_DISABLED			0

// SDIO Host Interrupt Mask Register
#define SDIO_HIMR_RX_REQUEST_MSK		BIT0
#define SDIO_HIMR_AVAL_MSK			BIT1
#define SDIO_HIMR_TXERR_MSK			BIT2
#define SDIO_HIMR_RXERR_MSK			BIT3
#define SDIO_HIMR_TXFOVW_MSK			BIT4
#define SDIO_HIMR_RXFOVW_MSK			BIT5
#define SDIO_HIMR_TXBCNOK_MSK			BIT6
#define SDIO_HIMR_TXBCNERR_MSK			BIT7
#define SDIO_HIMR_BCNERLY_INT_MSK		BIT16
#define SDIO_HIMR_C2HCMD_MSK			BIT17
#define SDIO_HIMR_CPWM1_MSK			BIT18
#define SDIO_HIMR_CPWM2_MSK			BIT19
#define SDIO_HIMR_HSISR_IND_MSK			BIT20
#define SDIO_HIMR_GTINT3_IND_MSK		BIT21
#define SDIO_HIMR_GTINT4_IND_MSK		BIT22
#define SDIO_HIMR_PSTIMEOUT_MSK			BIT23
#define SDIO_HIMR_OCPINT_MSK			BIT24
#define SDIO_HIMR_ATIMEND_MSK			BIT25
#define SDIO_HIMR_ATIMEND_E_MSK			BIT26
#define SDIO_HIMR_CTWEND_MSK			BIT27

// SDIO Host Interrupt Service Routine
#define SDIO_HISR_RX_REQUEST			BIT0
#define SDIO_HISR_AVAL				BIT1
#define SDIO_HISR_TXERR				BIT2
#define SDIO_HISR_RXERR				BIT3
#define SDIO_HISR_TXFOVW			BIT4
#define SDIO_HISR_RXFOVW			BIT5
#define SDIO_HISR_TXBCNOK			BIT6
#define SDIO_HISR_TXBCNERR			BIT7
#define SDIO_HISR_BCNERLY_INT			BIT16
#define SDIO_HISR_C2HCMD			BIT17
#define SDIO_HISR_CPWM1				BIT18
#define SDIO_HISR_CPWM2				BIT19
#define SDIO_HISR_HSISR_IND			BIT20
#define SDIO_HISR_GTINT3_IND			BIT21
#define SDIO_HISR_GTINT4_IND			BIT22
#define SDIO_HISR_PSTIMEOUT			BIT23
#define SDIO_HISR_OCPINT			BIT24
#define SDIO_HISR_ATIMEND			BIT25
#define SDIO_HISR_ATIMEND_E			BIT26
#define SDIO_HISR_CTWEND			BIT27

#define MASK_SDIO_HISR_CLEAR		(SDIO_HISR_TXERR |\
									SDIO_HISR_RXERR |\
									SDIO_HISR_TXFOVW |\
									SDIO_HISR_RXFOVW |\
									SDIO_HISR_TXBCNOK |\
									SDIO_HISR_TXBCNERR |\
									SDIO_HISR_C2HCMD |\
									SDIO_HISR_CPWM1 |\
									SDIO_HISR_CPWM2 |\
									SDIO_HISR_HSISR_IND |\
									SDIO_HISR_GTINT3_IND |\
									SDIO_HISR_GTINT4_IND |\
									SDIO_HISR_PSTIMEOUT |\
									SDIO_HISR_OCPINT)

// SDIO HCI Suspend Control Register
#define HCI_RESUME_PWR_RDY			BIT1
#define HCI_SUS_CTRL				BIT0

// SDIO Tx FIFO related
#define SDIO_TX_FREE_PG_QUEUE			4	// The number of Tx FIFO free page
#define SDIO_TX_FIFO_PAGE_SZ 			128

// vivi added for new cam search flow, 20091028
#define SCR_TxUseBroadcastDK			BIT6	// Force Tx Use Broadcast Default Key
#define SCR_RxUseBroadcastDK			BIT7	// Force Rx Use Broadcast Default Key


#define POLLING_LLT_THRESHOLD				20
#define POLLING_READY_TIMEOUT_COUNT		1000

//-----------------------------------------------------
//
//	0xFE00h ~ 0xFE55h	USB Configuration
//
//-----------------------------------------------------

//2 USB Information (0xFE17)
#define USB_IS_HIGH_SPEED					0
#define USB_IS_FULL_SPEED					1
#define USB_SPEED_MASK					BIT(5)

#define USB_NORMAL_SIE_EP_MASK			0xF
#define USB_NORMAL_SIE_EP_SHIFT			4


//2 Special Option
#define USB_AGG_EN						BIT(3)

// 0; Use interrupt endpoint to upload interrupt pkt
// 1; Use bulk endpoint to upload interrupt pkt,
#define INT_BULK_SEL					BIT(4)



//2REG_C2HEVT_CLEAR
#define		C2H_EVT_HOST_CLOSE			0x00	// Set by driver and notify FW that the driver has read the C2H command message
#define		C2H_EVT_FW_CLOSE			0xFF	// Set by FW indicating that FW had set the C2H command message and it's not yet read by driver.


//2REG_MULTI_FUNC_CTRL(For RTL8723 Only)
#define	WL_HWPDN_EN				BIT0		// Enable GPIO[9] as WiFi HW PDn source
#define	WL_HWPDN_SL				BIT1		// WiFi HW PDn polarity control
#define	WL_FUNC_EN				BIT2		// WiFi function enable
#define	WL_HWROF_EN				BIT3		// Enable GPIO[9] as WiFi RF HW PDn source
#define	BT_HWPDN_EN				BIT16	// Enable GPIO[11] as BT HW PDn source
#define	BT_HWPDN_SL				BIT17	// BT HW PDn polarity control
#define	BT_FUNC_EN					BIT18	// BT function enable
#define	BT_HWROF_EN				BIT19	// Enable GPIO[11] as BT/GPS RF HW PDn source
#define	GPS_HWPDN_EN				BIT20	// Enable GPIO[10] as GPS HW PDn source
#define	GPS_HWPDN_SL				BIT21	// GPS HW PDn polarity control
#define	GPS_FUNC_EN				BIT22	// GPS function enable


//3 REG_LIFECTRL_CTRL
#define	HAL92C_EN_PKT_LIFE_TIME_BK		BIT3
#define	HAL92C_EN_PKT_LIFE_TIME_BE		BIT2
#define	HAL92C_EN_PKT_LIFE_TIME_VI		BIT1
#define	HAL92C_EN_PKT_LIFE_TIME_VO		BIT0

#define	HAL92C_MSDU_LIFE_TIME_UNIT		128		// in us, said by Tim.

//========================================================
// General definitions
//========================================================
#define LAST_ENTRY_OF_TX_PKT_BUFFER		255

#define POLLING_LLT_THRESHOLD				20
//#if RTL8188E_FOR_MP_TEST == 1
//#define POLLING_READY_TIMEOUT_COUNT		3000
//#else
#define POLLING_READY_TIMEOUT_COUNT		1000
//#endif
// GPIO BIT
#define	HAL_8192C_HW_GPIO_WPS_BIT		BIT2

//-----------------------------------------------------------------------------
//USB interrupt
//-----------------------------------------------------------------------------
#define	UHIMR_TIMEOUT2					BIT31
#define	UHIMR_TIMEOUT1					BIT30
#define	UHIMR_PSTIMEOUT					BIT29
#define	UHIMR_GTINT4					BIT28
#define	UHIMR_GTINT3					BIT27
#define	UHIMR_TXBCNERR					BIT26
#define	UHIMR_TXBCNOK					BIT25
#define	UHIMR_TSF_BIT32_TOGGLE			BIT24
#define	UHIMR_BCNDMAINT3				BIT23
#define	UHIMR_BCNDMAINT2				BIT22
#define	UHIMR_BCNDMAINT1				BIT21
#define	UHIMR_BCNDMAINT0				BIT20
#define	UHIMR_BCNDOK3					BIT19
#define	UHIMR_BCNDOK2					BIT18
#define	UHIMR_BCNDOK1					BIT17
#define	UHIMR_BCNDOK0					BIT16
#define	UHIMR_HSISR_IND					BIT15
#define	UHIMR_BCNDMAINT_E				BIT14
//RSVD	BIT13
#define	UHIMR_CTW_END					BIT12
//RSVD	BIT11
#define	UHIMR_C2HCMD					BIT10
#define	UHIMR_CPWM2					BIT9
#define	UHIMR_CPWM					BIT8
#define	UHIMR_HIGHDOK					BIT7		// High Queue DMA OK Interrupt
#define	UHIMR_MGNTDOK					BIT6		// Management Queue DMA OK Interrupt
#define	UHIMR_BKDOK					BIT5		// AC_BK DMA OK Interrupt
#define	UHIMR_BEDOK					BIT4		// AC_BE DMA OK Interrupt
#define	UHIMR_VIDOK						BIT3		// AC_VI DMA OK Interrupt
#define	UHIMR_VODOK					BIT2		// AC_VO DMA Interrupt
#define	UHIMR_RDU						BIT1		// Receive Descriptor Unavailable
#define	UHIMR_ROK						BIT0		// Receive DMA OK Interrupt

// USB Host Interrupt Status Extension bit
#define	UHIMR_BCNDMAINT7				BIT23
#define	UHIMR_BCNDMAINT6				BIT22
#define	UHIMR_BCNDMAINT5				BIT21
#define	UHIMR_BCNDMAINT4				BIT20
#define	UHIMR_BCNDOK7					BIT19
#define	UHIMR_BCNDOK6					BIT18
#define	UHIMR_BCNDOK5					BIT17
#define	UHIMR_BCNDOK4					BIT16
// bit14-15: RSVD
#define	UHIMR_ATIMEND_E				BIT13
#define	UHIMR_ATIMEND					BIT12
#define	UHIMR_TXERR						BIT11
#define	UHIMR_RXERR						BIT10
#define	UHIMR_TXFOVW					BIT9
#define	UHIMR_RXFOVW					BIT8
// bit2-7: RSVD
#define	UHIMR_OCPINT					BIT1
// bit0: RSVD

#define	REG_USB_HIMR				0xFE38
#define	REG_USB_HIMRE				0xFE3C
#define	REG_USB_HISR					0xFE78
#define	REG_USB_HISRE				0xFE7C

#define	USB_INTR_CPWM_OFFSET		16
#define	USB_INTR_CONTENT_HISR_OFFSET		48
#define	USB_INTR_CONTENT_HISRE_OFFSET		52
#define	USB_INTR_CONTENT_LENGTH			56
#define	USB_C2H_CMDID_OFFSET		0
#define	USB_C2H_SEQ_OFFSET		1
#define	USB_C2H_EVENT_OFFSET		2

#endif

