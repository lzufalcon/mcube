/**
 * @file arch/arm/thread.c
 *
 * @author Hiroyuki Chishiro
 */
#include <mcube/mcube.h>


struct pt_regs pt_regs[NR_INTRA_KERNEL_CPUS];


/**
 * The run_user_thread() function runs user thread.
 */
void __attribute__((noreturn)) run_user_thread(void)
{
  size_t cpu = get_cpu_id();
  void *ret = NULL;
  //  print("begin_user_thread()\n");
  if (current_th[cpu]->run_user_func) {
    ret = (*current_th[cpu]->run_user_func)(current_th[cpu]->arg);
  }
  if (ret) {
    print("ret = 0x%lx\n", (unsigned long) ret);
  }
  wfi();
  inf_loop();
}


void __attribute__((noreturn)) exit(int status)
{
	for (;;)
		;
}

void wait(unsigned long count)
{
}
