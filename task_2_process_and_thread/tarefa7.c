#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/wait.h>

#define LIMITE_PROCESSO 1000  // Ajuste conforme necessário
#define LIMITE_THREAD 1000    // Ajuste conforme necessário

void* funcao_thread(void* arg) {
    pthread_exit(NULL);
}

int main() {
    // Teste de limites para processos
    printf("Teste do limite de criacao dos Processos:\n");

    int i, pid;

    for (i = 1; i <= LIMITE_PROCESSO; i++) {
        pid = fork();
        if (pid < 0) {
            printf("Limite de Processos excedido: %d\n", i - 1);
            break;
        }
        if (pid == 0) {
            exit(0);  // Filho sai imediatamente
        }
    }

    if (pid > 0) {
        for (int j = 0; j < i - 1; j++) {
            wait(NULL);  // Pai espera todos os filhos
        }
        printf("Teste processos concluido\n");
    }

    // Teste de limites para threads
    printf("\nTeste do limite de criacao de Threads:\n");

    pthread_t thread;
    for (int i = 1; i <= LIMITE_THREAD; i++) {
        if (pthread_create(&thread, NULL, funcao_thread, NULL) != 0) {
            printf("Limite de Threads excedido: %d\n", i - 1);
            break;
        }
        pthread_detach(thread);  // Evita que o pai precise esperar as threads
    }

    printf("Teste threads concluido\n");

    return 0;
}