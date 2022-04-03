#ifndef __READER_H
#define __READER_H

struct reader {
    FILE *fp;
};

void read(char* file_name);

#endif