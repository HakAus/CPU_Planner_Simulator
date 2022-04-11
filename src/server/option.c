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
            printf ("   --fifo          simulate Fisrt Come First Served\n");
            printf ("   --np-sjf        simulate Non-Preemptive Shortest Job First\n");
            printf ("   --np-hpf   simulate Non-Preemptive hpf\n");
            printf ("   --rr            simulate Round Robin\n");
            printf ("\n");
            opt->help = TRUE;
            return;
        } else if (strcmp ("--fifo", argv [i]) == 0) {
            opt->test_fifo = TRUE;
        } else if (strcmp ("--np_sjf", argv [i]) == 0) {
            opt->test_np_sjf = TRUE;
        } else if (strcmp ("--np_hpf", argv [i]) == 0) {
            opt->test_np_hpf = TRUE;
        } else if (strcmp ("--rr", argv [i]) == 0) {
            opt->test_rr = TRUE;
        } else {
            opt->help = TRUE;
            printf ("Please check arguments\n");
            printf ("   \'main -h\' or \'main --help\' for help\n");
            return;
        }
    }