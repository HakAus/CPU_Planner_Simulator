#include <stdlib.h>

#include "cpu.h"

cpu_t * create_cpu (clk_t * clk, List * process_list) {
    cpu_t * cpu = (cpu_t *) malloc (sizeof (cpu_t));
    cpu->clk = clk;
    cpu->process_list = process_list;
    
    return cpu;
}

void delete_cpu (cpu_t * this) {
    free (this);
}

void running (cpu_t * this) {
    if (this->process == NULL) {
        return;
    }
    if (run (this->process)) {
        this->process->termination_time = get_time (this->clk);
        insert(this->process_list, this->process);
        printf("Process: %d finished execution. \n", this->process->pid);
        this->process = NULL;
        
        return;
    }
}

int is_running (cpu_t * this) {
    return this->process != NULL;
}

void execute (cpu_t * this, process_t * new, process_t ** orig) {
    *orig = this->process;
    this->process = new;
    char process_state_message[100];
    sprintf(process_state_message, "Process with ID: %d with %d secs burst and priority %d is running ...\n", new->pid, new->cpu_burst_time, new->priority);
    printf(process_state_message);
}