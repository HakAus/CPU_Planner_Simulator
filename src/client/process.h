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

/* create new process with pid = pid
 * pid can have value from 1 (0 means idle)
 * you SHOULD call srand before call create_process
 */
process_t * create_process (int pid, int min_burst, int max_burst,
                            int min_creation, int max_creation);

/* decrease cpu remain time by 1
 * return TRUE when cpu remain time becomes 0
 */
int run (process_t * process);

/* delete process
 */
void delete_process (process_t * process);

#endif
