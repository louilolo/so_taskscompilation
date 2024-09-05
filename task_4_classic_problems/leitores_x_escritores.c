#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>

#define NUM_THREADS 5
#define NUM_ECRIT 4

sem_t troca;
sem_t mutex;
int leitores_ativos = 0;

pthread_t threads[NUM_THREADS];
int thread_ids[NUM_THREADS]; 
pthread_t escritores[NUM_ECRIT];
int ecrit_ids[NUM_ECRIT]; 

void* leitura(void* arg) {
    int id = *(int*)arg;

    sem_wait(&mutex);
    leitores_ativos++;
    if (leitores_ativos == 1) {
        sem_wait(&troca);
    }
    sem_post(&mutex);

    printf("O leitor %d está lendo\n", id);

    sem_wait(&mutex);
    leitores_ativos--;
    if (leitores_ativos == 0) {
        sem_post(&troca);
    }
    sem_post(&mutex);

    return NULL;
}

void* escrita(void* arg) {
    int id = *(int*)arg;

    printf("O escritor %d quer escrever\n", id);
    sem_wait(&troca);
    printf("O escritor %d está escrevendo\n", id);
    sem_post(&troca);

    return NULL;
}

int main() {
    sem_init(&troca, 0, 1);
    sem_init(&mutex, 0, 1);

    for (int i = 0; i < NUM_ECRIT; i++) {
        ecrit_ids[i] = i + 1;  
        pthread_create(&escritores[i], NULL, escrita, &ecrit_ids[i]);
    }

    for (int i = 0; i < NUM_THREADS; i++) {
        thread_ids[i] = i + 1;  
        pthread_create(&threads[i], NULL, leitura, &thread_ids[i]);
    }

    for (int i = 0; i < NUM_ECRIT; i++) {
        pthread_join(escritores[i], NULL);
    }

    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    sem_destroy(&troca);
    sem_destroy(&mutex);

    return 0;
}
