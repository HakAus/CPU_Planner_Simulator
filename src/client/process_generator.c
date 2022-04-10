#include "process_generator.h"
#include "client.h"
#include "process.h"
#include "util.h"

// void * generate_processes(void * info) {
//     struct generator_info* gi = info;
//     while (gi->generating) {
//         process_t * process = create_process(gi->process_id_consecutive, gi->min_burst, 
//                                            gi->max_burst, gi->min_creation, gi->max_creation);
//         gi->process_id_consecutive++;

//         printf("Sending process to server ...\n");
//         send_message(gi->socket_fd, process);
//         int sleep_time = get_random_in_range(gi->min_creation, gi->max_creation);
//         printf("Sleeping for %d seconds ...\n", sleep_time);
//         sleep(sleep_time);
//     }

//     return NULL;
// }

pthread_t thread_list[MAX_NUMBER_OF_THREADS];

void * generate_process(void * info) {
    struct generator_info* gi = info;

    process_t * process = create_process(0, gi->min_burst, gi->max_burst, 
                                         gi->min_creation, gi->max_creation);
    printf("Sending process to server ...\n");
    sleep(2); // wait 2 seconds before sending
    send_message(gi->socket_fd, process);

    pthread_exit(NULL);

    return NULL;
}

void init_process_generator(int burstMin, int burstMax, int creationMin, int creationMax) {

    int client_socket = start_connection();

    pthread_t generator_thread;
    int *thread_exit_status;
    
    struct generator_info* info = malloc(sizeof(struct generator_info));
    info->generating = ACTIVE;
    info->min_burst = burstMin;
    info->max_burst = burstMax;
    info->min_creation = creationMin;
    info->max_creation = creationMax;
    info->socket_fd = client_socket;

    int threads_created = 0;
    while (info->generating) {
        if (threads_created < MAX_NUMBER_OF_THREADS) {
            pthread_create(&generator_thread, NULL, generate_process, (void *) info);
            thread_list[threads_created] = generator_thread;
            threads_created++;
            int creation_time = get_random_in_range(info->min_creation, info->max_creation);
            printf("Creation time: %d seconds ...\n", creation_time);
            sleep(creation_time);
        } else {
            info->generating = 0;
            printf("Thread creation limit reached.\n");
        }
    }

    for (int i = 0;  i < threads_created; i++) {
        pthread_join(thread_list[i], (void**)&(thread_exit_status));

        if (thread_exit_status == PTHREAD_CANCELED) {
            perror("Thread join failed.");
        }
    }

}