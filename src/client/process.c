#include <stdlib.h>
#include "process.h"

/* arrival time can have value
 * from 0
 * to MAX_ARRIVAL_TIME - 1
 */
#define MAX_ARRIVAL_TIME 10

/* priority can have value
 * from 0
 * to MAX_PRIORITY - 1
 */
#define MAX_PRIORITY 5

process_t * create_process (int pid, int min_burst, int max_burst,
                            int min_creation, int max_creation) {
    // if (pid == 0) {
    //     return NULL;
    // }
    process_t * p = (process_t *) malloc (sizeof (process_t));

    p->pid = pid;

    p->arrival_time = rand() % MAX_ARRIVAL_TIME;
    p->cpu_burst_time = rand() % (max_burst - min_burst) + min_burst;
    p->cpu_remain_time = p->cpu_burst_time;
    p->termination_time = 0;

    p->priority = rand() % (MAX_PRIORITY);

    return p;
}

int run (process_t * this) {
    this->cpu_remain_time = this->cpu_remain_time - 1;
    return this->cpu_remain_time == 0;
}

void delete_process (process_t * this) {
    free (this);
}