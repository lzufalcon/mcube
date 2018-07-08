/**
 * @file kernel/sched.c
 *
 * @author Hiroyuki Chishiro
 */
#include <mcube/mcube.h>

struct thread_struct *current_th[NR_INTRA_KERNEL_CPUS];
struct thread_struct *prev_th[NR_INTRA_KERNEL_CPUS];

volatile spinlock sched_lock = INIT_SPINLOCK;

struct thread_struct idle_th[NR_INTRA_KERNEL_CPUS];


unsigned long sys_jiffies = 0;

#if CONFIG_ARCH_SIM
unsigned long exec_jiffies = 0;
#endif /* CONFIG_ARCH_SIM */

unsigned long nr_tasks = 0;

int bindex[NR_INTRA_KERNEL_CPUS];
int bidleindex;

unsigned long sched_time;
volatile uint32_t sched_end = FALSE;

#if SCHED_FP
void set_priority(struct thread_struct *th)
{
  /* the priority of idle thread is ULONG_MAX */
  /* smaller value, higher priority */
  /* priority 0 is the highest priority for US or ZL. */
  th->priority = th->id;
  /* NOTE: assume that period is an integer multiple of 100. */
  /* period range should be within [100,3200] */
  //              th->priority = th->sched.period / 100;
  //              th->priority = th->sched.period / 100 - 1;
}

#elif SCHED_DP

void set_priority(struct thread_struct *th)
{
  th->priority = th->sched.deadline;
}
#else
#error "Error: unknown priority"
#endif

void do_sync(void)
{
#if CONFIG_SYNC_PCP || CONFIG_SYNC_SRP
	int i;
	int cpu = get_cpu_id();
	for (i = 0; i < nr_resources; i++) {
		printk("current_th: remaining = %llu wcmt[0] = %llu enter_sem = %llu sem = %u\n",
					 current_th[cpu]->sched.remaining, current_th[cpu]->sched.wcmt[0], current_th[cpu]->sched.enter_sem[i], current_th[cpu]->sched.sem[i]);
		/* check if current_th enters critical section of sem[j] */
		if (current_th[cpu]->sched.sem[i] > 0) {
			if (current_th[cpu]->sched.remaining == current_th[cpu]->sched.enter_sem[i]) {
				/* Now enter critical section of sem[i] */
				printk("th->id = %llu enter critical section %d\n", current_th[cpu]->id, i);
				sync_sem_down(&sync_sem[i]);
			}
			if (current_th[cpu]->sched.remaining == current_th[cpu]->sched.enter_sem[i] + current_th[cpu]->sched.sem[i]) {
				/* Now exit critical section of sem[j] */
				printk("th->id = %llu exit critical section %d\n", current_th[cpu]->id, i);
				sync_sem_up(&sync_sem[i]);
			}
		}
	}
#endif
}


void do_release(void)
{
  //	unsigned long release_latency = current_jiffies_time();
	struct thread_struct *th;
  unsigned long cpu = get_cpu_id();
  pdebug_array(run_tq[cpu].array);
#if 0
	PDEBUG("run_tq: bheap\n");
  pdebug_bheap(&run_tq, run_tq[cpu].head);

	PDEBUG("cpu_run_tq: bheap\n");
	pdebug_bheap(&cpu_run_tq.rq, cpu_run_tq.rq.head);
#endif

	//pdebug_jiffies();
	//	pdebug_thread(current_th);


	//	printk("sleep_tq[cpu]->sched.release = %d\n", sleep_tq[cpu]->sched.release);

#if 0
	pdebug_bitmap(run_tq[cpu].bitmap);
#endif
	//	pdebug_bheap(&run_tq, run_tq[cpu].head);
  pdebug_sleep_tq();

	while (sleep_tq[cpu]->sched.release <= get_current_jiffies()) {
		th = sleep_tq[cpu];
    th->job_id++;
		sleep_tq[cpu] = dequeue_thread(sleep_tq[cpu], th);
		enqueue_rq(&run_tq[cpu], th);

    th->sched.remaining = th->sched.wcet;
		//		pdebug_jiffies();
	}
  pdebug_array(run_tq[cpu].array);
}

#if 1
void switch_to(struct thread_struct *next_task)
{
  unsigned long cpu = get_cpu_id();
  printk("switch_to()\n");
  if (current_th[cpu] == prev_th[cpu]) {
    return;
  }
  printk("call arch_switch_to()\n");
  arch_switch_to(prev_th[cpu], current_th[cpu]);
  printk("call arch_switch_to()2\n");
}

#else
void switch_to(struct task_struct *next_task)
{
  printk("switch_to()\n");
  if (current_task == next_task) {
    return;
  }
  struct task_struct *prev_task = current_task;
  current_task = next_task;
  arch_switch_to(prev_task, next_task);
}
#endif


#if 0

void __do_sched(void)
{
	int next, c;
  int i;
	struct task_struct *p;
	preempt_disable();
	while (1) {
		c = -1;
		next = 0;
		for (i = 0; i < NR_TASKS; i++) {
			p = tasks[i];
			if (p && p->state == RUNNING && p->counter > c) {
				c = p->counter;
				next = i;
			}
		}
		if (c) {
			break;
		}
		for (i = 0; i < NR_TASKS; i++) {
			p = tasks[i];
			if (p) {
				p->counter = (p->counter >> 1) + p->priority;
			}
		}
	}
	switch_to(tasks[next]);
	preempt_enable();
}


