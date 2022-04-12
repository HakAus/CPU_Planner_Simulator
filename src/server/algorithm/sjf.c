#include <stdlib.h>
#include "../cpu.h"
#include "sjf.h"

#define NODE struct __sjf_node
#define QUEUE struct __sjf_queue

struct __sjf_queue * create_sjf_queue () {
    QUEUE * queue = (QUEUE *) malloc (sizeof (QUEUE));
    queue->head = NULL;
    return queue;
}

void sjf_scheduling (cpu_scheduler_t * this) {
    if (is_running (this->cpu)) {
        return;
    }
    if (sjf_is_empty ((QUEUE *) this->queue)) {
        return;
    }
    process_t * orig;
    execute (this->cpu, sjf_dequeue ((QUEUE *) this->queue), &orig);
}

void sjf_enqueue (struct __sjf_queue * queue, process_t * process) {
    NODE * node = (NODE *) malloc (sizeof (NODE));
    node->p = process;
    node->next = NULL;

    NODE * t = queue->head;
    NODE * bf = NULL;
    while (t != NULL && t->p->cpu_burst_time <= process->cpu_burst_time) {
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

process_t * sjf_dequeue (QUEUE * queue) {
    NODE * del = queue->head;
    process_t * r = del->p;
    queue->head = del->next;
    free (del);
    return r;
}

int sjf_is_empty (QUEUE * queue) {
    return queue->head == NULL;
}

void print_sjf_queue (cpu_scheduler_t * this) {
    QUEUE * q = this->queue;
    NODE * t = q->head;
    printf ("+-----+--------------+----------------+---------------+\n");
    printf ("| pid | arrival_time | cpu_burst_time | priority |\n");
    printf ("+-----+--------------+----------------+---------------+\n");

    while (t != NULL) {
        process_t * p = t->p;
        printf ("| %3u | %12u | %14u |  %8u |\n", p->pid, p->arrival_time, p->cpu_burst_time, p->priority);
        printf ("+-----+--------------+----------------+---------------+\n");
        t = t->next;
    }
    printf ("\n");
}