#include "server.h"

#define ACTIVE 1
#define INACTIVE 0

int running = INACTIVE;
int stop = INACTIVE;

void setup_server() {

    int *thread_exit_status;

    // create the server socket
    struct server_info *s_info = malloc(sizeof(struct server_info));
    s_info->server_socket = socket(AF_INET, SOCK_STREAM, 0);

    // define the server address
    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(9002);
    server_address.sin_addr.s_addr = INADDR_ANY; // resolves for any ip address in th local machine.

    // bind the socket to our specified IP and port
    bind(s_info->server_socket, (struct sockaddr*) &server_address, sizeof(server_address));

    // the 2nd argument is a backlog of how many connections can be 
    // waiting for this socket at a certain point in time. 
    listen(s_info->server_socket, 5); 

    running = ACTIVE;

    pthread_t server_thread;
    printf("About to run server thread ...\n");
    pthread_create(&server_thread, NULL, run_server, (void*) s_info);

    pthread_join(server_thread, (void**)&(thread_exit_status));

    if (thread_exit_status != PTHREAD_CANCELED) {
        printf("Client halted normally");
    }
}

void * run_server(void * args) {
    struct server_info *info = args;
    char from_client[256];
    char server_response[256] = "Hello back!";
    // listen for connections
    int client_socket;
    client_socket = accept(info->server_socket, NULL, NULL);
    while (running) {
        recv(client_socket, from_client, sizeof(from_client), 0);
        printf("Mensaje del cliente: %s", from_client);
        send(client_socket, server_response, sizeof(server_response), 0);
        // send the message to the client
    }
    return NULL;
}