#else
void __do_sched(void)
{
  unsigned long cpu = get_cpu_id();
  PDEBUG("do_sched()\n");
	struct thread_struct *th;
  pdebug_deadline_tq();


	/* jump to algorithm-specific function */
  //	do_sched_algo();

	/* assign the highest priority task to cpu */
	th = pick_next_task();
	if (th) {
		current_th[cpu] = th;
	} else {
		current_th[cpu] = &idle_th[cpu];
	}

	if (prev_th[cpu] != &idle_th[cpu] && is_preempted(prev_th[cpu])) {
		/* preemption occurs */
		prev_th[cpu]->state = READY;
	}

  //	switch_to(tasks[next]);
	current_th[cpu]->state = RUNNING;
  //  switch_to(current_th[cpu]);

	//	pdebug_jiffies();
	PDEBUG("do_sched(): end\n");
}
#endif


void do_sched(void)
{
  unsigned long cpu = get_cpu_id();
  printk("do_sched()\n");
	struct thread_struct *th;
  pdebug_deadline_tq();


	/* jump to algorithm-specific function */
  //  do_sched_algo();

	/* assign the highest priority task to cpu */
	th = pick_next_task();
	if (th) {
		current_th[cpu] = th;
	} else {
		current_th[cpu] = &idle_th[cpu];
	}
  printk("current_th[%lu]->id = %lu\n", cpu, current_th[cpu]->id);

	if (prev_th[cpu] != &idle_th[cpu] && is_preempted(prev_th[cpu])) {
		/* preemption occurs */
		prev_th[cpu]->state = READY;
	}

  //	switch_to(tasks[next]);
	current_th[cpu]->state = RUNNING;
  //  switch_to(current_th[cpu]);

	//	pdebug_jiffies();
	PDEBUG("do_sched(): end\n");
}


int check_deadline_miss(void)
{
  unsigned long cpu = get_cpu_id();
	if (deadline_tq[cpu]->sched.deadline <= get_current_jiffies()) {
		PDEBUG("cpu %lu get_current_jiffies() %lu\n", cpu, get_current_jiffies());
		PDEBUG("task %lu missed deadline\n", deadline_tq[cpu]->id);
		PDEBUG("if the following inequality holds,\n");
		PDEBUG("then you must adjust parameters:\n");
		PDEBUG("current_th->sched.deadline = %lu\n", deadline_tq[cpu]->sched.deadline);
		return FALSE;
	}
	return TRUE;
}

void do_timer_tick(void)
{
  --current_task->counter;
  if (current_task->counter > 0 || current_task->preempt_count > 0) {
    return;
  }
  current_task->counter = 0;
  enable_interrupt();
  __do_sched();
  disable_interrupt();
}


int run(unsigned long nr_threads)
{
	int i;
	int ret;
  printk("run()\n");
  //  asm volatile("move %0, $fp" : "=r"(current_fp));
  //  printk("current_fp = 0x%x\n", current_fp);
  
  //  pdebug_array(run_tq[cpu].array);
#if 1
	// NOTE: not work if comment the following printk function
  for (i = 0; i < nr_threads; i++) {
		//		current_cpu = i;
    /* check feasibility and activate */
    if ((ret = do_activate(&ths[i])) != 0) {
			printk("Error: do_activate(): %d\n", ret);
      return 1;
    }
		//		do_sched_trace_thread_name(&ths[i]);
  }
#endif

	sys_jiffies = 0;
	sched_end = FALSE;

  printk("run()2\n");
  for (i = 0; i < NR_INTRA_KERNEL_CPUS; i++) {
    current_th[i] = prev_th[i] = &idle_th[i];
    current_th[i]->id = 0;
    current_th[i]->stack_top = THREAD_STACK_ADDR(i, 0);
    printk("current_th[%d]->stack.top = 0x%lx\n", i, current_th[i]->stack_top);
  }
  //		printk("current_th[%d] = %x\n", i, current_th[i]);

	//	inf_loop();
	//syscall0(SYS_sched);

  do_release();
  start_timer(0);

  
  //  generate_software_interrupt(0);
  
	/* idle thread start */
	while (sched_end == FALSE) {
		// printk("");
    //    printk("get_timer_count() = %lu\n", get_timer_count()); 
    printk("0");
    //    printk("sched_end = %d\n", sched_end);
		//		printk("idle!");
    //    asm volatile("move %0, $sp" : "=r"(current_fp));
    //    printk("current_fp = 0x%x\n", current_fp);
    //    nop();
    //    wait_until_next_interrupt();
	}
	stop_timer(0);

  //  printk("run() end\n");
  //  asm volatile("move %0, $fp" : "=r"(current_fp));
  //  printk("current_fp = 0x%x\n", current_fp);
  //  asm volatile("move %0, $sp" : "=r"(current_sp));
  //  printk("current_sp = 0x%x\n", current_sp);
  
	return 0;
}

void schedule_tail(void)
{
  preempt_enable();
}



void init_sched(void)
{
  unsigned long cpu = get_cpu_id();
  size_t i, j;
  sys_jiffies = 0;

  for (i = 0; i < NR_INTRA_KERNEL_CPUS; i++) {
    idle_th[i] = INIT_IDLE_THREAD(cpu);
    idle_th[i].thflags = THFLAGS_START_TH;
    run_tq[i].util = 0;
    run_tq[i].nr_threads = 0;
    for (j = 0; j < NR_PRIORITY_BITMAPS; j++) {
      run_tq[i].bitmap[j] = 0;
    }
  }
  current_th[cpu] = prev_th[cpu] = &idle_th[cpu];
  deadline_tq[cpu] = &idle_th[cpu];
  sleep_tq[cpu] = &idle_th[cpu];

}
