#ifndef __CPU_H
#define __CPU_H

#include "clock.h"
#include "process.h"
#include "record.h"
#include "list.h"

struct __cpu {
    clk_t * clk;
    record_t * record;
    process_t * process;

    // stastics
    List * process_list;
};

typedef struct __cpu cpu_t;

/* create cpu
 */
cpu_t * create_cpu (clk_t * clock, List * process_list);

/* delete cpu
 */
void delete_cpu (cpu_t * cpu);

/* execute cpu for one clock
 */
void running (cpu_t * cpu);

/* return if cpu has a process running
 */
int is_running (cpu_t * cpu);

/* schedule new process to cpu
 * if there is a process already running,
 * orig will store that process
 */
void execute (cpu_t * cpu, process_t * new, process_t ** orig);

#endif
