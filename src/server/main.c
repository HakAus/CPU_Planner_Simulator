#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/types.h>
#include <sys/socket.h>

#include <netinet/in.h>
#include <unistd.h>

#include "option.h"
#include "server.h"

int main(int argc, char** argv) {

    setup_server();
    

    // if (argc > 1)
    // {
    //     // PASO 1, definir variables
    //     int fd, fd2, longitud_cliente, puerto;
    //     puerto = atoi(argv[1]);

    //     // Se necesitan dos estructuras del tipo sockaddr
    //     // La primera guarda la dirección del servidor
    //     // La segunda guarda la dirección del cliente

    //     struct sockaddr_in server, client;

    //     // Configurar la estructura server
    //     server.sin_family = AF_INET; // Protocolo de internet
    //     server.sin_port = htons(puerto); // Puerto
    //     server.sin_addr.s_addr = INADDR_ANY; // Dirección IP (cualquiera puede conectarse)
    //     bzero(&(server.sin_zero), 8); // Poner a cero el resto de la estructura

    //     // PASO 2, crear el socket
    //     if((fd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    //     {
    //         perror("Error con la aperture del socket. \n");
    //         exit(-1);
    //     }

    //     // PASO 3, enlazar el socket con la estructura server
    //     if(bind(fd, (struct sockaddr *)&server, sizeof(struct sockaddr)) == -1)
    //     {
    //         printf("Error en el enlace.\n");
    //         exit(-1);
    //     }

    //     // PASO 4, modo escucha
    //     if(listen(fd, 5) == -1)
    //     {
    //         printf("Error en el modo escucha.\n");
    //         exit(-1);
    //     }

    //     // PASO 5, aceptar conexiones
    //     int contador = 1;
    //     while(1)
    //     {
    //         longitud_cliente = sizeof(struct sockaddr_in);
    //         // Llamada al sistema accept
    //         if((fd2 = accept(fd, (struct sockaddr *)&client, &longitud_cliente)) == -1)
    //         {
    //             printf("Error en la aceptacion de la conexion.\n");
    //             exit(-1);
    //         }

    //         char message[100]; // = "Hola cliente: ";
    //         sprintf(message, "Hola cliente: %d\n", contador);
    //         // snprintf(message, 12, "Hola cliente %d", contador);
    //         send(fd2, message, 26, 0);

    //         close(fd2); // Cerrar el socket

    //         contador += 1;
    //     }

    //     close(fd); 

    // }else{
    //     printf("No se ingresó el puerto por parámetro.");
    // }
    


    
    // option_t opt;
    // parse_option (argc, argv, &opt);

    // if (opt.help) {
    //     printf ("");
    //     printf ("Options:\n");
    //     printf ("  -h, --help\n");
    //     printf ("  -t, --test ...\n");
    //     return 0;
    // }



    // if (opt.test_fifo) {
    //     printf ("test_fifo\n");
    // }

    // if (opt.test_np_sjf) {
    //     printf ("test_np_sjf\n");
    // }

    // if (opt.test_np_hpf) {
    //     printf ("test_np_hpf\n");
    // }

    // if (opt.test_rr) {
    //     printf ("test_rr\n");
    // }




    return 0;
}