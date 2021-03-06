#ifndef __ASM_ARCH_REGS_LC181X_H
#define __ASM_ARCH_REGS_LC181X_H

/*
 * Base addresses for standard memory-mapped peripherals for LC1810
 */
#define DDR_MEMORY_BASE 	(0x00000000)
#define DEBUG_APB_BASE		(0x80000000)
#define AP_SEC_RAM_BASE 	(0x9FF80000)
#define AP_DMAG_BASE		(0xA0000000)
#define AUDIO_DMAS_BASE 	(0xA0002000)
#define AP_DMAS_BASE		(0xA0003000)
#define AP_DMAC_BASE		(0xA0004000)
#define LCDC0_BASE		(0xA0008000)

#if defined(CONFIG_CPU_LC1810)
#define LCDC1_BASE		(0xA0009000)
#define M0_RAM_BASE		(0xA0040000)
#endif

#define CTL_BASE		(0xA0060000)
#define NFC_BASE		(0xA0061000)

#if defined(CONFIG_CPU_LC1810)
#define HDMI_BASE		(0xA00A0000)
#define HPI_BASE		(0xA00B0000)
#define HPI_MEM_BASE		(0xA00C0000)
#endif

#if defined(CONFIG_CPU_LC1810)
#define RTC_BASE		(0xA0108400)
#define TRACKBALL_BASE		(0xA0108800)
#endif

#if defined(CONFIG_CPU_LC1810)
#define WDT0_BASE		(0xA0108C00)
#elif defined(CONFIG_CPU_LC1813)
#define WDT0_BASE		(0xA0108000)
#define WDT1_BASE		(0xA0108400)
#define WDT2_BASE		(0xA0108800)
#define WDT3_BASE		(0xA0108C00)
#endif

#define TIMER_BASE		(0xA0109000)
#define I2C1_BASE		(0xA0109800)
#define I2C0_BASE		(0xA0109C00)
#define I2C3_BASE		(0xA010A000)
#define PWM_BASE		(0xA010A400)
#define AP_PWR_BASE		(0xA010A800)

#define MIPI_BASE		(0xA0110000)

#define I2S0_BASE		(0xA0140000)
#define I2S1_BASE		(0xA0140800)
#define SSI0_BASE		(0xA0145000)
#define SSI1_BASE		(0xA0146000)
#define SSI3_BASE		(0xA0146800)
#define UART0_BASE		(0xA0147000)
#define UART1_BASE		(0xA0148000)
#define UART2_BASE		(0xA0149000)
#define ISP_BASE		(0xA0200000)
#define USB_OTG_BASE		(0xA0300000)

#if defined(CONFIG_CPU_LC1810)
#define USB_HOST_BASE		(0xA0340000)
#define USB_HSIC_BASE		(0xA0380000)
#endif

#define CTRL_DDR_BASE		(0xA1000000)
#define COM_I2C_BASE		(0xA1001000)
#define PCM_BASE		(0xA1002000)
#define PCM1_BASE		(0xA1002800)
#define MUX_PIN_BASE		(0xA1003000)
#define PHY_DDR_BASE		(0xA1004000)
#define DDR_PWR_BASE		(0xA1005000)
#define COM_UART_BASE		(0xA1006000)
#define GPIO0_BASE		(0xA1007000)
#define GPIO1_BASE		(0xA1007800)

#if defined(CONFIG_CPU_LC1813)
#define COM_RAM_BASE		(0xA1008000)
#endif

#define DECODER_BASE		(0xA2000000)
#define ENCODER0_BASE		(0xA2001000)
#define ENCODER1_BASE		(0xA2001800)
#define GPU_BASE		(0xA2010000)
#if defined(CONFIG_CPU_LC1813)
#define AP_2DACC_BASE		(0xA2020000)
#endif
#define I2C2_BASE		(0xA3000000)
#define KBS_BASE		(0xA3001000)
#define SSI2_BASE		(0xA3002000)
#define BP147_BASE		(0xA3003000)
#define SDMMC0_BASE		(0xA3004000)
#define SDMMC1_BASE		(0xA3005000)
#define SDMMC2_BASE		(0xA3006000)

#if defined(CONFIG_CPU_LC1810)
#define SDMMC3_BASE		(0xA3007000)
#elif defined(CONFIG_CPU_LC1813)
#define TIMESTAMP_BASE		(0xA3007000)
#endif

#define TPZCTL_BASE		(0xA3008000)

#if defined(CONFIG_CPU_LC1813)
#define GTIMER_BASE		(0xA3009000)
#endif

#define CIPHER_BASE		(0xA4000000)
#define SECURITY_BASE		(0xA4002000)
#define DDR_AXI_GPV_BASE	(0xA4100000)
#define PERI_AXI_GPV_BASE	(0xA4200000)

#define CPU_CORE_BASE		(0xA6000000)

#if defined(CONFIG_CPU_LC1810)
#define CORE_SCU_BASE		(CPU_CORE_BASE + 0x00)
#define GIC_CPU_BASE		(CPU_CORE_BASE + 0x100)
#define CORE_TWD_BASE		(CPU_CORE_BASE + 0x600)	
#define GIC_DIST_BASE		(CPU_CORE_BASE + 0x1000)
#define L2_CACHE_CTRL_BASE	(0xA6002000)
#elif defined(CONFIG_CPU_LC1813)
#define GIC_DIST_BASE		(CPU_CORE_BASE + 0x1000)
#define GIC_CPU_BASE		(CPU_CORE_BASE + 0x2000)
#define A7_AXI_GPV_BASE		(0xA4300000)
#endif

#define ROM_BASE		(0xFFFF0000)

#endif /* __ASM_ARCH_REGS_LC181X_H */
