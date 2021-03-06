/**
 * @file user/sim/user_sim.c
 *
 * @author Hiroyuki Chishiro
 */
#include <mcube/mcube.h>

int user_ap_main(__unused int argc, __unused char *argv[])
{
  unsigned long cpu = get_cpu_id();
  putchar(cpu + '0');
  print("user_ap_main()\n");
  print("get_cpu_id() = %lu\n", get_cpu_id());
  //  print("ap_main()\n");
  //  cpu_ids[cpu] = cpu;
  return 0;
}


int user_arch_main(__unused int argc, __unused char *argv[])
{
  //  printk("user_arch_main(): %lf\n", 1.0);
  //  printk("user_arch_main(): %020.5lf\n", 12.34567890);
  //  test_socket(argc, argv);
  return 0;
}
