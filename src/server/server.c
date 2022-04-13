#include "server.h"
#include "evaluate.h"

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

void start_simulation(struct server_info * info) {
    
    int *thread_exit_status;

    printf("Starting simulation ...\n");

    // create threads
    info->client_count = 0;
    pthread_create(&info->cpu_scheduler_thread, NULL, cs_thread_function, (void*) info);
    pthread_create(&info->accept_client_thread, NULL, accept_client_thread_function, (void*) info);
    pthread_create(&info->input_thread, NULL, read_user_input, (void*) info);

    // wait for threads to complete
    pthread_join(info->cpu_scheduler_thread, (void**)&(thread_exit_status));
    pthread_join(accept_client_thread_function, (void**)&(thread_exit_status));
    pthread_join(info->input_thread, (void**)&(thread_exit_status));
    for (int i = 0; i < MAX_CLIENTS; i++) {
        pthread_join(info->job_scheduler_threads[i], (void**)&(thread_exit_status));
    }

    // check that threads finished correctly
    if (thread_exit_status != PTHREAD_CANCELED) {
        printf("Client halted normally");
    }
}

void stop_simulation(struct server_info * info) {
    pthread_cancel(info->cpu_scheduler_thread);
    for (int i = 0; i < info->client_count; i++) {
        pthread_cancel(info->job_scheduler_threads[i]);
    }
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
        // wait for a client connection
        info->client_sockets[info->client_count] = accept(info->server_socket, NULL, NULL);

        // create a thread for the client
        pthread_create(&info->job_scheduler_threads[info->client_count], NULL, js_thread_function, (void*) info);
        info->client_count++;
    }

    printf("All possible clients have connected ...\n");

    return NULL;
}

void * read_user_input(void * args)
{
    struct server_info *info = args;
    while (1) {
        char input[100];
        scanf("%s", input);
        if (strcmp(input, "print") == 0) {
            info->cpu_scheduler->print_ready_queue(info->cpu_scheduler);
        } else if (strcmp(input, "quit") == 0) {
            stop_simulation(info);

            printf("Se ha terminado la simulación\n");

            // statics(info->cpu_scheduler->cpu);

          
            cpu_t * cpu = info->cpu_scheduler->cpu;
            
            List * process_list = cpu->process_list;
           
            int count_list = process_list->count;
           
            int * turn_around_time_list = (int *) malloc (sizeof (int) * (count_list + 1));
        
            int * waiting_time_list = (int *) malloc (sizeof (int) * (count_list + 1));
           
            double average_turn_around_time;
           
            double average_waiting_time;
            

            average_turn_around_time = evaluate_turn_around_time(count_list ,process_list, turn_around_time_list);
            average_waiting_time = evaluate_waiting_time(count_list, process_list, waiting_time_list);

            print_list("Waiting time", count_list, waiting_time_list);
            print_list("Turn around time", count_list, turn_around_time_list);
            printf("The average turn around time is: %f\n", average_turn_around_time);
            printf("The average waiting time: %f\n", average_waiting_time);
            printf("The total processes exucuted: %d\n", count_list);

            
        }
    }

    return NULL;
}

// void * statics(cpu_t * cpu){

// } 

void * js_thread_function(void * args) {
    struct server_info *info = args;

    // socket message buffers
    char from_client[256];
    char server_response[256];

    // Job scheduler main loop
    while (1) {

        // get and serialize process from client
        for (int i = 0; i < info->client_count; i++) {

            // receive message from client
            recv(info->client_sockets[i], from_client, sizeof(from_client), 0);

            // deserialize message
            int pid, arrival_time, cpu_burst_time, cpu_remain_time, termination_time, priority; 
            process_t * p = (process_t *) malloc (sizeof (process_t));
            sscanf(from_client, "%d,%d,%d,%d,%d,%d",
                &pid, &arrival_time, &cpu_burst_time, 
                &cpu_remain_time, &termination_time, &priority);
            ++info->pid_consecutive;
            p->pid = info->pid_consecutive;
            p->arrival_time = get_time(info->cpu_scheduler->clk);
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