/**
 * @file include/sim/cpu.h
 *
 * @author Hiroyuki Chishiro
 */
#ifndef __MCUBE_SIM_CPU_H__
#define __MCUBE_SIM_CPU_H__

#define USER_LEVEL 0
#define KERNEL_LEVEL 3

#define REG_LENGTH 64


#ifndef __ASSEMBLY__


extern unsigned long current_cpu;

/**
 * @struct cpuid_info
 * @brief CPU ID information
 */
struct cpuid_info {
  /** EAX register. */
  unsigned int eax;
  /** EBX register. */
  unsigned int ebx;
  /** ECX register. */
  unsigned int ecx;
  /** EDX register. */
  unsigned int edx;
};

typedef struct cpuid_info cpuid_info;

int get_nr_cpu_cores(void);


#define get_cpu_id() current_cpu

#endif /* !__ASSEMBLY__ */

#endif /* __MCUBE_SIM_CPU_H__ */
