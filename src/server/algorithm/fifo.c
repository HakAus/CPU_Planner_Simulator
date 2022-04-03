#include <stdlib.h>

#include "fifo.h"
#include "../cpu.h"

#define QUEUE struct __fifo_queue
#define NODE struct __fifo_node

struct __fifo_node {
    process_t * process;
    NODE * next;
};

struct __fifo_queue {
    NODE * head;
    NODE * tail;
};

int fifo_is_empty (QUEUE * queue) {
    return queue->head == NULL;
}

process_t * fifo_dequeue (QUEUE * queue) {
    NODE * del = queue->head;
    queue->head = del->next;
    process_t * p = del->process;
    free (del);
    return p;
}

void * create_fifo_queue () {
    QUEUE * queue = (QUEUE *) malloc (sizeof (QUEUE));
    queue->head = NULL;
    queue->tail = NULL;
    return (void *) queue;
}

void fifo_scheduling (cpu_scheduler_t * this) {
    if (is_running (this->cpu)) {
        return;
    }
    if (fifo_is_empty ((QUEUE *) this->queue)) {
        return;
    }
    process_t * orig;
    execute (this->cpu, fifo_dequeue ((QUEUE *) this->queue), &orig);
}

void fifo_enqueue (void * arg, process_t * process) {
    QUEUE * queue = (QUEUE *) arg;
    NODE * node = (NODE *) malloc (sizeof (NODE));
    node->process = process;
    node->next = NULL;
    if (queue->head == NULL) {
        queue->head = node;
    } else {
        queue->tail->next = node;
    }
    queue->tail = node;
}