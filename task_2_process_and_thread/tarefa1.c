#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    int pid_pai, pid_filho;

    printf("Sou o avô: %5d\n", getpid()); // processo avô

    pid_pai = fork();

    if (pid_pai < 0) { 
        perror("Erro: ");
        exit(1);
    } else if (pid_pai == 0) {  // processo pai
        printf("Sou o pai: %5d, filho de %d\n", getpid(), getppid());

        pid_filho = fork();

        if (pid_filho < 0) { 
            perror("Erro ao criar o filho");
            exit(1);
        } else if (pid_filho == 0) { // processo filho
            printf("Sou o filho: %5d, filho de %d\n", getpid(), getppid());
            sleep(5);  
            printf("bonne nuit: %5d.\n", getpid());
        } else {  
            wait(NULL);
            printf("bonne nuit: %5d.\n", getpid());
        }

    } else {
        wait(NULL);
        printf("bonne nuit: %5d.\n", getpid());
    }

    return 0;
}
