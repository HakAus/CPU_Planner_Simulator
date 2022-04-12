#ifndef __SERVER_H
#define __SERVER_H

#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>

#include "job_scheduler.h"
#include "cpu_scheduler.h"
#include "process.h"
#include "clock.h"

struct server_info {
    int server_socket;
    int client_sockets[5];
    job_scheduler_t * job_scheduler;
    cpu_scheduler_t * cpu_scheduler;
    pthread_t job_scheduler_threads [5];
    pthread_t cpu_scheduler_thread, accept_client_thread, input_thread;
    int client_count, pid_consecutive;
};

struct server_info * setup_server(job_scheduler_t * job_scheduler, cpu_scheduler_t * cpu_scheduler);
void * js_thread_function(void * args);
void * cs_thread_function(void * args);
void * accept_client_thread_function(void * args);
void * read_user_input(void * args);

#endif