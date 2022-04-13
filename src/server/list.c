#include "list.h"
#include <stdlib.h>


void initlist(List *list) {
    list->head = NULL;
    list->count = 0;
}

void insert(List *list, process_t *p) {
    Item *item = (Item *) malloc(sizeof(Item));
    item->process = p;
    item->id = p->pid;
    item->next = list->head;
    list->head = item;
    list->count++;
}

process_t * getItem(List *list, int id) {
    Item *item;
    int count = 1;
    item = list->head;
    if (id == 1) {
        return item->process;
    }
    while (item->next != NULL) {
        item = item->next;
        count++;
        if (id == count)
            return item->process;
    }
    return NULL;
    
}