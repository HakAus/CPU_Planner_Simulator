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

int run (process_t * this) {
    this->cpu_remain_time = this->cpu_remain_time - 1;
    return this->cpu_remain_time == 0;
}

void delete_process (process_t * this) {
    free (this);
}