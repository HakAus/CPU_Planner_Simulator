#ifndef __NP_PRIORITY_H
#define __NP_PRIORITY_H

#include "../cpu_scheduler.h"
#include "../process.h"

/* non-preemptive hpf queue is hpf queue
 * smaller hpf value, higher hpf
 */
void * create_np_hpf_queue ();

/* function for cpu scheduling
 */
void np_hpf_scheduling (cpu_scheduler_t * cpu_scheduler);

/* np-hpf enqueue
 */
void np_hpf_enqueue (void * queue, process_t * process);

#endif
