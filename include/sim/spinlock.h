/**
 * @file include/sim/spinlock.h
 *
 * @author Hiroyuki Chishiro
 */
#ifndef __MCUBE_SIM_SPINLOCK_H__
#define __MCUBE_SIM_SPINLOCK_H__

#ifndef __ASSEMBLY__


static inline void spin_lock(volatile spinlock *lock)
{
}

static inline void spin_unlock(volatile spinlock *lock)
{
}

static inline int spin_trylock(volatile spinlock *lock)
{
	return 0;
}

static inline void lock_scheduler(void)
{
}

static inline void unlock_scheduler(void)
{
}

#endif /* !__ASSEMBLY__ */

#endif /* __MCUBE_SIM_SPINLOCK_H__ */
