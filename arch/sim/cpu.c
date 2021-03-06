/**
 * @file arch/sim/cpu.c
 *
 * @author Hiroyuki Chishiro
 */
#include <mcube/mcube.h>

/* NOTE: current_cpu == get_cpu_id() */
unsigned long current_cpu = 0;


void copy_arch_process(__unused struct task_struct *p,
                       __unused unsigned long func,
                       __unused unsigned long arg)
{
}


void set_cpu_clock(void)
{
  time_t base_time;
  uint64_t begin_clk, end_clk;
  base_time = time(NULL);

  while (base_time == time(NULL))
    ;

  begin_clk = rdtsc();

  base_time = time(NULL);

  do {
    end_clk = rdtsc();
  } while (base_time == time(NULL));

  CPU_CLOCK = end_clk - begin_clk;
  CPU_CLOCK_MHZ_PER_USEC = (CPU_CLOCK + 500 * 1000) / (1000 * 1000);
  CPU_USEC_PER_CLOCK_MHZ = (1.0 * 1000 * 1000) / CPU_CLOCK;
  CPU_CLOCK_MHZ_PER_NSEC = CPU_CLOCK / (1.0 * 1000 * 1000 * 1000);
  CPU_NSEC_PER_CLOCK_MHZ = (1.0 * 1000 * 1000 * 1000) / CPU_CLOCK;
  printk("CPU_CLOCK = %lu\n", CPU_CLOCK);
  printk("CPU_CLOCK_MHZ_PER_USEC = %lu\n", CPU_CLOCK_MHZ_PER_USEC);
}


void init_cpu(void)
{
  //  set_cpu_clock();
}
