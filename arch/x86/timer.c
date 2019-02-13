/**
 * @file arch/x86/timer.c
 *
 * @author Hiroyuki Chishiro
 */
#include <mcube/mcube.h>


void init_timer(unsigned long tick_us)
{
#if 0
#if LAPIC_TIMER
  init_lapic_timer(tick_us);
#elif HPET_TIMER
  init_hpet_timer(tick_us);
#elif PIT_TIMER
  init_pit_timer(tick_us);
#endif /* LAPIC_TIMER */
#endif
}

void start_timer(unsigned int ch)
{
#if 0
#if LAPIC_TIMER
  start_lapic_timer(ch);
#elif HPET_TIMER
  start_hpet_timer(ch);
#elif PIT_TIMER
  start_pit_timer(ch);
#endif /* LAPIC_TIMER */
#endif
}

void stop_timer(unsigned int ch)
{
#if 0
#if LAPIC_TIMER
  stop_lapic_timer(ch);
#elif HPET_TIMER
  stop_hpet_timer(ch);
#elif PIT_TIMER
  stop_pit_timer(ch);
#endif /* LAPIC_TIMER */
#endif
}

