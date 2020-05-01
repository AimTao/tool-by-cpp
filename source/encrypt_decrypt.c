#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

}

// 解密
void Dec() {
    
}

int main(int argc, char ** argv) {
    char order = MenuShow();
    int state = TestOrder(order);
    if (state == -1) {
        printf("\n");
        printf("============ 程序已结束 ==========\n");
        printf("=                                =\n");
        printf("=             欢迎访问           =\n");
        printf("=          www.aimtao.net        =\n");
        printf("==================================\n\n");
        return 0;
    }
    
}
