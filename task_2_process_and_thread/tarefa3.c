#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    pid_t pid_avo, pid_pai, pid_filho, novo_pai;

    //processo do avô
    pid_avo = getpid();
    printf("Avô (PID=%d)\n", pid_avo);

    // processo do pai
    pid_pai = fork();

    if (pid_pai < 0) {
        //verifica se tem erro
        fprintf(stderr, "Erro ao criar processo do Pai\n");
        exit(1); // saída indicando falha
    } else if (pid_pai == 0) {
        // estamos no processo filho
        pid_filho = getpid();
        printf("Filho (PID=%d) do Pai (PID=%d)\n", pid_filho, getppid());
        exit(0); // saída indicando sucesso
    } else {
        // código executado pelo processo pai
        sleep(1); // Aguarda um pouco para garantir que o processo filho tenha iniciado
        printf("Pai (PID=%d) do filho (PID=%d)\n", getpid(), pid_pai);
        
        // simula "eliminação" do processo pai
        printf("Processo Pai eliminado.\n");

        // obtém o PID do novo pai do processo filho
        pid_t novo_pai = getppid(); // Obtém o PID do pai do processo pai (o avô)
        printf("Novo Pai do Filho (PID=%d)\n", novo_pai);
    }

    return 0;
}
