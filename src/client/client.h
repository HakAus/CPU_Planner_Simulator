
#ifndef __CLIENT_H
#define __CLIENT_H

#include <sys/types.h>
#include <sys/socket.h>

#include <netinet/in.h>
#include <unistd.h>

char server_response[256];

int start_connection();

void end_connection();

#endif