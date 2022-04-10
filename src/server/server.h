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
    job_scheduler_t * job_scheduler;
    cpu_scheduler_t * cpu_scheduler;
    int pid_consecutive;
    clk_t * clock;
};

void setup_server(job_scheduler_t * job_scheduler, cpu_scheduler_t * cpu_scheduler);
void * schedule_jobs(void * args);

#endif