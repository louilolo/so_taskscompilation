#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

// Função para encontrar o tempo de espera para todos os processos
void waitingtime(int proc[], int n, int burst_time[], int wait_time[], int spawn_time[]) {
    int rem_time[n]; // Tempo restante para cada processo
    int current_time = 0;
    int complete = 0; // Indicador se todos os processos foram concluídos
    int menor = INT_MAX; // Inicializa com o maior valor possível de inteiro
    int shortest = -1; // Índice do processo com menor tempo restante

    for (int i = 0; i < n; i++) {
        rem_time[i] = burst_time[i]; // De início, os tempos restantes são os de execução
        wait_time[i] = 0; // Tempo de espera é zero no começo
    }

    // Enquanto todos os processos ainda não estiverem concluídos
    while (complete != n) {
        int process_found = 0;
        menor = INT_MAX;

        for (int i = 0; i < n; i++) {
            if (spawn_time[i] <= current_time && rem_time[i] > 0 && rem_time[i] < menor) {
                menor = rem_time[i];
                shortest = i;
                process_found = 1;
            }
        }

        // Se nenhum processo foi encontrado, incrementa o tempo atual e continua
        if (process_found == 0) {
            current_time++;
            continue;
        }

        // Reduz o tempo restante do processo com menor tempo
        rem_time[shortest]--;

        // Se o tempo do processo acabar, ele está completo
        if (rem_time[shortest] == 0) {
            complete++;
            wait_time[shortest] = current_time + 1 - burst_time[shortest] - spawn_time[shortest];
            if (wait_time[shortest] < 0) {
                wait_time[shortest] = 0;
            }
        }

        // Incrementa o tempo decorrido
        current_time++;
    }
}

// Função para calcular o tempo de resposta (turnaround time)
void turnaroundtime(int proc[], int n, int burst_time[], int wait_time[], int tat[]) {
    for (int i = 0; i < n; i++) {
        tat[i] = burst_time[i] + wait_time[i];
    }
}

// Função para calcular os tempos médios
void avgtime(int proc[], int n, int burst_time[], int spawn_time[]) {
    int wait_time[n], tat[n], total_wt = 0, total_tat = 0;

    // Chama para calcular o tempo de espera
    waitingtime(proc, n, burst_time, wait_time, spawn_time);
    
    // Chama para calcular o tempo de resposta
    turnaroundtime(proc, n, burst_time, wait_time, tat);

    printf("Processo  Tempo de Execução  Instante de Chegada  Tempo de Espera  Tempo de Resposta\n");

    for (int i = 0; i < n; i++) {
        total_wt += wait_time[i];
        total_tat += tat[i];
        printf("  %d\t\t%d\t\t%d\t\t%d\t\t%d\n", proc[i], burst_time[i], spawn_time[i], wait_time[i], tat[i]);
    }

    printf("Tempo médio de espera = %f\n", (float)total_wt / (float)n);
    printf("Tempo médio de resposta = %f\n", (float)total_tat / (float)n);
}

// Sorteia tempos de execução entre 5, 8 e 12
int sorteiaTempo() {
    int tempos[] = {5, 8, 12};
    return tempos[rand() % 3];
}

int main() {
    int n = 30; // Definindo 30 processos
    int proc[n], burst_time[n], spawn_time[n];

    for (int i = 0; i < n; i++) {
        proc[i] = i + 1;
        spawn_time[i] = i; // Simulação de chegada em tempos consecutivos
    }

    // Inicializa os tempos de execução para cada processo com números sorteados
    for (int i = 0; i < n; i++) {
        burst_time[i] = sorteiaTempo();
    }

    // Chama função para calcular tempos médios
    avgtime(proc, n, burst_time, spawn_time);
    
    return 0;
}
