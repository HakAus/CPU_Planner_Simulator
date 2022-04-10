
#ifndef __CLIENT_H
#define __CLIENT_H

#include <sys/types.h>
#include <sys/socket.h>

#include <netinet/in.h>
#include <unistd.h>
#include "process.h"

char server_response[256];

int start_connection();
void send_message(int socket_fd, process_t * message);
void end_connection();

#endif