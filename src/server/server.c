#include "server.h"

#define MAX_CLIENTS 5

 struct server_info * setup_server(job_scheduler_t * job_scheduler, cpu_scheduler_t * cpu_scheduler) {

    // create the server socket
    struct server_info *s_info = malloc(sizeof(struct server_info));

    // create server info object
    s_info->server_socket = socket(AF_INET, SOCK_STREAM, 0);
    s_info->job_scheduler = job_scheduler;
    s_info->cpu_scheduler = cpu_scheduler;

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

    printf("Server is listening ...\n");

    return s_info;

}

void start_simulation(struct server_info * s_info) {
    pthread_t job_scheduler_thread, cpu_scheduler_thread, clock_thread, accept_client_thread;
    int *thread_exit_status;

    printf("Starting simulation ...\n");

    // create threads
    pthread_create(&cpu_scheduler_thread, NULL, cs_thread_function, (void*) s_info);
    s_info->client_count = 0;
    pthread_create(&accept_client_thread, NULL, accept_client_thread_function, (void*) s_info);

    // wait for threads to complete
    pthread_join(cpu_scheduler_thread, (void**)&(thread_exit_status));
    pthread_join(accept_client_thread_function, (void**)&(thread_exit_status));
    for (int i = 0; i < MAX_CLIENTS; i++) {
        pthread_join(s_info->job_scheduler_threads[i], (void**)&(thread_exit_status));
    }

    // check that threads finished correctly
    if (thread_exit_status != PTHREAD_CANCELED) {
        printf("Client halted normally");
    }
}

void stop_simulation(pthread_t js_thread, pthread_t cs_thread) {
    pthread_cancel(js_thread);
    pthread_cancel(cs_thread);
}

void * cs_thread_function(void * args) {
    struct server_info *info = args;
    while (1) {
        info->cpu_scheduler->scheduling(info->cpu_scheduler); // dequeue
        running (info->cpu_scheduler->cpu); // execution
        clocking(info->cpu_scheduler->clk); // update time
    }

    return NULL;
}

void * accept_client_thread_function(void * args) {
    struct server_info *info = args;

    while (info->client_count < MAX_CLIENTS) {
        // accept a client connection
        info->client_sockets[info->client_count] = accept(info->server_socket, NULL, NULL);

        // create a thread for the client
        pthread_create(&info->job_scheduler_threads[info->client_count], NULL, js_thread_function, (void*) info);
        info->client_count++;
    }

    printf("All clients have connected ...\n");

    return NULL;
}

void * js_thread_function(void * args) {
    struct server_info *info = args;

    // socket message buffers
    char from_client[256];
    char server_response[256];

    // Job scheduler main loop
    while (1) {

        // get and serialize process from client
        for (int i = 0; i < info->client_count+1; i++) {

            // receive message from client
            recv(info->client_sockets[i], from_client, sizeof(from_client), 0);

            // deserialize message
            int pid, arrival_time, cpu_burst_time, cpu_remain_time, termination_time, priority; 
            process_t * p = (process_t *) malloc (sizeof (process_t));
            sscanf(from_client, "%d,%d,%d,%d,%d,%d",
                &pid, &arrival_time, &cpu_burst_time, 
                &cpu_remain_time, &termination_time, &priority);
            p->pid = info->pid_consecutive++;
            p->arrival_time = 0;
            p->cpu_burst_time = cpu_burst_time;
            p->cpu_remain_time = cpu_remain_time;
            p->termination_time = termination_time;
            p->priority = priority;

            // send process to cpu scheduler
            new_process(info->cpu_scheduler, p);

            // send response to client
            sprintf(server_response, "Data received. Created process with ID: %d\n", info->pid_consecutive);
            send(info->client_sockets[i], server_response, sizeof(server_response), 0);
        }
        
    }
    return NULL;
}