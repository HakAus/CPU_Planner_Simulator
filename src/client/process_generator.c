#include "process_generator.h"
#include "client.h"
#include "process.h"
#include "util.h"

pthread_t thread_list[MAX_NUMBER_OF_THREADS];

void * generate_process(void * info) {
    struct generator_info* gi = info;

    process_t * process = create_automatic_process(gi->min_burst, gi->max_burst, 
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