#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NUM_PROCESSES 30  // Define o número de processos

// Função para calcular o tempo de espera de todos os processos usando Round Robin
void waitingTimeRR(int burst_time[], int n, int time_slice, int wait_time[]) {
    int remaining_burst[n];  // Array para armazenar o tempo de burst restante para cada processo
    int time = 0;  // Tempo total passado até agora

    // Inicializa o tempo restante e o tempo de espera de todos os processos
    for (int i = 0; i < n; i++) {
        remaining_burst[i] = burst_time[i];
        wait_time[i] = 0;
    }

    int processes_remaining = n;  // Contador de processos restantes

    // Loop para processar todos os processos até que todos sejam concluídos
    while (processes_remaining > 0) {
        for (int i = 0; i < n; i++) {
            if (remaining_burst[i] > 0) {  // Se o processo ainda tem tempo de burst restante
                if (remaining_burst[i] > time_slice) {
                    time += time_slice;  // Avança o tempo pelo tamanho do time-slice
                    remaining_burst[i] -= time_slice;  // Reduz o tempo de burst restante
                } else {
                    time += remaining_burst[i];  // Avança o tempo pelo tempo restante do burst
                    wait_time[i] = time - burst_time[i];  // Calcula o tempo de espera
                    remaining_burst[i] = 0;  // Marca o processo como concluído
                    processes_remaining--;  // Decrementa o número de processos restantes
                }
            }
        }
    }
}

// Função para calcular o tempo de turnaround (tempo total) para todos os processos
void turnaroundTime(int n, int burst_time[], int wait_time[], int tat[]) {
    for (int i = 0; i < n; i++) {
        tat[i] = burst_time[i] + wait_time[i];  // Tempo de turnaround é a soma do tempo de burst e do tempo de espera
    }
}

// Função para calcular e imprimir os tempos médios de espera e turnaround
void avgTime(int n, int burst_time[], int time_slice) {
    int wait_time[n], tat[n];  // Arrays para armazenar os tempos de espera e turnaround
    int total_wt = 0, total_tat = 0;  // Somas dos tempos de espera e turnaround

    // Calcula os tempos de espera usando Round Robin
    waitingTimeRR(burst_time, n, time_slice, wait_time);
    // Calcula os tempos de turnaround
    turnaroundTime(n, burst_time, wait_time, tat);

    // Imprime a tabela com os detalhes dos processos
    printf("Processos  Burst   Espera   Turnaround \n");
    for (int i = 0; i < n; i++) {
        total_wt += wait_time[i];  // Acumula o tempo total de espera
        total_tat += tat[i];  // Acumula o tempo total de turnaround
        printf(" %d\t  %d\t\t %d \t%d\n", i + 1, burst_time[i], wait_time[i], tat[i]);
    }

    // Calcula e imprime os tempos médios de espera e turnaround
    printf("Tempo médio de espera = %f\n", (float)total_wt / (float)n);
    printf("Tempo médio de turnaround = %f\n", (float)total_tat / (float)n);
}

// Função principal
int main() {
    int burst_time[NUM_PROCESSES];  // Array para armazenar os tempos de burst dos processos
    int time_slice = 4;  // Tamanho do time-slice para o escalonador Round Robin

    // Semente para o gerador de números aleatórios
    srand(time(NULL));

    // Gera tempos de burst aleatórios entre 5, 8 e 12
    for (int i = 0; i < NUM_PROCESSES; i++) {
        int rand_num = rand() % 3;  // Gera um número aleatório entre 0 e 2
        if (rand_num == 0) burst_time[i] = 5;
        else if (rand_num == 1) burst_time[i] = 8;
        else burst_time[i] = 12;
    }

    // Calcula e imprime os tempos médios de espera e turnaround
    avgTime(NUM_PROCESSES, burst_time, time_slice);

    return 0;
}
