#include <stdio.h>
#include <stdlib.h>


void read(char* file_name) {
    char ch;
    FILE *fp;

    fp = fopen(file_name, "r"); // read mode

    if (fp == NULL)
    {
        perror("Error while opening the file.\n");
        exit(EXIT_FAILURE);
    }

    fclose(fp);
}

char* readLine(FILE* fp) {
    char ch;
    char* line;
    do {
        ch = fgetc(fp);
        // line
        // printf("%c", ch);
    }
    while(ch != '\n' || ch != EOF);
}