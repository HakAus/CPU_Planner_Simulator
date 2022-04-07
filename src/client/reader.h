
#ifndef __READER_H
#define __READER_H

#include <time.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>

struct reader_args {
    char* filename;
};

void init_reader(void *arg);
void * read_processes(void *file_name);
void * connection_handler(void *message);

#endif