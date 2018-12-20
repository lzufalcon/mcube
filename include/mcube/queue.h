/**
 * @file include/mcube/queue.h
 *
 * @author Hiroyuki Chishiro
 */
#ifndef __MCUBE_MCUBE_SCHED_QUEUE_H__
#define __MCUBE_MCUBE_SCHED_QUEUE_H__

#ifndef __ASSEMBLY__

/**
 * @struct bheap_node
 * @brief Binominal heap node
 */
struct bheap_node {
	/** Node ID. */
  unsigned long node_id;
	/** Pointer to parent node. */
  struct bheap_node *parent;
	/** Pointer to next node. */
  struct bheap_node *next;
	/** Pointer to child node. */
  struct bheap_node *child;

	/** Degree. */
  unsigned long degree;
	/** Value in node. */
  struct thread_struct *value;
  //  struct bheap_node **ref;
};

typedef struct bheap_node bheap_node;

/**
 * @struct runqueue
 * @brief Runqueue information
 */
struct runqueue {
	/** Lock to runqueue. */
  atomic_int lock;
	/** Array to manage threads. */
  struct thread_struct array[NR_PRIORITIES];
	/** Bitmap. */
  uint32_t bitmap[NR_PRIORITY_BITMAPS];
	/** Utilization of runqueue. */
  unsigned long util;
	/** Number of threads in runqueue */
	int nr_threads;
#if CONFIG_TQ_BHEAP
  struct bheap_node *head;
  struct bheap_node *min;
#endif /* CONFIG_TQ_BHEAP */
};

typedef struct runqueue runqueue;

#define NR_CPU_BITMAPS (CEIL(NR_INTRA_KERNEL_CPUS, 32))

extern runqueue run_tq[NR_INTRA_KERNEL_CPUS];

/* partitioned scheduling */
extern unsigned long nr_ptasks[NR_INTRA_KERNEL_CPUS];

void enqueue_rq_head(struct runqueue *rq, struct thread_struct *th);
void enqueue_rq_queue_head(struct runqueue *rq, struct thread_struct *th);
void enqueue_rq(struct runqueue *rq, struct thread_struct *th);
void enqueue_rq_queue(struct runqueue *rq, struct thread_struct *th);


struct thread_struct *compare_thread(struct thread_struct *th,
                                     struct thread_struct *n,
                                     unsigned long offset);
struct thread_struct *enqueue_thread(struct thread_struct *head,
                                     struct thread_struct *th,
                                     unsigned long offset);
struct thread_struct *enqueue_deadline_thread(struct thread_struct *head,
																							struct thread_struct *th,
																							unsigned long offset);
struct thread_struct *dequeue_thread(struct thread_struct *head, struct thread_struct *th);
struct thread_struct *dequeue_deadline_thread(struct thread_struct *head, struct thread_struct *th);
void dequeue_rq(struct runqueue *rq, struct thread_struct *th);
void dequeue_rq_queue(struct runqueue *rq, struct thread_struct *th);


struct thread_struct *pick_next_task(void);
int do_partitioned(struct thread_struct *th, int (*func)(struct thread_struct *, struct thread_struct *, int));
void init_global(void);
void assign_global(void);
int partitioned_test(struct thread_struct *head, struct thread_struct *th, int cpu);

#if CONFIG_TQ_BHEAP
#define NOT_IN_BHEAP ULONG_MAX

typedef int (*thread_prio_t)(struct thread_struct *a, struct thread_struct *b);
extern thread_prio_t thread_prio;

extern struct bheap_node bh_nodes[NR_THREADS];

struct bheap_node *merge_bheap(struct bheap_node *p, struct bheap_node *q);
int empty_bheap(struct runqueue *rq);
void link_bheap(struct bheap_node *root, struct bheap_node *child);
void union_bheap(struct runqueue *rq, struct bheap_node *h2);
void insert_bheap(struct runqueue *rq, struct bheap_node *node);
void min_bheap(struct runqueue *rq, struct bheap_node **prev, struct bheap_node **node);
void min_uncache(struct runqueue *rq);
void union_bheap_uncache(struct runqueue *target, struct runqueue *addition);
struct bheap_node *reverse_bheap(struct bheap_node *h);
struct bheap_node *extract_min_bheap(struct runqueue *rq);
struct bheap_node *take_bheap(struct runqueue *rq);
struct bheap_node *peek_bheap(struct runqueue *rq);
void decrease_bheap(struct runqueue *rq, struct bheap_node *node);
void delete_bheap(struct runqueue *rq, struct bheap_node *node);

void print_bheap(struct runqueue *rq, struct bheap_node *th);

#endif /* CONFIG_TQ_BHEAP */

#endif /* !__ASSEMBLY__ */

#endif /* __MCUBE_MCUBE_SCHED_QUEUE_H__ */
