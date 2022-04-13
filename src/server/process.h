#ifndef __PROCESS_H
#define __PROCESS_H

struct __process {
    unsigned int pid;

    unsigned int arrival_time;
    unsigned int cpu_burst_time;
    unsigned int cpu_remain_time;
    unsigned int termination_time;

    unsigned int priority;
};

typedef struct __process process_t;

/* decrease cpu remain time by 1
 * return TRUE when cpu remain time becomes 0
 */
int run (process_t * process);

/* delete process
 */
void delete_process (process_t * process);

#endif
