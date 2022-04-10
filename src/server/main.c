#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/types.h>
#include <sys/socket.h>

#include <netinet/in.h>
#include <unistd.h>

#include "option.h"
#include "process.h"
#include "clock.h"
#include "server.h"
#include "cpu_scheduler.h"
#include "job_scheduler.h"

int main(int argc, char** argv) { 
    
    option_t opt;
    parse_option (argc, argv, &opt);

    // Prueba job scheduler
    clk_t * clk = create_clock();
    cpu_t * cpu = create_cpu (clk);
    
    job_scheduler_t * js = create_job_scheduler (clk);
    cpu_scheduler_t * cs;
    

    if (opt.test_fifo) {
        cs = create_cpu_scheduler ("fifo", clk);
        printf ("test_fifo\n");
    }

    else if (opt.test_np_sjf) {
        cs = create_cpu_scheduler ("np_sjf", clk);
        printf ("test_np_sjf\n");
    }

    else if (opt.test_np_hpf) {
        cs = create_cpu_scheduler ("np_hpf", clk);
        printf ("test_np_hpf\n");
    }

    else if (opt.test_rr) {
        cs = create_cpu_scheduler ("rr", clk);
        printf ("test_rr\n");
    }
    else {
        printf ("No test selected\n");
        return 0;
    }
    
    js_register_cpu_scheduler (js, cs);

    setup_server(js, cs);
    // create_processes (js, 5);
    // print_processes (js);


    return 0;
}