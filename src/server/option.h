#ifndef __OPTION_H
#define __OPTION_H

struct __option {
    int help;

    int test_fifo;
    int test_np_sjf;
    int test_np_hpf;
    int test_rr;

    int num_of_processes;
    int round_robin_time_quantum;
};

typedef struct __option option_t;

/* parse option from arguments of command line
 * modify variable option to return result
 */
void parse_option (int argc, char ** argv, option_t * option);

#endif