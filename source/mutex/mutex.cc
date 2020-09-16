#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <vector>

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

int key = 0;

// 临界资源
int nums = 0;

// 生产者
void *producer(void*) {
    int times = 10000000;
    if (key == 1) {
        while(times--) {
            pthread_mutex_lock(&mutex);
            nums ++;
            pthread_mutex_unlock(&mutex);
        }
    } else if (key == 0) {
        while(times--) {
            nums ++;
        }
    }
}

// 消费者
void *comsumer(void*) {
    int times = 10000000;
    if (key == 1) {
        while(times--) {
            pthread_mutex_lock(&mutex);
            nums --;
            pthread_mutex_unlock(&mutex);
        }
    } else if (key == 0) {
        while(times--) {
            nums --;
        }
    }
}

int main() {
    printf("================= option =================\n");
    printf("Add mutex, please input 1\n");
    printf("Don't add mutex, please input 0\n");
    printf("==========================================\n\n");
    printf("Please input your option: ");
    scanf("%d", &key);
    if (key != 0 && key != 1) {
        printf("Input error, please input 1 or 0\n");
        return 0;
    }
    printf("Start in main function: num.\n");
    pthread_t thread1, thread2;
    pthread_create( &thread1, NULL, &producer, NULL );
    pthread_create( &thread2, NULL, &comsumer, NULL );
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
    printf("Print in main function: num = %d", nums);
    return 0;
}