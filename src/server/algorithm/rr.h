#ifndef __RR_H
#define __RR_H

#include "../process.h"
#include "../cpu_scheduler.h"

/* round robin queue is FIFO queue
 */
void * create_rr_queue (int time_quantum);

/* function for cpu scheduling
 */
void rr_scheduling (cpu_scheduler_t * cpu_scheduler);

/* round robin enqueue
 */
void rr_enqueue (void * queue, process_t * process);

/* Print rr queue
*/
void print_rr_queue (cpu_scheduler_t * cpu_scheduler);

#endif
