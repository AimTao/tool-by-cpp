#include <stdio.h>
#include <string.h>

int main(int argc, char** argv) {
    if (!strcmp(argv[1], argv[2])) {
        printf("error: two files with the same name！");
        return 0;
    }
    FILE *source_fp = NULL;
    FILE *copy_fp = NULL;
    source_fp = fopen(argv[1], "rb+");
    if (source_fp == NULL) {
        perror("open file failed:");
    }
    copy_fp  = fopen(argv[2], "wb+");
    if (copy_fp == NULL) {
        perror("copy file failed:");
    }

    int res = 1;
    while (!feof(source_fp)) {
        char tmp[1024] = {0};
        res = fread(tmp, 1, 1024, source_fp);
        printf("%d\n", res);
        fwrite(tmp, 1, 1024, copy_fp);
    }
    fclose(source_fp);
    fclose(copy_fp);
    return 0;
}
