#include <stdio.h>
#include "option.h"
#include "reader.h"

// int guard(int r, char * err) {
//     if (r == -1) { 
//         perror(err);
//         exit(1); 
//     } 
//     return r; 
// }

// void * thread_func(void * arg) {
//   intptr_t conn_fd = (int) arg;
//   printf("thread: serving fd %ld\n", conn_fd);
//   char buf[1024];
//   for (;;) {
//     int bytes_received = guard(recv(conn_fd, buf, sizeof(buf), 0), "Could not recv");
//     if (bytes_received == 0) { goto stop_serving; }
//     int bytes_sent = 0;
//     while (bytes_sent < bytes_received) {
//       ssize_t bytes_sent_this_call = send(conn_fd, buf+bytes_sent, bytes_received-bytes_sent, 0);
//       if (bytes_sent_this_call == -1) { goto stop_serving; }
//       bytes_sent += bytes_sent_this_call;
//     }
//   }
//   stop_serving:
//   guard(close(conn_fd), "Could not close socket");
//   printf("thread: finished serving %ld\n", conn_fd);
//   return NULL;
// }

int main(int argc, char** argv) {

    option_t opt;
    parse_option (argc, argv, &opt);

    if (opt.mode !=  INVALID_OPTION_MODE) {
        if (opt.mode == AUTO_MODE) {
            printf("Se escogio el modo automatico");
        } else if (opt.mode == MANUAL_MODE) {
            printf("Se escogio el modo manual\n");
            init_reader(opt.file);
        }
    } else {
        printf("Inténtelo de nuevo.");
    }
    
    
    return 0;
}

// void * hello(void *input) {
    
//     printf("%s\n", (char *)input);
//     pthread_exit(NULL);
// }

// int main(void) {
//     pthread_t tid;
//     char * name = "austin";
//     pthread_create(&tid, NULL, hello, &name);
//     pthread_join(tid, NULL);
//     return 0;
// }