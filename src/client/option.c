#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "option.h"

#define DEFAULT_FILE "processes.txt"

void parse_option (int argc, char ** argv, option_t * opt) {
    // default
    opt->help = FALSE;
    opt->mode = AUTO_MODE;
    opt->file = DEFAULT_FILE;
    opt->file_set = FALSE;

    for (int i = 1; i < argc; i++) {
        if (strcmp ("--auto", argv [i]) == 0) {
            opt->mode = AUTO_MODE;
        } else if (strcmp ("--manual", argv[i]) == 0) {
            opt->mode = MANUAL_MODE;
        } else if (opt->mode == MANUAL_MODE && strcmp ("--file", argv [i]) == 0) {
            i++;
            opt->file = argv[i];
            opt->file_set = TRUE;
        } else if (opt->mode == AUTO_MODE && strcmp ("--file", argv [i]) == 0) {
            opt->mode = INVALID_OPTION_MODE;
            printf("El modo automático no requiere de un archivo de procesos. \n\n");
        } else if (strcmp ("-h", argv [i]) == 0 || strcmp ("--help", argv [i]) == 0) {
            printf ("Aiuuuuda");
            opt->help = TRUE;
            return;
        } else {
            opt->help = TRUE;
            printf ("Por favor revise bien sus argumentos\n");
            return;
        }
    }

    if (opt->mode == MANUAL_MODE && opt->file_set == FALSE) {
        opt->mode = INVALID_OPTION_MODE;
    }

    if (opt->mode == INVALID_OPTION_MODE) {
        printf ("Por favor revise bien sus argumentos\n");
    }
}