#include <stdio.h>
#include <string.h>

int main(int argc, char** argv) {
    FILE *source_fp = NULL;
    FILE *copy_fp = NULL;
    source_fp = fopen(argv[1], "rb+");
    if (source_fp == NULL) {
        perror("打开文件失败：");
    }
    copy_fp  = fopen(argv[2], "wb+");
    if (copy_fp == NULL) {
        perror("复制文件失败：");
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
