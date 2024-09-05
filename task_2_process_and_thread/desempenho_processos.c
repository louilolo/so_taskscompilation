#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>
#include <sys/wait.h>

#define SIZE 1000000

void init_array(int *arr, int size) {
    for (int i = 0; i < size; i++) {
        arr[i] = rand() % 100;
    }
}

int sum_array(int *arr, int size) {
    int sum = 0;
    for (int i = 0; i < size; i++) {
        sum += arr[i];
    }
    return sum;
}

double measure_fork() {
    int arr[SIZE];
    init_array(arr, SIZE);

    struct timeval start, end;
    gettimeofday(&start, NULL);

    pid_t pid = fork();
    if (pid == 0) {  // Processo filho
        int child_sum = sum_array(arr, SIZE);
        printf("Soma no processo filho: %d\n", child_sum);
        exit(0);
    } else if (pid > 0) {  // Processo pai
        wait(NULL);  // Espera o processo filho terminar
        int parent_sum = sum_array(arr, SIZE);
        gettimeofday(&end, NULL);
        printf("Soma no processo pai: %d\n", parent_sum);
    } else {
        perror("fork falhou");
        exit(1);
    }

    return (end.tv_sec - start.tv_sec) * 1000000 + (end.tv_usec - start.tv_usec);
}
