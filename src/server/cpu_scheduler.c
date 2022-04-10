#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

#include "cpu_scheduler.h"

#include "algorithm/fifo.h"
#include "algorithm/np_sjf.h"
#include "algorithm/np_hpf.h"
#include "algorithm/rr.h"


cpu_scheduler_t * create_cpu_scheduler (char * algo, clk_t * clock, ...) {
    cpu_scheduler_t * cs = (cpu_scheduler_t *) malloc (sizeof (cpu_scheduler_t));

    cs->algo = (char *) malloc (sizeof (algo));
    memcpy (cs->algo, algo, sizeof (algo));
    cs->clk = clock;

    if (strcmp ("fifo", algo) == 0) {
        cs->queue = create_fifo_queue ();
        cs->enqueue = fifo_enqueue;
        cs->scheduling = fifo_scheduling;
    } else if (strcmp ("np_sjf", algo) == 0) {
        cs->queue = create_np_sjf_queue ();
        cs->enqueue = np_sjf_enqueue;
        cs->scheduling = np_sjf_scheduling;    
    } else if (strcmp ("np_hpf", algo) == 0) {
        cs->queue = create_np_hpf_queue ();
        cs->enqueue = np_hpf_enqueue;
        cs->scheduling = np_hpf_scheduling;
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


void* startCpuScheduler(void* void_arg){
    char* arg = void_arg;
    if (strcmp(arg, "fifo") == 0)
    {
            printf("fifo inserted\n");
    }
    else if (strcmp(arg, "sjf") == 0)
    {
            printf("sjf inserted\n");
    }
    else if (strcmp(arg, "hpf") == 0)
    {
            printf("hpf inserted\n");
    }
    else if (strcmp(arg, "roundrobin") == 0)
    {
            printf("round robin inserted\n");
    }
    else
    {
        printf("invalid expression inserted\n");
    }
    return NULL;
}

int main(int argc, char** argv)
{
    pthread_t tid0;
    const char* arg1 = argv[1];

    // Create the thread for the CPU Scheduler.
    pthread_create(&tid0, NULL, startCpuScheduler, (void *) arg1);

    pthread_exit(NULL);
    return 0;
}