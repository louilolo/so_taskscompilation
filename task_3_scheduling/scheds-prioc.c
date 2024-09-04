#include <stdio.h>

// Function to find the waiting time for all processes
int waitingtime(int proc[], int n, int burst_time[], int wait_time[], int priority[]) {
    int i, j, temp;
    // Ordena os processos com base na prioridade (menor valor de prioridade executa primeiro)
    for (i = 0; i < n - 1; i++) {
        for (j = i + 1; j < n; j++) {
            if (priority[i] > priority[j]) {
                // Troca prioridades
                temp = priority[i];
                priority[i] = priority[j];
                priority[j] = temp;
                // Troca tempos de burst
                temp = burst_time[i];
                burst_time[i] = burst_time[j];
                burst_time[j] = temp;
                // Troca IDs de processos
                temp = proc[i];
                proc[i] = proc[j];
                proc[j] = temp;
            }
        }
    }
    // Tempo de espera do primeiro processo é 0
    wait_time[0] = 0;

    // Calcula o tempo de espera para cada processo
    for (i = 1; i < n; i++) {
        wait_time[i] = burst_time[i - 1] + wait_time[i - 1];
    }
    return 0;
}

int turnaroundtime( int proc[], int n,
int burst_time[], int wait_time[], int tat[]) {
   // calculating turnaround time by adding
   // burst_time[i] + wait_time[i]
   int i;
   for ( i = 0; i < n ; i++)
   tat[i] = burst_time[i] + wait_time[i];
   return 0;
}

// Function to calculate average time
int avgtime(int proc[], int n, int burst_time[], int priority[]) {
    int wait_time[n], tat[n], total_wt = 0, total_tat = 0;
    int i;
    //Function to find waiting time of all processes
    waitingtime(proc, n, burst_time, wait_time, priority);
    //Function to find turn around time for all processes
    turnaroundtime(proc, n, burst_time, wait_time, tat);
    //Display processes along with all details
    printf("Processos  Burst  Waiting  Turn around  Prioridade\n");
    // Calculate total waiting time and total turn
    // around time
    for (i = 0; i < n; i++) {
        total_wt += wait_time[i];
        total_tat += tat[i];
        printf("  %d\t\t%d\t%d\t  %d\t  %d\n", proc[i], burst_time[i], wait_time[i], tat[i], priority[i]);
    }

    printf("Average waiting time = %f\n", (float)total_wt / (float)n);
    printf("Average turn around time = %f\n", (float)total_tat / (float)n);
    return 0;
}

// Main function
int main() {
    //process id's
    int proc[] = {1, 2, 3};
    int n = sizeof proc / sizeof proc[0];
    //Burst time of all processes
    int burst_time[] = {10, 5, 8};

    // Prioridade de cada processo (quanto menor o número, maior a prioridade)
    int priority[] = {1, 3, 2};

    avgtime(proc, n, burst_time, priority);
    return 0;
}
