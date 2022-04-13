#include <stdio.h>
#include <stdlib.h>
#include "client.h"
#include "process.h"
#include "reader.h"
#include "util.h"

const int UPPER_SLEEP_TIME_LIMIT = 8;
const int LOWER_SLEEP_TIME_LIMIT = 3;
const int INITIAL_MEM_ALLOC_FOR_FILE = 128;
const int MAX_LINE_SIZE = 8;

pthread_t thread_list[MAX_NUMBER_OF_THREADS];

// https://stackoverflow.com/questions/33175857/read-line-by-line-from-a-file-and-create-a-thread-for-every-line-in-a-file-in-c
void * read_processes(void * args) {
    struct reader_args* info = args;
    int lines_allocated = INITIAL_MEM_ALLOC_FOR_FILE;
    char ch;
    FILE *fp;
    pthread_t sender_thread;
    int *thread_exit_status;

    // Allocate lines of text
    char **words = (char **)malloc(sizeof(char*)*lines_allocated);
    if (words == NULL) {
        perror("Out of memory for storing lines from the file.\n");
        exit(EXIT_FAILURE);
    }
    printf("Allocated lines of text\n");

    // Open file
    printf("Nombre del archivo: %s\n", info->filename);
    fp = fopen(info->filename, "r"); // read mode
    if (fp == NULL) {
        perror("Error while opening the file.\n");
        exit(EXIT_FAILURE);
    }

    printf("Opened the file\n");

    int threads_created = 0;

    int line;
    for (line = 0; 1; line++) {
        int j;

        printf("Line number: %i\n", line);

        /* have we gone over our line allocation? */
        if (line >= lines_allocated) {
            int new_size;

            /* Double our allocation and re-allocate */
            new_size = lines_allocated*2;
            words = (char **) realloc(words, sizeof(char*) * new_size);
            if (words == NULL){
                perror("Out of memory for storing lines from the file.\n");
                exit(EXIT_FAILURE);
            }
            lines_allocated = new_size;
        }

        /* allocate space for the next line */
        words[line] = malloc(MAX_LINE_SIZE);
        if (words[line] == NULL) {
            perror("Out of memory for storing lines from the file.\n");
            exit(EXIT_FAILURE);
        }

        if (fgets(words[line], MAX_LINE_SIZE-1, fp) == NULL)
            break;

        printf("Allocated space for the next line \n");

        /* get rid of CR or LF at end of line */
        for (j=strlen(words[line])-1; j>=0 && (words[line][j]=='\n' || words[line][j]=='\r'); j--)
        ;
        words[line][j+1]='\0';

        // create thread function args
        struct connection_args* conn_args = malloc(sizeof(struct connection_args));

        // separate burst and priority from line
        conn_args->client_socket = info->client_socket;
        char * split = strtok(words[line], " ");
        conn_args->burst = atoi(split);
        split = strtok(NULL, " ");
        conn_args->priority = atoi(split);

        // create a thread to send the process to the job scheduler
        pthread_create( &sender_thread, NULL , connection_handler , (void*) conn_args);
        thread_list[line] = sender_thread;
        threads_created++;

        // wait for a random time between 3 and 8 seconds
        int creation_time = get_random_in_range(LOWER_SLEEP_TIME_LIMIT, UPPER_SLEEP_TIME_LIMIT);
        printf("Creation time: %i ...\n", creation_time);
        sleep(creation_time); 
    }

    for (int i = 0; i < threads_created; i++) {
        pthread_join(thread_list[i], (void**)&(thread_exit_status));

        if (thread_exit_status == PTHREAD_CANCELED) {
            perror("Thread join failed.");
        }
    }
    

    fclose(fp);

    return NULL;
}

void *connection_handler(void* conn_args) {
    struct connection_args* info = conn_args;

    // create process
    process_t * process = create_manual_process(info->burst, info->priority);
    printf("Sending process to server ...\n");

    // wait 2 seconds before sending
    sleep(2);
    send_message(info->client_socket, process);

    // kill thread after server response
    pthread_exit(NULL);

    return NULL;
}

void init_reader(void *arg) {

    char * file_name = arg;
    pthread_t reader_thread;
    int *thread_exit_status;

    struct reader_args* args = malloc(sizeof(struct reader_args));

    args->filename = file_name;
    args->client_socket = start_connection();
    
    pthread_create(&reader_thread, NULL, read_processes, args);

    pthread_join(reader_thread, (void**)&(thread_exit_status));

    if (thread_exit_status != PTHREAD_CANCELED) {
        printf("Client halted normally");
    }
}