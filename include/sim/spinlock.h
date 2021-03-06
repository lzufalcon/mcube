/**
 * @file include/sim/spinlock.h
 *
 * @author Hiroyuki Chishiro
 */
#ifndef __MCUBE_SIM_SPINLOCK_H__
#define __MCUBE_SIM_SPINLOCK_H__

#ifndef __ASSEMBLY__


static inline void spin_lock(__unused spinlock_t *lock)
{
}


static inline bool spin_trylock(__unused spinlock_t *lock)
{
  return true;
}


static inline void spin_unlock(__unused spinlock_t *lock)
{
}


#endif /* !__ASSEMBLY__ */

#endif /* __MCUBE_SIM_SPINLOCK_H__ */
