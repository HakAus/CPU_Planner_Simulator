#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

#include "option.h"


#define DEFAULT_FILE "processes.txt"

// int is_positive_digit(char* value) {
//     return isnumber(value) && (atoi(value) > 0);
// }
void parse_option (int argc, char ** argv, option_t * opt) {
    // default
    opt->help = FALSE;
    opt->mode = AUTO_MODE;
    opt->file = DEFAULT_FILE;
    opt->file_set = FALSE;
    opt->burstMin = -1;
    opt->burstMax = -1;
    opt->creationMin = -1;
    opt->creationMax = -1;

    for (int i = 1; i < argc; i++) {
        if (strcmp ("--auto", argv[i]) == 0) {
            opt->mode = AUTO_MODE;
            printf("Se escogio el modo automatico\n");
        } else if (strcmp ("--manual", argv[i]) == 0) {
            opt->mode = MANUAL_MODE;
            printf("Se escogio el modo manual\n");
        } else if (opt->mode == MANUAL_MODE && strcmp("--file", argv[i]) == 0) {
            i++;
            opt->file = argv[i];
            opt->file_set = TRUE;
        } else if (opt->mode == AUTO_MODE && strcmp("--file", argv[i]) == 0) {
            opt->mode = INVALID_OPTION_MODE;
            printf("El modo automático no requiere de un archivo de procesos. \n\n");
        } else if (opt->mode == AUTO_MODE && strcmp("--minBurst", argv[i]) == 0) {
            // if (is_positive_digit(argv[i])) 
            i++;
            opt->burstMin = atoi(argv[i]);
            printf("Se definio minBurst como %d\n", opt->burstMin);
        } else if (opt->mode == AUTO_MODE && strcmp("--maxBurst", argv[i]) == 0) {
            // if (is_positive_digit(argv[i])) 
            i++;
            opt->burstMax = atoi(argv[i]);
            printf("Se definio maxBurst como %d\n", opt->burstMax);
        } else if (opt->mode == AUTO_MODE && strcmp("--creationMin", argv[i]) == 0) {
            // if (is_positive_digit(argv[i])) 
            i++;
            opt->creationMin = atoi(argv[i]);
            printf("Se definio creationMin como %d\n", opt->creationMin);
        } else if (opt->mode == AUTO_MODE && strcmp("--creationMax", argv[i]) == 0) {
            // if (is_positive_digit(argv[i])) 
            i++;
            opt->creationMax = atoi(argv[i]);
            printf("Se definio creationMax como %d\n", opt->creationMax);
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

    if (opt->mode == AUTO_MODE && (opt->burstMin == -1 ||
                                   opt->burstMax == -1 ||
                                   opt->creationMin == -1 ||
                                   opt->creationMax == -1))
    {
        opt->mode = INVALID_OPTION_MODE;
    }

    if (opt->mode == INVALID_OPTION_MODE) {
        printf ("Por favor revise bien sus argumentos\n");
    }
}