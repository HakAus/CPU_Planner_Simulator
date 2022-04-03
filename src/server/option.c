#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "option.h"

#define TRUE 1
#define FALSE 0

#define DEFAULT_NUM_PROCESS 10
#define DEFAULT_TIME_QUANTUM 4

void parse_option (int argc, char ** argv, option_t * opt) {
    // default
    opt->help = FALSE;
    opt->test_fifo = FALSE;
    opt->test_np_sjf = FALSE;
    opt->test_np_hpf = FALSE;
    opt->test_rr = FALSE;

    opt->num_of_processes = DEFAULT_NUM_PROCESS;
    opt->round_robin_time_quantum = DEFAULT_TIME_QUANTUM;

    for (int i = 1; i < argc; i++) {
        if (strcmp ("-n", argv [i]) == 0) {
            i++;
            opt->num_of_processes = atoi (argv [i]);
        } else if (strcmp ("-tq", argv [i]) == 0) {
            i++;
            opt->round_robin_time_quantum = atoi (argv [i]);
        } else if (strcmp ("-h", argv [i]) == 0 || strcmp ("--help", argv [i]) == 0) {
            printf ("Usage: simulator <options> <scheduler options>\n");
            printf ("\n");
            printf ("options are:\n");
            printf ("   -h, --help      show the list of options\n");
            printf ("   -n <int>        number of processes to create (default : %d)\n", DEFAULT_NUM_PROCESS);
            printf ("   -tq <int>       size of time quantum of round-robin scheduler (default : %d)\n", DEFAULT_TIME_QUANTUM);
            printf ("\n");
            printf ("with no scheduler options simulate all cpu scheduler algorithms\n");
            printf ("scheduler options are:\n");
            printf ("   --fifo          simulate Fisrt Come First Served\n");
            printf ("   --np-sjf        simulate Non-Preemptive Shortest Job First\n");
            printf ("   --p-sjf         simulate Preemptive Shortest Job First\n");
            printf ("   --np-priority   simulate Non-Preemptive Priority\n");
            printf ("   --p-priority    simulate Preemptive Priority\n");
            printf ("   --rr            simulate Round Robin\n");
            printf ("   --np-srtf       simulate Non-Preemptive Shortest Remain Time First\n");
            printf ("   --p-srtf        simulate Preemptive Shortest Remain Time First\n");
            printf ("\n");
            printf ("Korea Univ. KOSMOS\n");
            opt->help = TRUE;
            return;
        } else if (strcmp ("--fifo", argv [i]) == 0) {
            opt->test_fifo = TRUE;
        } else if (strcmp ("--np-sjf", argv [i]) == 0) {
            opt->test_np_sjf = TRUE;
        } else if (strcmp ("--np-priority", argv [i]) == 0) {
            opt->test_np_hpf = TRUE;
        } else if (strcmp ("--rr", argv [i]) == 0) {
            opt->test_rr = TRUE;
        } else {
            opt->help = TRUE;
            printf ("Please check arguments\n");
            printf ("   \'simulator -h\' or \'simulator --help\' for help\n");
            return;
        }
    }
    if (!opt->test_fifo
    && !opt->test_np_sjf
    && !opt->test_np_hpf
    && !opt->test_rr) {
        // if all false
        opt->test_fifo = TRUE;
        opt->test_np_sjf = TRUE;
        opt->test_np_hpf = TRUE;
        opt->test_rr = TRUE;
    }
}