/**
 * @file kernel/main.c
 *
 * @author Hiroyuki Chishiro
 */
#include <mcube/mcube.h>

#if CONFIG_ARCH_AXIS && CONFIG_COMPILER_CLANG
/* NOTE: padding to separate banks of text and data. */
char padding[0x1000] = {1};
#endif

unsigned int Debug = FALSE;
//unsigned int Debug = TRUE;

unsigned long CPU_CLOCK;
unsigned long CPU_CLOCK_MHZ_PER_USEC;
#if !CONFIG_ARCH_AXIS
double CPU_USEC_PER_CLOCK_MHZ;
double CPU_CLOCK_MHZ_PER_NSEC;
double CPU_NSEC_PER_CLOCK_MHZ;
#endif /* !CONFIG_ARCH_AXIS */

static unsigned int is_initialized = FALSE;

int main(int argc, char *argv[])
{
  unsigned long cpu = get_cpu_id();
#if CONFIG_ARCH_AXIS
  /* local cpu id in AXIS is in [0, 7]. */
  cpu &= 0x7;
#endif
  if (cpu == 0) {
    init_arch();
    is_initialized = TRUE;
    printk("main()\n");
    init_rq();
    printk("main()2\n");
    init_sched();
    printk("main()3\n");
    //    printk("%13lx\n", 0x1234);
    
    user_main();
    exit_arch();
    //    printk("main()4\n");
  } else {
    printk("get_cpu_id() = %lu\n", get_cpu_id());
    /* wait until init_arch() is finished. */
    while (is_initialized == FALSE) {
    }
    /* do application processor's specific code. */
    ap_main();
  }
  return 0;
}
