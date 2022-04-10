#include "../cpu.h"
#include "hpf.h"
#include "np_hpf.h"

#define QUEUE struct __priority_queue

void * create_np_hpf_queue () {
    return (void *) create_priority_queue ();
}

void np_hpf_scheduling (cpu_scheduler_t * this) {
    if (is_running (this->cpu)) {
        return;
    }
    if (priority_is_empty ((QUEUE *) this->queue)) {
        return;
    }
    process_t * orig;
    execute (this->cpu, priority_dequeue ((QUEUE *) this->queue), &orig);
}

void np_hpf_enqueue (void * queue, process_t * process) {
    priority_enqueue ((QUEUE *) queue, process);
}