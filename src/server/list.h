#ifndef _LIST_H
#define _LIST_H

#include "process.h"

struct item {
    int id;
    process_t * process;
    struct item * next;
};

typedef struct item Item;

struct list {
    Item *head;
    int count;
};

typedef struct list List;

void initlist (List * list);

void insert(List * list, process_t *);

process_t * getItem(List * list, int n); 

#endif 