/*
**
** Use of source code is subject to the terms of the LeadCore license agreement under
** which you licensed source code. If you did not accept the terms of the license agreement,
** you are not authorized to use source code. For the terms of the license, please see the
** license agreement between you and LeadCore.
**
** Copyright (c) 2010 LeadCoreTech Corp.
**
**	PURPOSE: This files contains the mfp config.
**
**	CHANGE HISTORY:
**
**	Version		Date		Author		Description
**	1.0.0		2011-11-22	lengyansong	created
**
*/

#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/io.h>
#include <plat/mfp.h>

struct mfp mfp_pin_list[] = {
	{MFP_PIN_GPIO(0),   0,   0, MFP_PIN_GPIO_ONLY},
	{MFP_PIN_GPIO(1),   0,   0, MFP_PIN_GPIO_ONLY},
	{MFP_PIN_GPIO(2),   0,   0, MFP_PIN_GPIO_ONLY},
	{MFP_PIN_GPIO(3),   0,   0, MFP_PIN_GPIO_ONLY},
	{MFP_PIN_GPIO(4),   0,   0, MFP_PIN_GPIO_ONLY},
	{MFP_PIN_GPIO(5),   0,   0, MFP_PIN_GPIO_ONLY},
	{MFP_PIN_GPIO(6),   0,   0, MFP_PIN_GPIO_ONLY},
	{MFP_PIN_GPIO(7),   0,   0, MFP_PIN_GPIO_ONLY},
	{MFP_PIN_GPIO(8),   0,   0, MFP_PIN_GPIO_ONLY},
	{MFP_PIN_GPIO(9),   0,   0, MFP_PIN_GPIO_ONLY},
	{MFP_PIN_GPIO(10),  0,   0, MFP_PIN_GPIO_ONLY},
	{MFP_PIN_GPIO(11),  0,   0, MFP_PIN_GPIO_ONLY},
	{MFP_PIN_GPIO(12),  0,   0, MFP_PIN_GPIO_ONLY},
	{MFP_PIN_GPIO(13),  0,   0, 0},
	{MFP_PIN_GPIO(14),  220, 2, 0},
	{MFP_PIN_GPIO(15),  219, 2, 0},
	{MFP_PIN_GPIO(16),  46, 2, 0},
	{MFP_PIN_GPIO(17),  47, 2, 0},
	{MFP_PIN_GPIO(18),  48, 2, 0},
	{MFP_PIN_GPIO(19),  49, 2, 0},
	{MFP_PIN_GPIO(20),  194, 2, 0},
	{MFP_PIN_GPIO(21),  193, 2, 0},
	{MFP_PIN_GPIO(22),  192, 2, 0},
	{MFP_PIN_GPIO(23),  191, 2, 0},
	{MFP_PIN_GPIO(24),  190, 0, 0},
	{MFP_PIN_GPIO(25),  94,  0, 0},
	{MFP_PIN_GPIO(26),  217,  2, 0},
	{MFP_PIN_GPIO(27),  218,  2, 0},
	{MFP_PIN_GPIO(28),  216,  2, 0},
	{MFP_PIN_GPIO(29),  0,   0, 0},
	{MFP_PIN_GPIO(30),  0,   0, 0},
	{MFP_PIN_GPIO(31),  0,   0, 0},
	{MFP_PIN_GPIO(32),  7,   2, 0},
	{MFP_PIN_GPIO(33),  8,   2, 0},
	{MFP_PIN_GPIO(34),  0,   0, 0},
	{MFP_PIN_GPIO(35),  0,   0, 0},
	{MFP_PIN_GPIO(36),  0,   0, 0},
	{MFP_PIN_GPIO(37),  0,   0, 0},
	{MFP_PIN_GPIO(38),  0,   0, 0},
	{MFP_PIN_GPIO(39),  0,   0, 0},
	{MFP_PIN_GPIO(40),  0,   0, 0},
	{MFP_PIN_GPIO(41),  0,   0, 0},
	{MFP_PIN_GPIO(42),  0,   0, 0},
	{MFP_PIN_GPIO(43),  0,   0, 0},
	{MFP_PIN_GPIO(44),  19,  2, 0},
	{MFP_PIN_GPIO(45),  20,  2, 0},
	{MFP_PIN_GPIO(46),  21,  2, 0},
	{MFP_PIN_GPIO(47),  22,  2, 0},
	{MFP_PIN_GPIO(48),  23,  2, 0},
	{MFP_PIN_GPIO(49),  0,   0, 0},
	{MFP_PIN_GPIO(50),  0,   0, 0},
	{MFP_PIN_GPIO(51),  0,   0, 0},
	{MFP_PIN_GPIO(52),  0,   0, 0},
	{MFP_PIN_GPIO(53),  0,   0, 0},
	{MFP_PIN_GPIO(54),  0,   0, 0},
	{MFP_PIN_GPIO(55),  0,   0, 0},
	{MFP_PIN_GPIO(56),  0,   0, 0},
	{MFP_PIN_GPIO(57),  0,   0, 0},
	{MFP_PIN_GPIO(58),  0,   0, 0},
	{MFP_PIN_GPIO(59),  34,  2, 0},
	{MFP_PIN_GPIO(60),  35,  2, 0},
	{MFP_PIN_GPIO(61),  36,  2, 0},
	{MFP_PIN_GPIO(62),  37,  2, 0},
	{MFP_PIN_GPIO(63),  38,  2, 0},
	{MFP_PIN_GPIO(64),  39,  2, 0},
	{MFP_PIN_GPIO(65),  40,  2, 0},
	{MFP_PIN_GPIO(66),  41,  2, 0},
	{MFP_PIN_GPIO(67),  42,  2, 0},
	{MFP_PIN_GPIO(68),  43,  2, 0},
	{MFP_PIN_GPIO(69),  44,  2, 0},
	{MFP_PIN_GPIO(70),  45,  2, 0},
	{MFP_PIN_GPIO(71),  200, 2, 0},
	{MFP_PIN_GPIO(72),  201, 2, 0},
	{MFP_PIN_GPIO(73),  202, 2, 0},
	{MFP_PIN_GPIO(74),  203, 2, 0},
	{MFP_PIN_GPIO(75),  204, 2, 0},
	{MFP_PIN_GPIO(76),  205, 2, 0},
	{MFP_PIN_GPIO(77),  206, 2, 0},
	{MFP_PIN_GPIO(78),  207, 2, 0},
	{MFP_PIN_GPIO(79),  208, 2, 0},
	{MFP_PIN_GPIO(80),  209, 2, 0},
	{MFP_PIN_GPIO(81),  210, 2, 0},
	{MFP_PIN_GPIO(82),  211, 2, 0},
	{MFP_PIN_GPIO(83),  212, 2, 0},
	{MFP_PIN_GPIO(84),  213, 2, 0},
	{MFP_PIN_GPIO(85),  214, 2, 0},
	{MFP_PIN_GPIO(86),  215, 2, 0},
	{MFP_PIN_GPIO(87),  82,  2, 0},
	{MFP_PIN_GPIO(88),  83,  2, 0},
	{MFP_PIN_GPIO(89),  106, 2, 0},
	{MFP_PIN_GPIO(90),  237, 2, 0},
	{MFP_PIN_GPIO(91),  238, 2, 0},
	{MFP_PIN_GPIO(92),  239, 2, 0},
	{MFP_PIN_GPIO(93),  240,   2, 0},
	{MFP_PIN_GPIO(94),  241,   2, 0},
	{MFP_PIN_GPIO(95),  0,   0, 0},
	{MFP_PIN_GPIO(96),  54,  2, 0},
	{MFP_PIN_GPIO(97),  55,  2, 0},
	{MFP_PIN_GPIO(98),  56,  2, 0},
	{MFP_PIN_GPIO(99),  57,  2, 0},
	{MFP_PIN_GPIO(100), 58,  2, 0},
	{MFP_PIN_GPIO(101), 59,  2, 0},
	{MFP_PIN_GPIO(102), 0,   0, 0},
	{MFP_PIN_GPIO(103), 0,   0, 0},
	{MFP_PIN_GPIO(104), 0,   0, 0},
	{MFP_PIN_GPIO(105), 0,   0, 0},
	{MFP_PIN_GPIO(106), 0,   0, 0},
	{MFP_PIN_GPIO(107), 0,   0, 0},
	{MFP_PIN_GPIO(108), 0,   0, 0},
	{MFP_PIN_GPIO(109), 67,  2, 0},
	{MFP_PIN_GPIO(110), 68,  2, 0},
	{MFP_PIN_GPIO(111), 69,  2, 0},
	{MFP_PIN_GPIO(112), 70,  2, 0},
	{MFP_PIN_GPIO(113), 71,  2, 0},
	{MFP_PIN_GPIO(114), 72,  2, 0},
	{MFP_PIN_GPIO(115), 73,  2, 0},
	{MFP_PIN_GPIO(116), 74,  2, 0},
	{MFP_PIN_GPIO(117), 75,  2, 0},
	{MFP_PIN_GPIO(118), 76,  2, 0},
	{MFP_PIN_GPIO(119), 77,  2, 0},
	{MFP_PIN_GPIO(120), 78,  2, 0},
	{MFP_PIN_GPIO(121), 79,  2, 0},
	{MFP_PIN_GPIO(122), 80,  2, 0},
	{MFP_PIN_GPIO(123), 81,  2, 0},
	{MFP_PIN_GPIO(124), 0,   0, 0},
	{MFP_PIN_GPIO(125), 0,   0, 0},
	{MFP_PIN_GPIO(126), 84,  2, 0},
	{MFP_PIN_GPIO(127), 85,  2, 0},
	{MFP_PIN_GPIO(128), 86,  2, 0},
	{MFP_PIN_GPIO(129), 87,  2, 0},
	{MFP_PIN_GPIO(130), 88,  2, 0},
	{MFP_PIN_GPIO(131), 89,  2, 0},
	{MFP_PIN_GPIO(132), 90,  2, 0},
	{MFP_PIN_GPIO(133), 95,  2, 0},
	{MFP_PIN_GPIO(134), 96,  2, 0},
	{MFP_PIN_GPIO(135), 97,  2, 0},
	{MFP_PIN_GPIO(136), 98,  2, 0},
	{MFP_PIN_GPIO(137), 100, 2, 0},
	{MFP_PIN_GPIO(138), 101, 2, 0},
	{MFP_PIN_GPIO(139), 102, 2, 0},
	{MFP_PIN_GPIO(140), 103, 2, 0},
	{MFP_PIN_GPIO(141), 104, 2, 0},
	{MFP_PIN_GPIO(142), 105, 2, 0},
	{MFP_PIN_GPIO(143), 0,   0, 0},
	{MFP_PIN_GPIO(144), 0,   0, 0},
	{MFP_PIN_GPIO(145), 108, 2, 0},
	{MFP_PIN_GPIO(146), 109, 2, 0},
	{MFP_PIN_GPIO(147), 110, 2, 0},
	{MFP_PIN_GPIO(148), 111, 2, 0},
	{MFP_PIN_GPIO(149), 112, 2, 0},
	{MFP_PIN_GPIO(150), 113, 2, 0},
	{MFP_PIN_GPIO(151), 114, 2, 0},
	{MFP_PIN_GPIO(152), 115, 2, 0},
	{MFP_PIN_GPIO(153), 116, 2, 0},
	{MFP_PIN_GPIO(154), 117, 2, 0},
	{MFP_PIN_GPIO(155), 118, 2, 0},
	{MFP_PIN_GPIO(156), 119, 2, 0},
	{MFP_PIN_GPIO(157), 120, 2, 0},
	{MFP_PIN_GPIO(158), 121, 2, 0},
	{MFP_PIN_GPIO(159), 122, 2, 0},
	{MFP_PIN_GPIO(160), 123, 2, 0},
	{MFP_PIN_GPIO(161), 124, 2, 0},
	{MFP_PIN_GPIO(162), 125, 2, 0},
	{MFP_PIN_GPIO(163), 126, 2, 0},
	{MFP_PIN_GPIO(164), 127, 2, 0},
	{MFP_PIN_GPIO(165), 128, 2, 0},
	{MFP_PIN_GPIO(166), 129, 2, 0},
	{MFP_PIN_GPIO(167), 130, 2, 0},
	{MFP_PIN_GPIO(168), 131, 2, 0},
	{MFP_PIN_GPIO(169), 132, 2, 0},
	{MFP_PIN_GPIO(170), 133, 2, 0},
	{MFP_PIN_GPIO(171), 134, 2, 0},
	{MFP_PIN_GPIO(172), 135, 2, 0},
	{MFP_PIN_GPIO(173), 139, 2, 0},
	{MFP_PIN_GPIO(174), 140, 2, 0},
	{MFP_PIN_GPIO(175), 141, 2, 0},
	{MFP_PIN_GPIO(176), 142, 2, 0},
	{MFP_PIN_GPIO(177), 143, 2, 0},
	{MFP_PIN_GPIO(178), 144, 2, 0},
	{MFP_PIN_GPIO(179), 145, 2, 0},
	{MFP_PIN_GPIO(180), 146, 2, 0},
	{MFP_PIN_GPIO(181), 147, 2, 0},
	{MFP_PIN_GPIO(182), 148, 2, 0},
	{MFP_PIN_GPIO(183), 149, 2, 0},
	{MFP_PIN_GPIO(184), 150, 2, 0},
	{MFP_PIN_GPIO(185), 151, 2, 0},
	{MFP_PIN_GPIO(186), 152, 2, 0},
	{MFP_PIN_GPIO(187), 153, 2, 0},
	{MFP_PIN_GPIO(188), 154, 2, 0},
	{MFP_PIN_GPIO(189), 155, 2, 0},
	{MFP_PIN_GPIO(190), 156, 2, 0},
	{MFP_PIN_GPIO(191), 157, 2, 0},
	{MFP_PIN_GPIO(192), 158, 2, 0},
	{MFP_PIN_GPIO(193), 159, 2, 0},
	{MFP_PIN_GPIO(194), 160, 2, 0},
	{MFP_PIN_GPIO(195), 161, 2, 0},
	{MFP_PIN_GPIO(196), 162, 2, 0},
	{MFP_PIN_GPIO(197), 0,   0, 0},
	{MFP_PIN_GPIO(198), 0,   0, 0},
	{MFP_PIN_GPIO(199), 0,   0, 0},
	{MFP_PIN_GPIO(200), 0,   0, 0},
	{MFP_PIN_GPIO(201), 0,   0, 0},
	{MFP_PIN_GPIO(202), 0,   0, 0},
	{MFP_PIN_GPIO(203), 0,   0, 0},
	{MFP_PIN_GPIO(204), 0,   0, 0},
	{MFP_PIN_GPIO(205), 0,   0, 0},
	{MFP_PIN_GPIO(206), 0,   0, 0},
	{MFP_PIN_GPIO(207), 0,   0, 0},
	{MFP_PIN_GPIO(208), 0,   0, 0},
	{MFP_PIN_GPIO(209), 222, 2, 0},
	{MFP_PIN_GPIO(210), 223, 2, 0},
	{MFP_PIN_GPIO(211), 224, 2, 0},
	{MFP_PIN_GPIO(212), 225, 2, 0},
	{MFP_PIN_GPIO(213), 226, 2, 0},
	{MFP_PIN_GPIO(214), 227, 2, 0},
	{MFP_PIN_GPIO(215), 228, 2, 0},
	{MFP_PIN_GPIO(216), 180, 2, 0},
	{MFP_PIN_GPIO(217), 181, 2, 0},
	{MFP_PIN_GPIO(218), 182, 2, 0},
	{MFP_PIN_GPIO(219), 183, 2, 0},
	{MFP_PIN_GPIO(220), 184, 2, 0},
	{MFP_PIN_GPIO(221), 185, 2, 0},
	{MFP_PIN_GPIO(222), 186, 2, 0},
	{MFP_PIN_GPIO(223), 187, 2, 0},
	{MFP_PIN_GPIO(224), 188, 2, 0},
	{MFP_PIN_GPIO(225), 189, 2, 0},
	{MFP_PIN_GPIO(226), 136, 2, 0},
	{MFP_PIN_GPIO(227), 137, 2, 0},
	{MFP_PIN_GPIO(228), 138, 2, 0},
	{MFP_PIN_GPIO(229), 91,  2, 0},
	{MFP_PIN_GPIO(230), 92,  2, 0},
	{MFP_PIN_GPIO(231), 0,   0, 0},
	{MFP_PIN_GPIO(232), 0,   0, MFP_PIN_GPIO_ONLY},
	{MFP_PIN_GPIO(233), 0,   0, MFP_PIN_GPIO_ONLY},
	{MFP_PIN_GPIO(234), 0,   0, MFP_PIN_GPIO_ONLY},
	{MFP_PIN_GPIO(235), 0,   0, 0},
	{MFP_PIN_GPIO(236), 0,   0, 0},
	{MFP_PIN_GPIO(237), 0,   0, 0},
	{MFP_PIN_GPIO(238), 0,   0, 0},
	{MFP_PIN_GPIO(239), 0,   0, MFP_PIN_GPIO_ONLY},
	{MFP_PIN_GPIO(240), 0,   0, MFP_PIN_GPIO_ONLY},
	{MFP_PIN_GPIO(241), 233, 2, 0},
	{MFP_PIN_GPIO(242), 234, 2, 0},

