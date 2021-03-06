/**
 * @file user/test/test.c
 *
 * @author Hiroyuki Chishiro
 */
#include <mcube/mcube.h>

int user_test_main(__unused int argc, __unused char *argv[])
{
#if 0
  test_atomic();
  test_bitmap();
  test_debug();
  test_ext2();
  test_hash();
  test_kmalloc();
  test_list();
  test_page_alloc();
  test_printk();
  test_ring_buf();
  test_socket(argc, argv);
  test_string();
  test_unrolled_list();
  test_vm();
#endif
  return 0;
}
