#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

// Variável global 
int var_comp = 1;

int main() {
    printf("Valor inicial da variavel no processo pai = %d\n", var_comp);

    pid_t pid = fork();  

    if (pid < 0) { 
        perror("Erro: ");
        exit(1);
    } else if (pid == 0) { // processo filho
        var_comp = 5; 
        printf("Valor da variavel alterada pelo processo filho = %d\n", var_comp);
        exit(0);  
    } else {  // codigo do pai
        waitpid(pid, NULL, 0);  
        printf("Valor da variavel após ser alterada no processo filho = %d\n", var_comp);
    }

    return 0;
}
