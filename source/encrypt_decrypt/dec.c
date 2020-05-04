#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv) {

    // 读入待解密文件路径
    char *enc_path = argv[1];
    char backup_enc_path[512] = {0};
    strcpy(backup_enc_path, enc_path);

    // 打开读文件，检查路径
    FILE *enc_fp = NULL;
    enc_fp = fopen(enc_path, "rb+");
    if (enc_fp == NULL) {
        perror("\n【打开待解密文件失败！】\n 原因：");
        return 0;
    }

    // 生成解密文件路径
    char dec_path[512] = {0};
    char last_name[100] = {0};    // 获取文件后缀名
    char file_name[100] = {0};   // 获取文件名（省去后缀名）
    char *strtok_p = NULL;
    strtok_p = strtok(backup_enc_path, ".");
    strtok_p = strtok(NULL, ".");
    if (strtok_p != NULL) {
        while (strtok_p != NULL) {
            strcpy(last_name, strtok_p);
            strtok_p = strtok(NULL, ".");
        }
        char *last_path_ptr = NULL;
        char *enc_path_ptr = enc_path;
        while (1) {
            last_path_ptr = strstr(enc_path_ptr, last_name);
            if (last_path_ptr == NULL) {
                enc_path_ptr -= strlen(last_name);
                break;
            } else {
                enc_path_ptr = last_path_ptr + strlen(last_name);
                if (enc_path_ptr > enc_path + strlen(enc_path)) {
                    break;
                }
            }
        }
        strncpy(file_name, enc_path, enc_path_ptr - 1 - enc_path);
        sprintf(dec_path, "%s_dec.%s", file_name, last_name);
    } else {
        sprintf(dec_path, "%s_dec", enc_path);
    }

    // 打开写文件
    FILE *dec_fp = NULL;
    dec_fp = fopen(dec_path, "wb+");
    if (dec_fp == NULL) {
        perror("\n【解密失败！】\n 原因：");
        return 0;
    }

    // 读取密钥
    long num_key = 0;
    fread(&num_key, 1, sizeof(num_key), enc_fp);
    char key[100] = {0};
    sprintf(key, "%ld", num_key * 13 - 20200502);
    int key_lens = strlen(key);
    int size_key = num_key % 5 * 1024 + 1024;
    
    // 边读边写，解密
    while (1) {
        char tmp_enc[6144] = {0};      // 1024 * 5
        int read_size = fread(tmp_enc, 1, size_key, enc_fp);
        if (!read_size) {
            break;
        }
        for (int i = 0; i < read_size; i++) {
            tmp_enc[i] = tmp_enc[i] ^ key[i % key_lens];
        }
        fwrite(tmp_enc, 1, read_size, dec_fp);
    }
    printf("\n\n解密已完成！解密文件位于 %s\n\n", dec_path);

    // 关闭文件
    fclose(enc_fp);
    fclose(dec_fp);
    
    return 0;
}