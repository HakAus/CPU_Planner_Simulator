#include <stdio.h>
#include <stdlib.h>

#include "client.h"


int start_connection()
{
     // create a socket
    int socket_fd = guard(socket(AF_INET, SOCK_STREAM, 0), "Could not create TCP listening socket");
   
    // int network_socket;
    // network_socket = socket(AF_INET, SOCK_STREAM, 0);

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

    // send(listen_fd, )

    // receive data from the server
    // recv(socket_fd, &server_response, sizeof(server_response), 0);

    // print out the server's response
    // printf("The server sent the data %s\n", server_response);

    // and then close the socket
    // close(listen_fd);
}