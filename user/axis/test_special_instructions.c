/**
 * @file user/test_special_instructions.c
 *
 * @author Hiroyuki Chishiro
 */
#include <mcube/mcube.h>

static void test_nop(void)
{
  printk("test_nop()\n");
  asm volatile("nop");
}

static void test_wi(void)
{
  /* TODO: implement interrupt setting and handler. */
  printk("test_wi()... nothing\n");
  //  asm volatile("wi");
}

static void test_sync(void)
{
  printk("test_sync()\n");
  asm volatile("sync");
}


static void test_ert(void)
{
  /* NOTE: MIPS's instrcution is eret. */
  /* TODO: implement interrupt setting and handler. */
  printk("test_ert()... nothing\n");
  //  asm volatile("ert");
}



void test_special_instructions(void)
{
  test_nop();
  test_wi();
  test_sync();
  test_ert();
}

