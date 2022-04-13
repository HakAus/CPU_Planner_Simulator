#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "option.h"

#define TRUE 1
#define FALSE 0

void parse_option (int argc, char ** argv, option_t * opt) {
    // default
    opt->help = FALSE;
    opt->test_fifo = FALSE;
    opt->test_np_sjf = FALSE;
    opt->test_np_hpf = FALSE;
    opt->test_rr = FALSE;

    for (int i = 1; i < argc; i++) {
        if (strcmp ("-h", argv [i]) == 0 || strcmp ("--help", argv [i]) == 0) {
            printf ("Usage: main <options> <scheduler options>\n");
            printf ("\n");
            printf ("options are:\n");
            printf ("   -h, --help      show the list of options\n");
            printf ("\n");
            printf ("scheduler options are:\n");
            printf ("   --fifo      simulate Fisrt Come First Served\n");
            printf ("   --sjf       simulate Non-Preemptive Shortest Job First\n");
            printf ("   --hpf       simulate Non-Preemptive hpf\n");
            printf ("   --rr <qt>       simulate Round Robin\n");
            printf ("\n");
            opt->help = TRUE;
            return;
        } else if (strcmp ("--fifo", argv [i]) == 0) {
            opt->test_fifo = TRUE;
        } else if (strcmp ("--sjf", argv [i]) == 0) {
            opt->test_np_sjf = TRUE;
            printf("sjf\n");
        } else if (strcmp ("--hpf", argv [i]) == 0) {
            opt->test_np_hpf = TRUE;
            printf("hpf\n");
        } else if (strcmp ("--rr", argv [i]) == 0) {
            opt->test_rr = TRUE;
            if(i+1 < argc) {
                opt->round_robin_time_quantum = atoi(argv[i+1]);
                printf("rr\n");
            }
            else{
                printf("Error: --rr requires a time quantum\n");
                exit(1);
            }
        } else {
            opt->help = TRUE;
            printf ("Please check arguments\n");
            printf ("   \'main -h\' or \'main --help\' for help\n");
            return;
        }
    }
}