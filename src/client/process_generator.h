#ifndef __PROCESS_GENERATOR_H
#define __PROCESS_GENERATOR_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>
#include "util.h"

#define ACTIVE 1
#define INACTIVE 0

struct generator_info {
    int generating;
    int process_id_consecutive;
    int min_burst;
    int max_burst;
    int min_creation;
    int max_creation;
    int socket_fd;
};

void * generate_processes(void * info);
void init_process_generator(int burstMin, int burstMax, int creationMin, int creationMax);

#endif