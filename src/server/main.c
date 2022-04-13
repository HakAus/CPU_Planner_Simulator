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
#include "list.h"

int main(int argc, char** argv) { 
    
    List process_list;
    option_t opt;
    parse_option (argc, argv, &opt);

    initlist(&process_list);
    clk_t * clk = create_clock();
    cpu_t * cpu = create_cpu (clk, &process_list);
    
    job_scheduler_t * js = create_job_scheduler (clk);
    cpu_scheduler_t * cs;

    if (opt.test_fifo) {
        cs = create_cpu_scheduler ("fifo", clk);
        printf ("test_fifo\n");
    }

    else if (opt.test_np_sjf) {
        cs = create_cpu_scheduler ("sjf", clk);
        printf ("test_np_sjf\n");
    }

    else if (opt.test_np_hpf) {
        cs = create_cpu_scheduler ("hpf", clk);
        printf ("test_np_hpf\n");
    }

    else if (opt.test_rr) {
        // opt.round_robin_time_quantum
        cs = create_cpu_scheduler ("rr", clk, opt.round_robin_time_quantum);
        
        printf ("test_rr\n");
    }
    else {
        printf ("No test selected\n");
        return 0;
    }
    
    // Simulation
    js_register_cpu_scheduler (js, cs);
    register_cpu(cs, cpu);
    init_clock(clk);
    struct server_info * si = setup_server(js, cs);
    start_simulation(si);

    return 0;
}