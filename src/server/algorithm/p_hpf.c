#include "../cpu.h"
#include "hpf.h"
#include "p_hpf.h"

#define QUEUE struct __priority_queue

#define NULL 0

void * create_p_hpf_queue () {
    return (void *) create_hpf_queue ();
}

void p_hpf_scheduling (cpu_scheduler_t * this) {
    if (hpf_is_empty ((QUEUE *) this->queue)) {
        return;
    }
    if (is_running (this->cpu) && this->cpu->process->priority <= ((QUEUE *) this->queue)->head->p->priority) {
        // preemtion condition check
        return;
    }
    process_t * orig;
    execute (this->cpu, hpf_dequeue ((QUEUE *) this->queue), &orig);
    if (orig != NULL) { // if preemted
        p_hpf_enqueue (this->queue, orig);
    }
}

void p_hpf_enqueue (void * queue, process_t * process) {
    hpf_enqueue ((QUEUE *) queue, process);
}