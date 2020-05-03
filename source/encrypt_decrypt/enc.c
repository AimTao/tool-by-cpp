#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int main(int argc, char **argv) {

    // 获取待加密文件路径
    char *source_path = argv[1];
    char backup_source_path[512] = {0};
    strcpy(backup_source_path, source_path);

    // 打开读文件，检查路径
    FILE *source_fp = NULL;
    source_fp = fopen(source_path, "rb");
    if (source_fp == NULL) {
        perror("\n【打开待加密文件失败！】\n 原因：");
        return 0;
    }
    
    // 生成已加密文件路径
    char enc_path[512] = {0};
    char last_name[100] = {0};    // 获取文件后缀名
    char file_name[100] = {0};   // 获取文件名（省去后缀名）
    char *strtok_p = strtok(backup_source_path, ".");
    strtok_p = strtok(NULL, ".");
    if (strtok_p != NULL) {
        while (strtok_p != NULL) {
            strcpy(last_name, strtok_p);
            strtok_p = strtok(NULL, ".");
        }
        char *last_path_ptr = NULL;
        char *source_path_ptr = source_path;
        while (1) {
            last_path_ptr = strstr(source_path_ptr, last_name);
            if (last_path_ptr == NULL) {
                source_path_ptr -= strlen(last_name);
                break;
            } else {
                source_path_ptr = last_path_ptr + strlen(last_name);
                if (source_path_ptr > source_path + strlen(source_path)) {
                    break;
                }
            }
        }
        strncpy(file_name, source_path, source_path_ptr - 1 - source_path);
        sprintf(enc_path, "%s_enc.%s", file_name, last_name);
    } else {
        sprintf(enc_path, "%s_enc", source_path);
    }

    // 打开写文件
    FILE *enc_fp = NULL;
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
    // 写入解密密钥
    fwrite(&num_key, 1, sizeof(num_key), enc_fp);
    
    // 边读边写，加密
    while (1) {
        char tmp_source[6144] = {0};    // 1024 * 5
        int read_size = fread(tmp_source, 1, size_key, source_fp);
        if (!read_size) {
            break;
        }
        for (int i = 0; i < read_size; i++) {
            tmp_source[i] = tmp_source[i] ^ key[i % key_lens];
        }
        fwrite(tmp_source, 1, read_size, enc_fp);
    }
    printf("\n加密已完成！加密文件为于 %s\n\n", enc_path);

    // 关闭文件
    fclose(source_fp);
    fclose(enc_fp);

    return 0;
}

