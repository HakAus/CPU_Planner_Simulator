#include <stdlib.h>
#include "../cpu.h"
#include "hpf.h"

#define NODE struct __priority_node
#define QUEUE struct __priority_queue

QUEUE * create_priority_queue () {
    QUEUE * queue = (QUEUE *) malloc (sizeof (QUEUE));
    queue->head = NULL;
    return queue;
}

void hpf_scheduling (cpu_scheduler_t * this) {
    if (is_running (this->cpu)) {
        return;
    }
    if (priority_is_empty ((QUEUE *) this->queue)) {
        return;
    }
    process_t * orig;
    execute (this->cpu, priority_dequeue ((QUEUE *) this->queue), &orig);
}

void priority_enqueue (QUEUE * queue, process_t * process) {
    NODE * node = (NODE *) malloc (sizeof (NODE));
    node->p = process;
    node->next = NULL;

    NODE * t = queue->head;
    NODE * bf = NULL;
    while (t != NULL && t->p->priority <= process->priority) {
        bf = t;
        t = t->next;
    }
    node->next = t;
    if (bf == NULL) {
        node->next = queue->head;
        queue->head = node;
    } else {
        bf->next = node;
    }
}

process_t * priority_dequeue (QUEUE * queue) {
    NODE * del = queue->head;
    process_t * r = del->p;
    queue->head = del->next;
    free (del);
    return r;
}

int priority_is_empty (QUEUE * queue) {
    return queue->head == NULL;
}