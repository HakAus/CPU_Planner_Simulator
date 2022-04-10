#ifndef __UTIL_H
#define __UTIL_H

#include <stdlib.h>
#include <unistd.h>
#include <time.h>

#define MAX_NUMBER_OF_THREADS 10000
// https://www.educba.com/random-number-generator-in-c/
int get_random_in_range(int lower_end, int higher_end);

#endif