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

struct server_info {
    int server_socket;
};

void setup_server();
void * run_server(void * args);

#endif