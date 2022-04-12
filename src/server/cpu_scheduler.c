#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

#include "cpu_scheduler.h"

#include "algorithm/fifo.h"
#include "algorithm/np_sjf.h"
#include "algorithm/hpf.h"
#include "algorithm/rr.h"


cpu_scheduler_t * create_cpu_scheduler (char * algo, clk_t * clock, ...) {
    cpu_scheduler_t * cs = (cpu_scheduler_t *) malloc (sizeof (cpu_scheduler_t));

    cs->algo = (char *) malloc (sizeof (algo));
    memcpy (cs->algo, algo, sizeof(cs->algo));
    cs->clk = clock;

    if (strcmp ("fifo", algo) == 0) {
        cs->queue = create_fifo_queue ();
        cs->enqueue = fifo_enqueue;
        cs->scheduling = fifo_scheduling;
        cs->print_ready_queue = print_fifo_queue;
    } else if (strcmp ("sjf", algo) == 0) {
        printf("0");
        cs->queue = create_sjf_queue ();
        printf("1");
        cs->enqueue = sjf_enqueue;
        printf("2");
        cs->scheduling = sjf_scheduling;    
        printf("3");
    } else if (strcmp ("hpf", algo) == 0) {
        cs->queue = create_priority_queue ();
        cs->enqueue = priority_enqueue;
        cs->scheduling = hpf_scheduling;
    } else if (strcmp ("rr", algo) == 0) {
        va_list vl;
        va_start (vl, 1);
        cs->queue = create_rr_queue (va_arg (vl, int));
        va_end (vl);
        cs->enqueue = rr_enqueue;
        cs->scheduling = rr_scheduling;
    } else {
        free (cs);
        return NULL;
    }

    return cs;
}

void delete_cpu_scheduler (cpu_scheduler_t * this) {
    free (this->queue);
    free (this);
}

void register_cpu (cpu_scheduler_t * this, cpu_t * cpu) {
    this->cpu = cpu;
}

void new_process (cpu_scheduler_t * this, process_t * proc) {
    this->enqueue (this->queue, proc);
}

void print_ready_queue(cpu_scheduler_t * this) {
    this->print_ready_queue(this);
}