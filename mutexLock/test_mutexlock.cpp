/*************************************************************************
 *   @file : test_mutexlock.cpp
 *   @date : 2018-05-21
 *   @author : jiayunwei 
 ************************************************************************/
#include "mutexlock.h"
#include <unistd.h>
#include <iostream>

#define    NUM_THREADS     10000

int num=0;
Mutex mutex;

//void *count(void *args) {
void *count(void* /* args */) {

//    (void)args; // 显式声明未使用参数args，避免编译器警告
    MutexLock lock(&mutex);
    num++;
    return nullptr;
}


int main() {
    int t;
    pthread_t thread[NUM_THREADS];

    for( t = 0; t < NUM_THREADS; t++) {   
        int ret = pthread_create(&thread[t], NULL, count, NULL);
        if(ret) {   
            return -1;
        }   
    }

    for( t = 0; t < NUM_THREADS; t++)
        pthread_join(thread[t], NULL);
    std::cout << num << std::endl;
    return 0;
}
