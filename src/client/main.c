#include "option.h"

int main(int argc, char** argv) {
    
    option_t opt;
    parse_option (argc, argv, &opt);

    return 0;
}