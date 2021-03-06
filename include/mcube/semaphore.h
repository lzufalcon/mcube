/**
 * @file include/mcube/semaphore.h
 *
 * @author Hiroyuki Chishiro
 */
#ifndef __MCUBE_MCUBE_SEMAPHORE_H__
#define __MCUBE_MCUBE_SEMAPHORE_H__

#ifndef __ASSEMBLY__


/**
 * @struct sem_struct
 * @brief Semaphore
 */
struct sem_struct {
  /** Semaphore counter. */
  volatile short counter;
  /** Ceiling for Priority Ceiling Protocol. */
  unsigned int ceil;
  /** Wait queue for semaphore. */
  struct thread_struct *ewq;
  /** Owner of semaphore. */
  struct thread_struct *owner;
  /** Original priority. */
  uint64_t org_prio;
};

typedef struct sem_struct sem_struct;

#define  INIT_COUNT_SEM(nres, cpu) {            \
    .counter  = nres,                           \
      .ceil  = 0,                               \
      .ewq    = &kernel_th[cpu],                \
      .owner    = NULL,                         \
      .org_prio  = 0,                           \
      }

#define  INIT_SEM_MUTEX  INIT_COUNT_SEM(1)

/* true: if down, false: if still up */
/* reading the counter directly in user land will fail due to the data cache */
static inline int sem_is_down(struct sem_struct *sem)
{
  return (sem->counter <= 0);
}

extern unsigned int nr_resources;

void __sem_down(struct sem_struct *);
void __sem_up(struct sem_struct *);

void init_sem(struct sem_struct *, unsigned int, unsigned int);
void sem_down(struct sem_struct *);
void sem_up(struct sem_struct *);

#endif /* !__ASSEMBLY__ */

#endif /* __MCUBE_MCUBE_SEMAPHORE_H__ */
