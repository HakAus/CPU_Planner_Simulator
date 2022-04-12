#ifndef __FIFO_H
#define __FIFO_H

#include "../process.h"
#include "../cpu_scheduler.h"

/* FIFO queue 
 */
void * create_fifo_queue ();

/* function for cpu scheduling
 */
void fifo_scheduling (cpu_scheduler_t * cpu_scheduler);

/* FIFO enqueue
 */
void fifo_enqueue (void * queue, process_t * process);

/* Print fifo queue
*/
void print_fifo_queue (cpu_scheduler_t * cpu_scheduler);

#endif
