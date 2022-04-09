#include "util.h"

int get_random_in_range(int lower_end, int higher_end) {
    int rand_num;
    srand(time(NULL));
    rand_num = rand() % (higher_end - lower_end + 1) + lower_end;
    return rand_num;
}