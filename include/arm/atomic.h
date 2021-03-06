/**
 * @file include/arm/atomic.h
 *
 * @author Hiroyuki Chishiro
 */
#ifndef __MCUBE_ARM_ATOMIC_H__
#define __MCUBE_ARM_ATOMIC_H__

#ifndef __ASSEMBLY__

static inline void compare_and_swap(volatile uint64_t *ptr, uint64_t new,
                                    uint64_t old)
{
  uint64_t tmp;
  //  printk("new = 0x%lx old = 0x%lx\n", new, old);
#if 1
  uint64_t oldval;
  //  asm volatile("prfm    pstl1strm, %0" :: "r"(&v->counter));
  asm volatile("1: ldaxr %x0, [%1]" : "=&r"(oldval) : "r"(ptr));
  asm volatile("eor %x0, %x1, %x2" : "=r"(tmp) : "r"(oldval), "r"(old));
  asm volatile("cbnz %x0, 2f" :: "r"(tmp));
  asm volatile("stxr %w0, %x2, [%1]" : "=&r"(tmp) : "r"(ptr), "r"(new));
  asm volatile("cbnz %x0, 1b" :: "r"(tmp));
  asm volatile("2:");
#else
  /* Large System Extension (LSE) in ARMv8.1 */
  asm volatile("mov %x0, %x1" : "=r"(tmp) : "r"(old));
  asm volatile("cas %x0, %x1, [%2]" : "=r"(tmp), "=r"(new), "=r"(*ptr));
#endif
}


static inline void atomic_inc(uint64_t *val)
{
  compare_and_swap(val, *val + 1, *val);
}

static inline void atomic_dec(uint64_t *val)
{
  compare_and_swap(val, *val - 1, *val);
}


#endif /* !__ASSEMBLY__ */

#endif /* __MCUBE_ARM_ATOMIC_H__ */
