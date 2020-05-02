#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int main() {

    // 获取待加密文件路径
    char source_path[512] = {0};
    char backup_source_path[512] = {0};
    char enc_path[512] = {0};
    printf("请输出文件路径（例如: ../enc/hello.jpg）：");
    scanf("%s", source_path);
    strcpy(backup_source_path, source_path);
    
    // 生成已加密文件路径
    char tmp_last_path[100] = {0};
    char *strtok_p = strtok(backup_source_path, ".");
    if (strtok_p != NULL) {
        while (strtok_p != NULL) {
            strcpy(tmp_last_path, strtok_p);
            strtok_p = strtok(NULL, ".");
        }
        sprintf(enc_path, "%s_your_enc.%s", source_path, tmp_last_path);
    } else {
        sprintf(enc_path, "%s_your_enc", source_path);
    }

    // 打开文件
    FILE *source_fp = NULL;
    FILE *enc_fp = NULL;
    source_fp = fopen(source_path, "rb");
    if (source_fp == NULL) {
        perror("\n【打开待加密文件失败！】\n 原因：");
        return 0;
    }
    enc_fp = fopen(enc_path, "wb+");
    if (source_fp == NULL) {
        perror("\n【加密失败！】\n 原因：");
        return 0;
    }

    // 用当前时间做随机量，设计随机密钥、随机块大小
    long num_key = time(NULL);
    char key[100] = {0};
    sprintf(key, "%ld", num_key * 13 - 20200502);
    int key_lens = strlen(key);
    int size_key = num_key % 5 * 1024 + 1024; 

    // 边读边写
    while (1) {
        char tmp_source[6144] = {0};
        int read_size = fread(tmp_source, 1, size_key, source_fp);
        if (!read_size) {
            break;
        }
        int source_lens = strlen(tmp_source);
        for (int i = 0; i < source_lens; i++) {
            tmp_source[i] = tmp_source[i] ^ key[i % key_lens];
        }
        fwrite(tmp_source, 1, size_key, enc_fp);
    }
    fwrite(&num_key, 1, sizeof(num_key), enc_fp);

    // 关闭文件
    fclose(source_fp);
    fclose(enc_fp);
    return 0;
}

