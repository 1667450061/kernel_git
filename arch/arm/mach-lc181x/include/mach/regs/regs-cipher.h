#ifndef __ASM_ARCH_REGS_CIPHER_H
#define __ASM_ARCH_REGS_CIPHER_H

/* AES. */
#define CIPHER_AES_START						(0x0)
#define CIPHER_AES_CTL							(0x4)
#define CIPHER_AES_INTR							(0x8)
#define CIPHER_AES_INTE							(0xC)
#define CIPHER_AES_INTS							(0x10)
#define CIPHER_AES_KEY_LEN						(0x14)
#define CIPHER_AES_KEY_UPDATE						(0x18)
#define CIPHER_AES_BLK_NUM						(0x1C)	
#define CIPHER_AES_SADDR						(0x20)
#define CIPHER_AES_CUR_SAR						(0x24)	
#define CIPHER_AES_TADDR						(0x30)
#define CIPHER_AES_CUR_TAR						(0x34)
#define CIPHER_AES_IN0							(0x40)
#define CIPHER_AES_IN1							(0x44)
#define CIPHER_AES_IN2							(0x48)
#define CIPHER_AES_IN3							(0x4C)
#define CIPHER_AES_OUT0							(0x50)
#define CIPHER_AES_OUT1							(0x54)
#define CIPHER_AES_OUT2							(0x58)
#define CIPHER_AES_OUT3							(0x5C)
#define CIPHER_AES_KEY0							(0x60)
#define CIPHER_AES_KEY1							(0x64)
#define CIPHER_AES_KEY2							(0x68)
#define CIPHER_AES_KEY3							(0x6C)
#define CIPHER_AES_KEY4							(0x70)
#define CIPHER_AES_KEY5							(0x74)
#define CIPHER_AES_KEY6							(0x78)
#define CIPHER_AES_KEY7							(0x7C)
#define CIPHER_AES_KEY_MASK0						(0x80)
#define CIPHER_AES_KEY_MASK1						(0x84)
#define CIPHER_AES_KEY_MASK2						(0x88)
#define CIPHER_AES_KEY_MASK3						(0x8C)
#define CIPHER_AES_KEY_MASK4						(0x90)
#define CIPHER_AES_KEY_MASK5						(0x94)
#define CIPHER_AES_KEY_MASK6						(0x98)
#define CIPHER_AES_KEY_MASK7						(0x9C)

/* SHA. */
#define CIPHER_SHA_CTL							(0x0)
#define CIPHER_SHA_IN_TYPE						(0x4)
#define CIPHER_SHA_MOD							(0x8)
#define CIPHER_SHA_INTR							(0xC)
#define CIPHER_SHA_INTE							(0x10)
#define CIPHER_SHA_INTS							(0x14)
#define CIPHER_SHA_SADDR						(0x18)
#define CIPHER_SHA_CUR_SAR						(0x1C)
#define CIPHER_SHA_LINE_NUM						(0x20)
#define CIPHER_SHA_W0							(0x24)
#define CIPHER_SHA_W1							(0x28)
#define CIPHER_SHA_W2							(0x2C)
#define CIPHER_SHA_W3							(0x30)
#define CIPHER_SHA_W4							(0x34)
#define CIPHER_SHA_W5							(0x38)
#define CIPHER_SHA_W6							(0x3C)
#define CIPHER_SHA_W7							(0x40)
#define CIPHER_SHA_W8							(0x44)
#define CIPHER_SHA_W9							(0x48)
#define CIPHER_SHA_W10							(0x4C)
#define CIPHER_SHA_W11							(0x50)
#define CIPHER_SHA_W12							(0x54)
#define CIPHER_SHA_W13							(0x58)
#define CIPHER_SHA_W14							(0x5C)
#define CIPHER_SHA_W15							(0x60)
#define CIPHER_SHA_H0							(0x64)
#define CIPHER_SHA_H1							(0x68)   
#define CIPHER_SHA_H2							(0x6C)
#define CIPHER_SHA_H3							(0x70) 
#define CIPHER_SHA_H4							(0x74)
#define CIPHER_SHA_H5							(0x78)   
#define CIPHER_SHA_H6							(0x7C)
#define CIPHER_SHA_H7							(0x80)

#endif /* __ASM_ARCH_REGS_CIPHER_H */
