#include <stdio.h>
#include <stdlib.h>
#include "reader.h"

const int UPPER_SLEEP_TIME_LIMIT = 8;
const int LOWER_SLEEP_TIME_LIMIT = 3;
const int INITIAL_MEM_ALLOC_FOR_FILE = 128;
const int MAX_LINE_SIZE = 8;

// https://www.educba.com/random-number-generator-in-c/
int getRandomSleepTime() {
    int rand_num;
    srand(time(NULL));
    rand_num = rand() % (UPPER_SLEEP_TIME_LIMIT - LOWER_SLEEP_TIME_LIMIT + 1) + LOWER_SLEEP_TIME_LIMIT;
    printf("Random number generated: %i", rand_num);
    return rand_num;
}

// https://stackoverflow.com/questions/33175857/read-line-by-line-from-a-file-and-create-a-thread-for-every-line-in-a-file-in-c
void * read_processes(void *file_name) {
    char* fn = (char*) file_name;
    int lines_allocated = INITIAL_MEM_ALLOC_FOR_FILE;
    char ch;
    FILE *fp;
    pthread_t sender_thread;

    // Allocate lines of text
    char **words = (char **)malloc(sizeof(char*)*lines_allocated);
    if (words == NULL) {
        perror("Out of memory for storing lines from the file.\n");
        exit(EXIT_FAILURE);
    }
    printf("Allocated lines of text\n");

    // Open file

    printf("Nombre del archivo: %s\n", fn);
    fp = fopen(fn, "r"); // read mode
    if (fp == NULL) {
        perror("Error while opening the file.\n");
        exit(EXIT_FAILURE);
    }

    printf("Opened the file\n");

    int i;
    for (i = 0; 1; i++) {
        int j;

        printf("Line number: %i\n", i);

        /* have we gone over our line allocation? */
        if (i >= lines_allocated) {
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
        words[i] = malloc(MAX_LINE_SIZE);
        if (words[i] == NULL) {
            perror("Out of memory for storing lines from the file.\n");
            exit(EXIT_FAILURE);
        }
        if (fgets(words[i], MAX_LINE_SIZE-1, fp) == NULL)
            break;
        printf("Allocated space for the next line \n");

        /* get rid of CR or LF at end of line */
        for (j=strlen(words[i])-1; j>=0 && (words[i][j]=='\n' || words[i][j]=='\r'); j--)
        ;
        words[i][j+1]='\0';

        // create a thread to send the process to the job scheduler
        pthread_create( &sender_thread, NULL , connection_handler , words[i]);

        // wait for a random time between 3 and 8 seconds
        int waitTime = getRandomSleepTime();
        printf("Waiting for random time: %i ...\n",waitTime);
        sleep(waitTime); 
    }

    fclose(fp);

    return NULL;
}

void *connection_handler(void* message) {
    // wait for 2 seconds
    char* m = message;
    sleep(2);    
    printf("The message to send to the server is %s\n", m);

    return NULL;
}

void init_reader(void *arg) {

    char * file_name = arg;
    pthread_t reader_thread;
    size_t i;
    int *thread_exit_status;

    printf("Dentro de init reader, el nombre del archivo es: %s\n",file_name);

    pthread_create(&reader_thread, NULL, read_processes, file_name);

    pthread_join(reader_thread, (void**)&(thread_exit_status));

    if (thread_exit_status != PTHREAD_CANCELED) {
        printf("Client halted normally");
    }
}

// char* readLine(FILE* fp, const char* file_name) {
//     char * line = NULL;
//     size_t len = 0;
//     ssize_t read;

//     fp = fopen(file_name, "r");
//     if (fp == NULL)
//         exit(EXIT_FAILURE);

//     if ((read = getline(&line, &len, fp)) != -1) {
//         return line;
//     }

//     // while ((read = getline(&line, &len, fp)) != -1) {
//     //     printf("Retrieved line of length %zu:\n", read);
//     //     printf("%s", line);
//     // }

//     // if (line)
//     //     free(line);
//     // exit(EXIT_SUCCESS);
// }

// void closeFile(FILE* fp) {
//     fclose(fp);
// }