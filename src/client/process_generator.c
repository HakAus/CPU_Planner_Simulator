#include "process_generator.h"
#include "process.h"

void * generate_processes(void * info) {
    struct generator_info* gi = info;
    while (gi->generating) {
        printf("generating ...\n");
        process_t * process = create_process(gi->process_id_consecutive, gi->min_burst, 
                                           gi->max_burst, gi->min_creation, gi->max_creation);
        gi->process_id_consecutive++;
        printf("PID: %d\n", process->pid);
        printf("Arrival time: %d\n", process->arrival_time);
        printf("CPU burst time: %d\n", process->cpu_burst_time);
        printf("CPU remain time: %d\n", process->cpu_remain_time);
        printf("Priority: %d\n", process->priority);
        printf("Termination time: %d\n", process->termination_time);
        sleep(1);
    }

    return NULL;
}

void init_process_generator(int burstMin, int burstMax, int creationMin, int creationMax) {

    pthread_t generator_thread;
    int *thread_exit_status;
    
    struct generator_info* info = malloc(sizeof(struct generator_info));
    info->generating = ACTIVE;
    info->process_id_consecutive = 0;
    info->min_burst = burstMin;
    info->max_burst = burstMax;
    info->min_creation = creationMin;
    info->max_creation = creationMax;
    
    pthread_create(&generator_thread, NULL, generate_processes, (void *) info);

    pthread_join(generator_thread, (void**)&(thread_exit_status));

    if (thread_exit_status != PTHREAD_CANCELED) {
        printf("Client halted normally");
    }
    
}