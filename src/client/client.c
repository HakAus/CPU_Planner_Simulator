#include <stdio.h>
#include <stdlib.h>
#include "client.h"

int guard(int r, char * err) {
    if (r == -1) { 
        perror(err);
        exit(1); 
    } 
    return r; 
}

int start_connection()
{
     // create a socket
    int socket_fd = guard(socket(AF_INET, SOCK_STREAM, 0), "Could not create TCP listening socket");

    // specify an address for the socket
    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(9002);
    server_address.sin_addr.s_addr = INADDR_ANY;

    int connection_status = guard(connect(socket_fd, (struct sockaddr*) &server_address, sizeof(server_address)),
                                  "Could not connect to server");

    // check for error with the connection
    if (connection_status == -1) {
        printf("There was an error making the connection to the remote socket \n\n");
    }

    return socket_fd;
}

void send_message(int socket_fd, process_t * process) {
    char message[256];
    const int len = sprintf(message, "%d,%d,%d,%d,%d,%d", 
                            process->pid, process->arrival_time,
                            process->cpu_burst_time, process->cpu_remain_time,
                            process->termination_time, process->priority);
    int toServer = guard(send(socket_fd, message, sizeof(message), 0), "Error sending message to server\n");
    guard(recv(socket_fd, server_response, sizeof(server_response), 0), "Error receiving message from the server");
    printf("Server response: %s\n", server_response);
}