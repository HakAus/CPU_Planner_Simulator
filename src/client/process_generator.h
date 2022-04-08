#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#ifndef __PROCESS_GENERATOR_H
#define __PROCESS_GENERATOR_H

#define ACTIVE 1
#define INACTIVE 0

struct generator_info {
    int generating;
    int process_id_consecutive;
    int min_burst;
    int max_burst;
    int min_creation;
    int max_creation;
};

void * generate_processes(void * info);
void init_process_generator(int burstMin, int burstMax, int creationMin, int creationMax);

#endif