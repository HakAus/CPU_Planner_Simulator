#include <stdio.h>
#include <stdlib.h>

#include <sys/types.h>
#include <sys/socket.h>

#include <netinet/in.h>
#include <unistd.h>
#include <netdb.h>

int main(int argc, char *argv[]){
    if(argc > 2){
        // PASO 1, definir variables
        char *ip;
        int fd, numbytes, puerto;
        char buf[100];
        puerto = atoi(argv[2]);
        ip = argv[1];

        struct hostent *host;
        // Estructura que recibira informacion sobre el nodo remoto
        struct sockaddr_in server;
        // Informacion sobre la direccion del servidor

        if((host = gethostbyname(ip)) == NULL){
            // Llamada al sistema gethostbyname
            printf("Error en la obtencion de gethostbyname.\n");
            exit(-1);
        }

        // PASO 2, definicion del socket
        if((fd = socket(AF_INET, SOCK_STREAM, 0)) == -1){
            // Llamada al sistema socket
            printf("Error en el socket.\n");
            exit(-1);
        }
        // Datos del servidor
        server.sin_family = AF_INET;
        server.sin_port = htons(puerto);
        server.sin_addr = *((struct in_addr *)host->h_addr);
        // host->h_addr pasa la informacion de *host a h_addr
        bzero(&(server.sin_zero), 8); 

        // PASO 3, conexion con el servidor
        if(connect(fd, (struct sockaddr *)&server, sizeof(struct sockaddr)) == -1){
            // Llamada al sistema connect
            printf("Error en la conexion.\n");
            exit(-1);
        }

        if((numbytes = recv(fd, buf, 100, 0)) == -1){
            // Llamada al sistema recv
            printf("Error en la recepcion.\n");
            exit(-1);
        }

        buf[numbytes] = '\0';

        printf("Mensaje: %s\n", buf);
        // Para mensaje de bienvenida o algo asi.

        close(fd);
    }
    else{
        printf("Error en los argumentos. No se ingresó la ip y puerto.\n");
    }

    return 0;
}
