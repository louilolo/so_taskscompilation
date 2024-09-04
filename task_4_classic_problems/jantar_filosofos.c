#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>
#include <unistd.h>  // Para usar usleep()

#define N 5  // Número de filósofos

#define LEFT (i+N-1)%N  // Índice do vizinho à esquerda
#define RIGHT (i+1)%N   // Índice do vizinho à direita

#define THINKING 0  // Estado do filósofo pensando
#define HUNGRY 1    // Estado do filósofo com fome
#define EATING 2    // Estado do filósofo comendo

int estado[N];  // Arranjo para controlar o estado de cada filósofo
sem_t mutex;   // Exclusão mútua para as regiões críticas
sem_t s[N];    // Um semáforo por filósofo

void think(int i) {
    printf("Filósofo %d está pensando.\n", i);
    usleep(rand() % 500000);  // Atraso aleatório entre 0 e 0.5 segundos
}

void eat(int i) {
    printf("Filósofo %d está comendo.\n", i);
    usleep(rand() % 500000);  // Atraso aleatório entre 0 e 0.5 segundos
}

void test(int i) {
    if (estado[i] == HUNGRY && estado[LEFT] != EATING && estado[RIGHT] != EATING) {
        estado[i] = EATING;
        sem_post(&s[i]);  // Libera o semáforo do filósofo
    }
}

void take_forks(int i) {
    sem_wait(&mutex);       // Entra na região crítica
    estado[i] = HUNGRY;    // Registra que o filósofo está faminto
    test(i);               // Tenta pegar dois garfos
    sem_post(&mutex);      // Sai da região crítica

    sem_wait(&s[i]);       // Bloqueia se os garfos não foram pegos

    // Se não conseguir pegar o segundo garfo
    if (estado[i] != EATING) {
        printf("Filósofo %d não conseguiu pegar ambos os garfos. Devolvendo o garfo e aguardando...\n", i);
        
        sem_wait(&mutex);   // Entra na região crítica novamente
        estado[i] = THINKING;  // Devolve o garfo (volta ao estado pensando)
        test(LEFT);         // Libera os garfos para o vizinho da esquerda, se puder
        test(RIGHT);        // Libera os garfos para o vizinho da direita, se puder
        sem_post(&mutex);   // Sai da região crítica

        // Aguarda por um tempo aleatório
        usleep(rand() % 1000000);  // Aguarda por um tempo aleatório (até 1 segundo)
    }
}

void put_forks(int i) {
    sem_wait(&mutex);       // Entra na região crítica
    estado[i] = THINKING;  // O filósofo acabou de comer
    test(LEFT);            // Vê se o vizinho da esquerda pode comer agora
    test(RIGHT);           // Vê se o vizinho da direita pode comer agora
    sem_post(&mutex);      // Sai da região crítica
}

void* philosopher(void* num) {
    int i = *(int*)num;
    while (1) {  // Repete para sempre
        think(i);        // O filósofo está pensando
        take_forks(i);   // Tenta pegar dois garfos ou bloqueia
        eat(i);          // Hummm, espaguete!
        put_forks(i);    // Devolve os dois garfos à mesa
    }
}

int main() {
    pthread_t thread_id[N];
    int phil[N];
    
    // Inicializa os semáforos
    sem_init(&mutex, 0, 1);
    for (int i = 0; i < N; i++) {
        sem_init(&s[i], 0, 0);
        phil[i] = i;  // Define o número do filósofo
    }
    
    // Cria as threads dos filósofos
    for (int i = 0; i < N; i++) {
        pthread_create(&thread_id[i], NULL, philosopher, &phil[i]);
    }
    
    // Junta as threads (espera que todas terminem)
    for (int i = 0; i < N; i++) {
        pthread_join(thread_id[i], NULL);
    }
    
    return 0;
}
