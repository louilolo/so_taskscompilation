#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

#define SIMULATIONS 20

double average_time(double (*func)(), int simulations) {
    double total = 0;
    for (int i = 0; i < simulations; i++) {
        total += func();
    }
    return total / simulations;
}

int main() {
    srand(time(NULL));

    printf("Iniciando simulações...\n");

    double fork_time = average_time(measure_fork, SIMULATIONS);
    double threads_time = average_time(measure_threads, SIMULATIONS);

    printf("Média de tempo usando fork: %.2f microssegundos\n", fork_time);
    printf("Média de tempo usando threads: %.2f microssegundos\n", threads_time);

    return 0;
}
