// Basado en codigo del koreano

#ifndef __OPTION_H
#define __OPTION_H

#define TRUE 1
#define FALSE 0

#define AUTO_MODE 0
#define MANUAL_MODE 1
#define INVALID_OPTION_MODE 2

struct __option {
    int help;

    int mode; // manual or automatic
    int file_set;
    char* file; // only for manual mode
};

typedef struct __option option_t;

/* parse option from arguments of command line
 * modify variable option to return result
 */
void parse_option (int argc, char ** argv, option_t * option);

#endif