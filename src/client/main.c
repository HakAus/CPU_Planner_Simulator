#include <stdio.h>
#include "option.h"
#include "reader.h"
#include "process_generator.h"
#include "client.h"

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

    int cont = 0;
    if (opt.mode !=  INVALID_OPTION_MODE) {
        if (opt.mode == AUTO_MODE) {
            init_process_generator(opt.burstMin, opt.burstMax, opt.creationMin, opt.creationMax);
        } else if (opt.mode == MANUAL_MODE) {
            init_reader(opt.file);
        }
    } else {
        printf("Inténtelo de nuevo.");
    }
    
    return 0;
}