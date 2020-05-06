#include <stdio.h>

int main(int argc, char **argv) {
    FILE *fp = NULL;
    fp = fopen(argv[1], "rb+");
    if (fp == NULL) {
        perror("file open failed:");
    }
    fseek(fp, 0, SEEK_END);
    long size = ftell(fp);
    printf("the size of this file : %ld Byte", size);
    fclose(fp);
    return 0;
}