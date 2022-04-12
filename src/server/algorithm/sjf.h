#ifndef __SJF_H
#define __SJF_H

#include "../cpu_scheduler.h"
#include "../process.h"

struct __sjf_node {
    process_t * p;
    struct __sjf_node * next;
};

struct __sjf_queue {
    struct __sjf_node * head;
};


/* non-preemptive SJF queue is priority queue
 * shorter cpu burst time, higher priority
 */
struct __sjf_queue * create_sjf_queue ();

/* function for cpu scheduling
 */
void sjf_scheduling (cpu_scheduler_t * cpu_scheduler);

/* np-SJF enqueue
 */
void sjf_enqueue (struct __sjf_queue * queue, process_t * process);

/* SJF dequeue
 * return a process which has the shortest cpu burst time
 */
process_t * sjf_dequeue (struct __sjf_queue * queue);

/* return TRUE if queue is empty
 */
int sjf_is_empty (struct __sjf_queue * queue);
#endif
