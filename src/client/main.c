#include <stdio.h>
#include "option.h"
#include "reader.h"

int main(int argc, char** argv) {

    option_t opt;
    parse_option (argc, argv, &opt);

    if (opt.mode !=  INVALID_OPTION_MODE) {
        if (opt.mode == AUTO_MODE) {
            printf("Se escogio el modo automatico");
        } else if (opt.mode == MANUAL_MODE) {
            printf("Se escogio el modo manual");
            read("processes.txt");
        }
    } else {
        printf("Inténtelo de nuevo.");
    }
    
    
    return 0;
}