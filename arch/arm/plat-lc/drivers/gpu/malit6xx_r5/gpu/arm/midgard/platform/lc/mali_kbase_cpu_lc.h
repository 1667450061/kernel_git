/*
 *
 * (C) COPYRIGHT ARM Limited. All rights reserved.
 *
 * This program is free software and is provided to you under the terms of the
 * GNU General Public License version 2 as published by the Free Software
 * Foundation, and any use by you of this program is subject to the terms
 * of such GNU licence.
 *
 * A copy of the licence is included with the program, and can also be obtained
 * from Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA  02110-1301, USA.
 *
 */





#ifndef _KBASE_CPU_LC_H_
#define _KBASE_CPU_LC_H_

/**
 * Versatile lc implementation of @ref kbase_cpuprops_clock_speed_function.
 */
int kbase_get_lc_cpu_clock_speed(u32 *cpu_clock);

int kbase_get_lc_gpu_clock_speed(u32 *clock_speed);

#endif				/* _KBASE_CPU_VEXPRESS_H_ */
