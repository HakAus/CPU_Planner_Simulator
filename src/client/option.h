// Basado en codigo del koreano

#ifndef __OPTION_H
#define __OPTION_H

struct __option {
    int help;

    char* mode; // manual or automatic
    char* file; // only for manual mode
};

typedef struct __option option_t;

/* parse option from arguments of command line
 * modify variable option to return result
 */
void parse_option (int argc, char ** argv, option_t * option);

#endif