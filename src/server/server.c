#include "server.h"

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
    pthread_t job_scheduler_thread, cpu_scheduler_thread, clock_thread;
    int *thread_exit_status;

    printf("Starting simulation ...\n");

    // create threads
    pthread_create(&job_scheduler_thread, NULL, js_thread_function, (void*) s_info);
    pthread_create(&cpu_scheduler_thread, NULL, cs_thread_function, (void*) s_info);

    // wait for threads to complete
    pthread_join(cpu_scheduler_thread, (void**)&(thread_exit_status));
    pthread_join(job_scheduler_thread, (void**)&(thread_exit_status));

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
        printf("cpu working ...\n");
        info->cpu_scheduler->scheduling(info->cpu_scheduler); // dequeue
        running (info->cpu_scheduler->cpu); // execution
        clocking(info->cpu_scheduler->clk);
        printf("%d seconds have passed ...", get_time(info->cpu_scheduler->clk));
    }

    return NULL;
}

void * js_thread_function(void * args) {
    struct server_info *info = args;

    // socket message buffers
    char from_client[256];
    char server_response[256];

    // listen for connections
    int client_socket = accept(info->server_socket, NULL, NULL);
    
    // Job scheduler main loop
    while (1) {

        // get and serialize process from client
        recv(client_socket, from_client, sizeof(from_client), 0);
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

        // print incoming message from client
        // printf("Mensaje del cliente: \n");
        // printf("PID: %d\n", p->pid);
        // printf("Arrival time: %d\n", p->arrival_time);
        // printf("CPU burst time: %d\n", p->cpu_burst_time);
        // printf("CPU remain time: %d\n", p->cpu_remain_time);
        // printf("Priority: %d\n", p->priority);
        // printf("Termination time: %d\n", p->termination_time);

        // add process to job scheduler queue (Ready queue)
        // js_enqueue(info->job_scheduler->queue, p);

        
        // job_scheduling(info->job_scheduler);

        // send process to cpu scheduler
        new_process(info->cpu_scheduler, p);

        // send response to client
        sprintf(server_response, "Data received. Created process with ID: %d\n", info->pid_consecutive);
        // server_response = strcat("Data received. Created process with ID: ", itoa(info->pid_consecutive));
        send(client_socket, server_response, sizeof(server_response), 0);

        // print_processes(info->job_scheduler);
    }
    return NULL;
}