#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

char MenuShow();
int TestOrder(char order);
void Enc();
void Dec();

// 菜单
char MenuShow() {
    printf("\n");
    printf("============ 功能选择 ===========\n");
    printf("=            E  加密            =\n");
    printf("=            D  解密            =\n");
    printf("=            C  清屏            =\n");
    printf("=            Q  退出            =\n");
    printf("=================================\n\n");
    printf("请输入指令所对应的字母：");
    char order;
    scanf("%c", &order);
    char more_char[100] = {0};
    fgets(more_char, 100, stdin); 
    if (strlen(more_char) != 1) {
        order = 'N';
    }
    return order;
}

// 识别指令
int TestOrder(char order) {
    switch (order) {
        case 'E' :
        case 'e' :
        case '1' :
            Enc();
            break;
        case 'D' :
        case 'd' :
        case '2' :
            Dec();
            break;
        case 'C' :
        case 'c' :
        case '3' :
            system("clear");
            break;
        case 'Q' :
        case 'q' :
        case '4' :
            return -1;       
        default:
            printf("\n\n【Error】输入指令有误！\n");
            char tmp_order = MenuShow();
            TestOrder(tmp_order);
            break;
    }
    return 0;
}

// 加密
void Enc() {
   // 获取待加密文件路径
    char source_path[512] = {0};
    char backup_source_path[512] = {0};
    printf("请输入待加密文件路径（例如: ../enc/hello.jpg）：");
    scanf("%s", source_path);
    getchar();
    strcpy(backup_source_path, source_path);

    // 打开读文件，检查路径
    FILE *source_fp = NULL;
    source_fp = fopen(source_path, "rb");
    if (source_fp == NULL) {
        perror("\n【打开待加密文件失败！】\n 原因：");
        return;
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
        return;
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
    printf("\n\n加密已完成！加密文件为于 %s\n\n", enc_path);

    // 关闭文件
    fclose(source_fp);
    fclose(enc_fp);

    return;
}

// 解密
void Dec() {
    // 读入待解密文件路径
    char enc_path[512] = {0};
    char backup_enc_path[512] = {0};
    printf("请输入待解密文件路径（例如: ../enc/hello.jpg）：");
    scanf("%s", enc_path);
    getchar();
    strcpy(backup_enc_path, enc_path);

    // 打开读文件
    FILE *enc_fp = NULL;
    enc_fp = fopen(enc_path, "rb+");
    if (enc_fp == NULL) {
        perror("\n【打开待解密文件失败！】\n 原因：");
        return;
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
        perror("\n【解密失败！\n 原因：");
        return;
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
    printf("\n\n解密已完成！解密文件为于 %s\n\n", dec_path);

    // 关闭文件
    fclose(enc_fp);
    fclose(dec_fp);
    
    return;
}

int main(int argc, char ** argv) {
    int state = 0;
    while (state != -1) {
        char order = MenuShow();
        state = TestOrder(order);
    }
    if (state == -1) {
        printf("\n");
        printf("============ 程序已结束 ==========\n");
        printf("=                                =\n");
        printf("=             欢迎访问           =\n");
        printf("=          www.aimtao.net        =\n");
        printf("==================================\n\n");
        return 0;
    }
    return 0;  
}