	{MFP_PIN_GPIO16_2,  0,   0, 0},
	{MFP_PIN_GPIO17_2,  0,   0, 0},
	{MFP_PIN_GPIO18_2,  0,   0, 0},
	{MFP_PIN_GPIO19_2,  0,   0, 0},
	{MFP_PIN_GPIO191_2, 0,   0, 0},
	{MFP_PIN_GPIO192_2, 0,   0, 0},

	{MFP_PIN_NAND_TBALL_0, 0,   0, 0},
	{MFP_PIN_NAND_TBALL_1, 0,   0, 0},
	{MFP_PIN_NAND_TBALL_2, 0,   0, 0},
	{MFP_PIN_NAND_TBALL_3, 0,   0, 0},
	{MFP_PIN_NAND_TBALL_4, 0,   0, 0},
};

struct mfp_pull mfp_pull_list[] = {
	{MFP_PULL_TD_DATA0_0, 	   MFP_PULL_DOWN_CAP, 0, 22, 0, 0},
	{MFP_PULL_TD_DATA0_1, 	   MFP_PULL_DOWN_CAP, 0, 21, 0, 0},
	{MFP_PULL_TD_DATA0_2, 	   MFP_PULL_DOWN_CAP, 0, 20, 0, 0},
	{MFP_PULL_TD_DATA0_3, 	   MFP_PULL_DOWN_CAP, 0, 19, 0, 0},
	{MFP_PULL_TD_DATA0_4, 	   MFP_PULL_DOWN_CAP, 0, 18, 0, 0},
	{MFP_PULL_TD_DATA0_5, 	   MFP_PULL_DOWN_CAP, 0, 17, 0, 0},
	{MFP_PULL_TD_DATA0_6, 	   MFP_PULL_DOWN_CAP, 0, 16, 0, 0},
	{MFP_PULL_TD_DATA0_7, 	   MFP_PULL_DOWN_CAP, 0, 15, 0, 0},
	{MFP_PULL_TD_DATA0_8, 	   MFP_PULL_DOWN_CAP, 0, 14, 0, 0},
	{MFP_PULL_TD_DATA0_9, 	   MFP_PULL_DOWN_CAP, 0, 13, 0, 0},
	{MFP_PULL_OSC_EN1,    	   MFP_PULL_DOWN_CAP, 0, 12, 0, 0},
	{MFP_PULL_CLK26M_IN1, 	   MFP_PULL_DOWN_CAP, 0, 11, 0, 0},
	{MFP_PULL_GSM0_DIGRF_DEN,  MFP_PULL_DOWN_CAP, 0, 1, 0, 0},
	{MFP_PULL_GSM0_DIGRF_D,    MFP_PULL_DOWN_CAP, 0, 0, 0, 0},
	{MFP_PULL_GSM0_GPO, 	   MFP_PULL_DOWN_CAP, 7, 12, 0, 0},
	{MFP_PULL_GSM0_SW_GPO0,    MFP_PULL_DOWN_CAP, 1, 31, 0, 0},
	{MFP_PULL_GSM0_SW_GPO1,    MFP_PULL_DOWN_CAP, 1, 30, 0, 0},
	{MFP_PULL_GSM0_SW_GPO2,    MFP_PULL_DOWN_CAP, 1, 29, 0, 0},
	{MFP_PULL_GSM0_SW_GPO3,    MFP_PULL_DOWN_CAP, 1, 28, 0, 0},
	{MFP_PULL_TD_GPO0, 	   MFP_PULL_DOWN_CAP, 1, 27, 0, 0},
	{MFP_PULL_TD_GPO1, 	   MFP_PULL_DOWN_CAP, 1, 26, 0, 0},
	{MFP_PULL_TD_GPO2, 	   MFP_PULL_DOWN_CAP, 1, 25, 0, 0},
	{MFP_PULL_TD_GPO3, 	   MFP_PULL_DOWN_CAP, 1, 24, 0, 0},
	{MFP_PULL_TD_GPO4, 	   MFP_PULL_DOWN_CAP, 1, 23, 0, 0},
	{MFP_PULL_TD_GPO5, 	   MFP_PULL_DOWN_CAP, 1, 22, 0, 0},
	{MFP_PULL_TD_GPO6, 	   MFP_PULL_DOWN_CAP, 1, 21, 0, 0},
	{MFP_PULL_TD_GPO7, 	   MFP_PULL_DOWN_CAP, 1, 20, 0, 0},
	{MFP_PULL_TD_GPO8, 	   MFP_PULL_DOWN_CAP, 1, 19, 0, 0},
	{MFP_PULL_TD_GPO9, 	   MFP_PULL_DOWN_CAP, 1, 18, 0, 0},
	{MFP_PULL_TD_GPO10, 	   MFP_PULL_DOWN_CAP, 1, 17, 0, 0},
	{MFP_PULL_TD_GPO11, 	   MFP_PULL_DOWN_CAP, 1, 16, 0, 0},
	{MFP_PULL_TD_SPI_CS2, 	   MFP_PULL_DOWN_CAP, 1, 5, 0, 0},
	{MFP_PULL_TD_SPI_CS0, 	   MFP_PULL_DOWN_CAP, 1, 4, 0, 0},
	{MFP_PULL_TD_SPI_CLK, 	   MFP_PULL_DOWN_CAP, 1, 3, 0, 0},
	{MFP_PULL_TD_SPI_DOUT, 	   MFP_PULL_DOWN_CAP, 1, 2, 0, 0},
	{MFP_PULL_TD_SPI_DIN, 	   MFP_PULL_DOWN_CAP, 1, 1, 0, 0},
	{MFP_PULL_ISP_FSIN1, 	   MFP_PULL_DOWN_CAP, 2, 25, 0, 0},
	{MFP_PULL_ISP_FSIN0, 	   MFP_PULL_DOWN_CAP, 2, 24, 0, 0},
	{MFP_PULL_CLK26_SEL,    MFP_PULL_DOWN_CAP,   2, 22, 0, 0},
	{MFP_PULL_KB_DKI_2, 	   MFP_PULL_UP_CAP,   2, 14, 0, 0},
	{MFP_PULL_KB_DKI_3, 	   MFP_PULL_UP_CAP,   2, 13, 0, 0},
	{MFP_PULL_KB_DKI_4, 	   MFP_PULL_UP_CAP,   2, 12, 0, 0},
	{MFP_PULL_KB_DKI_5, 	   MFP_PULL_UP_CAP,   2, 11, 0, 0},
	{MFP_PULL_KB_DKI_6, 	   MFP_PULL_UP_CAP,   2, 10, 0, 0},
	{MFP_PULL_KB_DKI_7, 	   MFP_PULL_DOWN_CAP,   2, 9, 0, 0},
	{MFP_PULL_COM_UART_RX, 	   MFP_PULL_UP_CAP,   4, 2, 0, 0},
	{MFP_PULL_COM_UART_TX, 	   MFP_PULL_UP_CAP,   4, 1, 0, 0},
	{MFP_PULL_UART1_RTS, 	   MFP_PULL_DOWN_CAP, 4, 0, 0, 0},
	{MFP_PULL_UART1_CTS, 	   MFP_PULL_UP_CAP,   3, 31, 0, 0},
	{MFP_PULL_UART1_RX, 	   MFP_PULL_UP_CAP,   3, 30, 0, 0},
	{MFP_PULL_UART1_TX, 	   MFP_PULL_UP_CAP,   3, 29, 0, 0},
	{MFP_PULL_UART2_RTS, 	   MFP_PULL_DOWN_CAP, 3, 28, 0, 0},
	{MFP_PULL_UART2_CTS, 	   MFP_PULL_UP_CAP,   3, 27, 0, 0},
	{MFP_PULL_UART2_RX, 	   MFP_PULL_UP_CAP,   3, 26, 0, 0},
	{MFP_PULL_UART2_TX, 	   MFP_PULL_UP_CAP,   3, 25, 0, 0},
	{MFP_PULL_PWM_0, 	   MFP_PULL_DOWN_CAP, 3, 24, 0, 0},
	{MFP_PULL_NAND_OEN, 	   MFP_PULL_UP_CAP,   3, 13, 0, 0},
	{MFP_PULL_NAND_WEN, 	   MFP_PULL_UP_CAP,   3, 12, 0, 0},
	{MFP_PULL_NAND_IO_0, 	   MFP_PULL_DOWN_CAP, 3, 9, 0, 0},
	{MFP_PULL_NAND_IO_1, 	   MFP_PULL_DOWN_CAP, 3, 8, 0, 0},
	{MFP_PULL_NAND_IO_2, 	   MFP_PULL_DOWN_CAP, 3, 7, 0, 0},
	{MFP_PULL_NAND_IO_3, 	   MFP_PULL_DOWN_CAP, 3, 6, 0, 0},
	{MFP_PULL_NAND_IO_4, 	   MFP_PULL_DOWN_CAP, 3, 5, 0, 0},
	{MFP_PULL_NAND_IO_5, 	   MFP_PULL_DOWN_CAP, 3, 4, 0, 0},
	{MFP_PULL_NAND_IO_6, 	   MFP_PULL_DOWN_CAP, 3, 3, 0, 0},
	{MFP_PULL_NAND_IO_7, 	   MFP_PULL_DOWN_CAP, 3, 2, 0, 0},
	{MFP_PULL_NAND_IO_8, 	   MFP_PULL_DOWN_CAP, 3, 1, 0, 0},
	{MFP_PULL_NAND_IO_9, 	   MFP_PULL_DOWN_CAP, 3, 0, 0, 0},
	{MFP_PULL_NAND_IO_10, 	   MFP_PULL_DOWN_CAP, 2, 31, 0, 0},
	{MFP_PULL_NAND_IO_11, 	   MFP_PULL_DOWN_CAP, 2, 30, 0, 0},
	{MFP_PULL_NAND_IO_12, 	   MFP_PULL_DOWN_CAP, 2, 29, 0, 0},
	{MFP_PULL_NAND_IO_13, 	   MFP_PULL_DOWN_CAP, 2, 28, 0, 0},
	{MFP_PULL_NAND_IO_14, 	   MFP_PULL_DOWN_CAP, 2, 27, 0, 0},
	{MFP_PULL_NAND_IO_15, 	   MFP_PULL_DOWN_CAP, 2, 26, 0, 0},
	{MFP_PULL_I2S0_WS, 	   MFP_PULL_UP_CAP,   4, 30, 0, 0},
	{MFP_PULL_I2S0_SCLK, 	   MFP_PULL_DOWN_CAP, 4, 29, 0, 0},
	{MFP_PULL_I2S0_SDOUT, 	   MFP_PULL_DOWN_CAP, 4, 28, 0, 0},
	{MFP_PULL_I2S0_SDIN, 	   MFP_PULL_DOWN_CAP, 4, 27, 0, 0},
	{MFP_PULL_COM_PCM_SSN, 	   MFP_PULL_UP_CAP,   4, 26, 0, 0},
	{MFP_PULL_COM_PCM_CLK, 	   MFP_PULL_DOWN_CAP, 4, 25, 0, 0},
	{MFP_PULL_COM_PCM_RX, 	   MFP_PULL_DOWN_CAP, 4, 24, 0, 0},
	{MFP_PULL_COM_PCM_TX, 	   MFP_PULL_DOWN_CAP, 4, 23, 0, 0},
	{MFP_PULL_COM_PCM0_SSN,    MFP_PULL_UP_CAP,   4, 22, 0, 0},
	{MFP_PULL_COM_PCM0_CLK,    MFP_PULL_DOWN_CAP, 4, 21, 0, 0},
	{MFP_PULL_COM_PCM0_RX, 	   MFP_PULL_DOWN_CAP, 4, 20, 0, 0},
	{MFP_PULL_COM_PCM0_TX, 	   MFP_PULL_DOWN_CAP, 4, 19, 0, 0},
	{MFP_PULL_BOOT_CTL_0, 	   MFP_PULL_DOWN_CAP, 4, 18, 0, 0},
	{MFP_PULL_BOOT_CTL_1, 	   MFP_PULL_DOWN_CAP, 4, 17, 0, 0},
	{MFP_PULL_BOOT_CTL_2, 	   MFP_PULL_UP_CAP,   4, 16, 0, 0},
	{MFP_PULL_SSI2_SSN, 	   MFP_PULL_UP_CAP,   4, 15, 0, 0},
	{MFP_PULL_SSI2_CLK, 	   MFP_PULL_UP_CAP,   4, 14, 0, 0},
	{MFP_PULL_SSI2_RX, 	   MFP_PULL_DOWN_CAP, 4, 13, 0, 0},
	{MFP_PULL_SSI2_TX, 	   MFP_PULL_DOWN_CAP, 4, 12, 0, 0},
	{MFP_PULL_SSI1_SSN, 	   MFP_PULL_UP_CAP,   4, 11, 0, 0},
	{MFP_PULL_SSI1_CLK, 	   MFP_PULL_DOWN_CAP, 4, 10, 0, 0},
	{MFP_PULL_SSI1_RX, 	   MFP_PULL_DOWN_CAP, 4, 9, 0, 0},
	{MFP_PULL_SSI1_TX, 	   MFP_PULL_DOWN_CAP, 4, 8, 0, 0},
	{MFP_PULL_SSI0_SSN_0, 	   MFP_PULL_UP_CAP,   4, 7, 0, 0},
	{MFP_PULL_SSI0_SSN_1, 	   MFP_PULL_UP_CAP,   4, 6, 0, 0},
	{MFP_PULL_SSI0_CLK, 	   MFP_PULL_DOWN_CAP, 4, 5, 0, 0},
	{MFP_PULL_SSI0_RX, 	   MFP_PULL_DOWN_CAP, 4, 4, 0, 0},
	{MFP_PULL_SSI0_TX, 	   MFP_PULL_DOWN_CAP, 4, 3, 0, 0},
	{MFP_PULL_SEC_SW, 	   MFP_PULL_DOWN_CAP, 5, 31, 0, 0},
	{MFP_PULL_SEC_SMC, 	   MFP_PULL_DOWN_CAP, 5, 30, 0, 0},
	{MFP_PULL_GPIO_D_24,	   MFP_PULL_DOWN_CAP, 5, 29, 0, 0},
	{MFP_PULL_JTAG1_NTRS, 	   MFP_PULL_UP_CAP,   5, 28, 0, 0},
	{MFP_PULL_JTAG1_TMS, 	   MFP_PULL_UP_CAP,   5, 27, 0, 0},
	{MFP_PULL_JTAG1_TDO, 	   MFP_PULL_UP_CAP,   5, 26, 0, 0},
	{MFP_PULL_JTAG1_TDI, 	   MFP_PULL_DOWN_CAP, 5, 25, 0, 0},
	{MFP_PULL_JTAG1_TCK, 	   MFP_PULL_DOWN_CAP, 5, 24, 0, 0},
	{MFP_PULL_JTAG0_NTRS, 	   MFP_PULL_UP_CAP,   5, 23, 0, 0},
	{MFP_PULL_JTAG0_TMS, 	   MFP_PULL_DOWN_CAP, 5, 22, 0, 0},
	{MFP_PULL_JTAG0_TDO, 	   MFP_PULL_UP_CAP,   5, 21, 0, 0},
	{MFP_PULL_JTAG0_TDI, 	   MFP_PULL_DOWN_CAP, 5, 20, 0, 0},
	{MFP_PULL_JTAG0_TCK, 	   MFP_PULL_DOWN_CAP, 5, 19, 0, 0},
	{MFP_PULL_SIM1_IO, 	   MFP_PULL_UP_CAP,   5, 6, 0, 0},
	{MFP_PULL_SIM0_IO, 	   MFP_PULL_UP_CAP,   5, 5, 0, 0},
	{MFP_PULL_I2C1_SDA, 	   MFP_PULL_UP_CAP,   5, 4, 0, 0},
	{MFP_PULL_I2C1_SCL, 	   MFP_PULL_UP_CAP,   5, 3, 0, 0},
	{MFP_PULL_I2C0_SDA, 	   MFP_PULL_UP_CAP,   5, 2, 0, 0},
	{MFP_PULL_I2C0_SCL, 	   MFP_PULL_UP_CAP,   5, 1, 0, 0},
	{MFP_PULL_COM_I2C_SDA, 	   MFP_PULL_UP_CAP,   5, 0, 0, 0},
	{MFP_PULL_COM_I2C_SCL, 	   MFP_PULL_UP_CAP,   4, 31, 0, 0},
	{MFP_PULL_ISP_I2C_SDA, 	   MFP_PULL_UP_CAP,   7, 5, 0, 0},
	{MFP_PULL_ISP_I2C_SCL, 	   MFP_PULL_UP_CAP,   7, 4, 0, 0},
	{MFP_PULL_ISP_S_VSYNC, 	   MFP_PULL_DOWN_CAP, 7, 3, 0, 0},
	{MFP_PULL_ISP_S_HSYNC, 	   MFP_PULL_DOWN_CAP, 7, 2, 0, 0},
	{MFP_PULL_ISP_SCLK,	   MFP_PULL_DOWN_CAP, 7, 1, 0, 0},
	{MFP_PULL_ISP_S_DATA_0, 	   MFP_PULL_DOWN_CAP, 6, 1, 0, 0},
	{MFP_PULL_ISP_S_DATA_1, 	   MFP_PULL_DOWN_CAP, 6, 0, 0, 0},
	{MFP_PULL_ISP_S_DATA_2,    MFP_PULL_UP_CAP,   6, 30, 0, 0},
	{MFP_PULL_ISP_S_DATA_3,    MFP_PULL_UP_CAP,   6, 29, 0, 0},
	{MFP_PULL_ISP_S_DATA_4,    MFP_PULL_UP_CAP,   6, 28, 0, 0},
	{MFP_PULL_ISP_S_DATA_5,    MFP_PULL_DOWN_CAP, 6, 27, 0, 0},
	{MFP_PULL_ISP_S_DATA_6,    MFP_PULL_DOWN_CAP, 6, 26, 0, 0},
	{MFP_PULL_ISP_S_DATA_7,    MFP_PULL_DOWN_CAP, 6, 25, 0, 0},
	{MFP_PULL_ISP_S_DATA_8,    MFP_PULL_DOWN_CAP, 7, 0, 0, 0},
	{MFP_PULL_ISP_S_DATA_9,    MFP_PULL_DOWN_CAP, 6, 31, 0, 0},
	{MFP_PULL_ISP_STROBE, 	   MFP_PULL_DOWN_CAP, 6, 24, 0, 0},
	{MFP_PULL_ISP_SCLK0, 	   MFP_PULL_DOWN_CAP, 6, 23, 0, 0},
	{MFP_PULL_ISP_PWM, 	   MFP_PULL_DOWN_CAP, 6, 22, 0, 0},
	{MFP_PULL_ISP_PDWN1, 	   MFP_PULL_UP_CAP,   6, 7, 0, 0},
	{MFP_PULL_ISP_PDWN0, 	   MFP_PULL_UP_CAP,   6, 6, 0, 0},
	{MFP_PULL_ISP_RSTN1, 	   MFP_PULL_DOWN_CAP, 6, 5, 0, 0},
	{MFP_PULL_ISP_RSTN0, 	   MFP_PULL_DOWN_CAP, 6, 4, 0, 0},
	{MFP_PULL_GPIO_D_0, 	   MFP_PULL_DOWN_CAP, 6, 21, 0, 0},
	{MFP_PULL_GPIO_D_1, 	   MFP_PULL_DOWN_CAP, 6, 20, 0, 0},
	{MFP_PULL_GPIO_D_2, 	   MFP_PULL_DOWN_CAP, 6, 19, 0, 0},
	{MFP_PULL_GPIO_D_3, 	   MFP_PULL_DOWN_CAP, 6, 18, 0, 0},
	{MFP_PULL_GPIO_D_4, 	   MFP_PULL_DOWN_CAP, 6, 17, 0, 0},
	{MFP_PULL_GPIO_D_5, 	   MFP_PULL_DOWN_CAP, 6, 16, 0, 0},
	{MFP_PULL_GPIO_D_6, 	   MFP_PULL_DOWN_CAP, 6, 15, 0, 0},
	{MFP_PULL_GPIO_D_7, 	   MFP_PULL_DOWN_CAP, 6, 14, 0, 0},
	{MFP_PULL_GPIO_D_8, 	   MFP_PULL_DOWN_CAP, 6, 13, 0, 0},
	{MFP_PULL_GPIO_D_9, 	   MFP_PULL_DOWN_CAP, 6, 12, 0, 0},
	{MFP_PULL_GPIO_D_10, 	   MFP_PULL_DOWN_CAP, 6, 11, 0, 0},
	{MFP_PULL_GPIO_D_11, 	   MFP_PULL_DOWN_CAP, 6, 10, 0, 0},
	{MFP_PULL_GPIO_D_12, 	   MFP_PULL_DOWN_CAP, 6, 9, 0, 0},
	{MFP_PULL_GPIO_D_28, 	   MFP_PULL_UP_CAP, 6, 3, 0, 0},
	{MFP_PULL_GPIO_D_25, 	   MFP_PULL_DOWN_CAP, 6, 2, 0, 0},
	{MFP_PULL_GPIO_D_240, 	   MFP_PULL_DOWN_CAP, 7, 11, 0, 0},
	{MFP_PULL_GPIO_D_239, 	   MFP_PULL_DOWN_CAP, 7, 10, 0, 0},
	{MFP_PULL_GPIO_D_234, 	   MFP_PULL_DOWN_CAP, 7, 9, 0, 0},
	{MFP_PULL_GPIO_D_233, 	   MFP_PULL_DOWN_CAP, 7, 8, 0, 0},
	{MFP_PULL_GPIO_D_232, 	   MFP_PULL_DOWN_CAP, 7, 7, 0, 0},
	{MFP_PULL_MMC0_CMD,    	   MFP_PULL_ALL_CAP,  8, 13, 8, 12},
	{MFP_PULL_MMC0_DATA_3, 	   MFP_PULL_ALL_CAP,  8, 11, 8, 10},
	{MFP_PULL_MMC0_DATA_2, 	   MFP_PULL_UP_CAP,   8, 2, 0, 0},
	{MFP_PULL_MMC0_DATA_1, 	   MFP_PULL_UP_CAP,   8, 1, 0, 0},
	{MFP_PULL_MMC0_DATA_0, 	   MFP_PULL_UP_CAP,   8, 0, 0, 0},
	{MFP_PULL_MMC1_CMD,    	   MFP_PULL_UP_CAP,   9, 13, 0, 0},
	{MFP_PULL_MMC1_DATA_7,	   MFP_PULL_UP_CAP,   9, 7, 0, 0},
	{MFP_PULL_MMC1_DATA_6, 	   MFP_PULL_UP_CAP,   9, 6, 0, 0},
	{MFP_PULL_MMC1_DATA_5, 	   MFP_PULL_UP_CAP,   9, 5, 0, 0},
	{MFP_PULL_MMC1_DATA_4, 	   MFP_PULL_UP_CAP,   9, 4, 0, 0},
	{MFP_PULL_MMC1_DATA_3, 	   MFP_PULL_UP_CAP,   9, 11, 0, 0},
	{MFP_PULL_MMC1_DATA_2, 	   MFP_PULL_UP_CAP,   9, 2, 0, 0},
	{MFP_PULL_MMC1_DATA_1, 	   MFP_PULL_UP_CAP,   9, 1, 0, 0},
	{MFP_PULL_MMC1_DATA_0, 	   MFP_PULL_UP_CAP,   9, 0, 0, 0},
	{MFP_PULL_MMC2_CMD,    	   MFP_PULL_UP_CAP,   10, 13, 0, 0},
	{MFP_PULL_MMC2_DATA_3, 	   MFP_PULL_UP_CAP,   10, 11, 0, 0},
	{MFP_PULL_MMC2_DATA_2, 	   MFP_PULL_UP_CAP,   10, 2, 0, 0},
	{MFP_PULL_MMC2_DATA_1, 	   MFP_PULL_UP_CAP,   10, 1, 0, 0},
	{MFP_PULL_MMC2_DATA_0, 	   MFP_PULL_UP_CAP,   10, 0, 0, 0},
};

unsigned int mfp_pin_list_size = ARRAY_SIZE(mfp_pin_list);
unsigned int mfp_pull_list_size = ARRAY_SIZE(mfp_pull_list);
