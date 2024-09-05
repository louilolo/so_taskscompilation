#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

pthread_mutex_t lock;
pthread_cond_t cond;
int turn = 0;

void* printA(void* arg){
    pthread_mutex_lock(&lock);
    while(turn != 0){
        pthread_cond_wait(&cond, &lock);
    }
    printf("A");
    turn = 1;
    pthread_cond_signal(&cond);
    pthread_mutex_unlock(&lock);
    return NULL;
}

void* printB(void* arg){
    pthread_mutex_lock(&lock);
    while(turn != 1){
        pthread_cond_wait(&cond, &lock);
    }
    printf("B");
    turn = 2;
    pthread_cond_signal(&cond);
    pthread_mutex_unlock(&lock);
    return NULL;
}

void* printC(void* arg){
    pthread_mutex_lock(&lock);
    while(turn!=2){
        pthread_cond_wait(&cond, &lock);
    }
    printf("C\n");
    turn = 0;
    pthread_cond_signal(&cond);
    pthread_mutex_unlock(&lock);
    return NULL;
}
int main(){
    pthread_t thread_A, thread_B, thread_C;
    pthread_mutex_init(&lock, NULL);
    pthread_cond_init(&cond, NULL);
   
    for (int i = 0; i < 10; i++){
        pthread_create(&thread_A, NULL, printA, NULL);
        pthread_create(&thread_B, NULL, printB, NULL);
        pthread_create(&thread_C, NULL, printC, NULL);
       
        pthread_join(thread_A, NULL);
        pthread_join(thread_B, NULL);
        pthread_join(thread_C, NULL);
    }
    pthread_mutex_destroy(&lock);
        pthread_cond_destroy(&cond);
        return 0;
}
