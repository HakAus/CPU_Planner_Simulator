
#ifndef __READER_H
#define __READER_H

#include <time.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>
#include "util.h"

struct reader_args {
    char* filename;
    int client_socket;
};

struct connection_args {
    int client_socket;
    int burst;
    int priority;
};

void init_reader(void *arg);
void * read_processes(void *file_name);
void * connection_handler(void *message);

#endif