/**
 * @file include/debug/jiffies_debug.h
 *
 * @author Hiroyuki Chishiro
 */
#ifndef __MCUBE_JIFFIES_DEBUG_H__
#define __MCUBE_JIFFIES_DEBUG_H__

/* Never include this file directly. Include <debug/debug.h> instead. */
#ifndef __ASSEMBLY__

#if CONFIG_DEBUG

static inline void print_jiffies(void)
{
  unsigned long cpu = get_cpu_id();
  PDEBUG("cpu = %lu sys_jiffies = %lu\n",
         cpu, sys_jiffies);
}


#define pdebug_jiffies() do {                                           \
    PDEBUG_WHERE();                                                     \
    print_jiffies();                                                    \
  } while (0)

#else
#define pdebug_jiffies()
#endif /* CONFIG_DEBUG */

#endif /* !__ASSEMBLY__ */

#endif /* __MCUBE_JIFFIES_DEBUG_H__ */
