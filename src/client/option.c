#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "option.h"

#define TRUE 1
#define FALSE 0

#define DEFAULT_MODE "auto"
#define DEFAULT_FILE "processes.txt"

void parse_option (int argc, char ** argv, option_t * opt) {
    // default
    opt->help = FALSE;
    opt->mode = DEFAULT_MODE;
    opt->file = DEFAULT_FILE;

    for (int i = 1; i < argc; i++) {
        if (strcmp ("-m", argv [i]) == 0) {
            i++;
            if (strcmp("auto", argv[i]) == 0 || strcmp("man", argv[i]) == 0) {
                opt->mode = argv[i];
                i++;
                printf("Modo seleccionado\n");
                if (strcmp("man", opt->mode) == 0 && strcmp("-f", argv[i]) == 0) {
                    i++;
                    opt->file = argv[i];
                    printf("Archivo seleccionado \n");
                } else if (strcmp("auto", opt->mode) == 0 && strcmp("-f", argv[i]) == 0) {
                    printf("El modo auto no requiere que se le pase un archivo");
                }
            } else {
                printf("Invalid mode selected, choose 'auto' or 'manual'\n\n.");
            }
        } else if (strcmp ("-h", argv [i]) == 0 || strcmp ("--help", argv [i]) == 0) {
            printf ("Usage: simulator <options> <scheduler options>\n");
            printf ("\n");
            printf ("options are:\n");
            printf ("   -h, --help      show the list of options\n");
            printf ("\n");
            printf ("with no scheduler options simulate all cpu scheduler algorithms\n");
            printf ("scheduler options are:\n");
            printf ("   --fcfs          simulate Fisrt Come First Served\n");
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
        } else {
            opt->help = TRUE;
            printf ("Please check arguments\n");
            printf ("   \'simulator -h\' or \'simulator --help\' for help\n");
            return;
        }
    }
}