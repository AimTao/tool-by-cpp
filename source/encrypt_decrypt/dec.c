#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {

    // 读入待解密文件路径
    char enc_path[512] = {0};
    char backup_enc_path[512] = {0};
    printf("请输入待解密文件路径（例如: ../enc/hello.jpg）：");
    scanf("%s", enc_path);
    strcpy(backup_enc_path, enc_path);


    // 生成解密文件路径
    char dec_path[512] = {0};
    char tmp_last_path[100] = {0};
    char *strtok_p = NULL;
    strtok_p = strtok(backup_enc_path, ".");
    if (strtok_p != NULL) {
        while (strtok_p != NULL) {
            strcpy(tmp_last_path, strtok_p);
            strtok_p = strtok(NULL, ".");
        }
        sprintf(dec_path, "%s_your_dec.%s", enc_path, tmp_last_path);
    } else {
        sprintf(dec_path, "%s_your_dec", enc_path);
    }

    // 打开文件
    FILE *enc_fp = NULL;
    FILE *dec_fp = NULL;
    enc_fp = fopen(enc_path, "rb+");
    if (enc_fp == NULL) {
        perror("\n【打开待解密文件失败！】\n 原因：");
        return 0;
    }
    dec_fp = fopen(dec_path, "wb+");
    if (dec_fp == NULL) {
        perror("\n【解密失败！\n 原因：");
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

    // 关闭文件
    fclose(enc_fp);
    fclose(dec_fp);
    
    return 0;
}