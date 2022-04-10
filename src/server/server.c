#include "server.h"

#define ACTIVE 1
#define INACTIVE 0

int scheduling = INACTIVE;
int stop = INACTIVE;

void setup_server(job_scheduler_t * job_scheduler, cpu_scheduler_t * cpu_scheduler) {

    int *thread_exit_status;

    // create the server socket
    struct server_info *s_info = malloc(sizeof(struct server_info));

    // create server info object
    s_info->server_socket = socket(AF_INET, SOCK_STREAM, 0);
    s_info->job_scheduler;
    s_info->cpu_scheduler;

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

    scheduling = ACTIVE;

    pthread_t server_thread, clock_thread;
    s_info->clock = create_clock();
    printf("Running server ...\n");

    pthread_create(&clock_thread, NULL, run_clock, (void*) s_info->clock);
    pthread_create(&server_thread, NULL, schedule_jobs, (void*) s_info);

    pthread_join(server_thread, (void**)&(thread_exit_status));
    pthread_join(clock_thread, (void**)&(thread_exit_status));

    if (thread_exit_status != PTHREAD_CANCELED) {
        printf("Client halted normally");
    }
}

void * run_clock(void * clock) {
    struct clk_t * clk = clock;
    while (1) {
        clocking(clk);
        sleep(1);
    }
}

void * schedule_jobs(void * args) {
    struct server_info *info = args;

    // socket message buffers
    char from_client[256];
    char server_response[256] = "OK";

    // listen for connections
    int client_socket = accept(info->server_socket, NULL, NULL);

    // clock for calculating arrival time
    
    // Job scheduler main loop
    while (scheduling) {

        // get and serialize process from client
        recv(client_socket, from_client, sizeof(from_client), 0);
        int pid, arrival_time, cpu_burst_time, cpu_remain_time, termination_time, priority; 
        process_t * p = (process_t *) malloc (sizeof (process_t));
        sscanf(from_client, "%d,%d,%d,%d,%d,%d",
               &pid, &arrival_time, &cpu_burst_time, 
               &cpu_remain_time, &termination_time, &priority);

        p->pid = info->pid_consecutive++;
        p->arrival_time = get_time(info->clock);
        p->cpu_burst_time = cpu_burst_time;
        p->cpu_remain_time = cpu_remain_time;
        p->termination_time = termination_time;
        p->priority = priority;

        // print incoming message from client
        printf("Mensaje del cliente: \n");
        printf("PID: %d\n", p->pid);
        printf("Arrival time: %d\n", p->arrival_time);
        printf("CPU burst time: %d\n", p->cpu_burst_time);
        printf("CPU remain time: %d\n", p->cpu_remain_time);
        printf("Priority: %d\n", p->priority);
        printf("Termination time: %d\n", p->termination_time);


        // put process in ready queue
        // info->job_scheduler->queue(info->job_scheduler->queue, p);  // LINEA CON ERROR

        send(client_socket, server_response, sizeof(server_response), 0);
        // send the message to the client
    }
    return NULL;
}