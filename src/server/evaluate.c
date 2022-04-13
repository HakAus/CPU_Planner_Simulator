#include <stdio.h>

#include "evaluate.h"

double evaluate_turn_around_time (int n, List * list, int * rl) {
    int sum = 0;
    int tt = 0;
   
    for (int i = 1; i <= n; i++) {
        process_t * p = getItem(list, i);
        tt = p->termination_time - p->arrival_time + 1;
        sum = sum + tt;
        rl[p->pid] = tt;
    }
    return (double) sum / n;
}

double evaluate_waiting_time (int n, List * list, int * rl) {
    int sum = 0;
    int wt = 0;
    for (int i = 1; i <= n; i++) {
        process_t * p = getItem(list, i);
        wt = p->termination_time - p->arrival_time - p->cpu_burst_time + 1;
        sum = sum + wt;
        rl[p->pid] = wt;
    }
    return (double) sum / n;
}

void print_list (char * desc, int n, int * list) {
    printf ("+-----+------------------+\n");
    printf ("| pid | %16s |\n", desc);
    printf ("+-----+------------------+\n");

    for (int i = 1; i <= n; i++) {
        printf ("| %3d | %16d |\n", i, list [i]);
        printf ("+-----+------------------+\n");
    }
}