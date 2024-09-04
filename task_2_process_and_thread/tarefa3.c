#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    pid_t processo_avo, processo_pai, processo_filho, novo_pai;

    // Processo do avô
    processo_avo = getpid();
    printf("Avô (PID=%d)\n", processo_avo);

    // Cria o processo pai
    processo_pai = fork();

    if (processo_pai < 0) {
        // Verifica se houve erro ao criar o processo do Pai
        fprintf(stderr, "Erro ao criar processo do Pai\n");
        exit(1); // Saída indicando falha
    } else if (processo_pai == 0) {
        // Estamos no processo filho
        processo_filho = getpid();
        printf("Filho (PID=%d) do Pai (PID=%d)\n", processo_filho, getppid());
        exit(0); // Saída indicando sucesso
    } else {
        // Código executado pelo processo pai
        sleep(1); // Aguarda um pouco para garantir que o processo filho tenha iniciado

        // Espera o processo filho terminar
        waitpid(processo_pai, NULL, 0);

        // Imprime a mensagem do pai
        printf("Pai (PID=%d) do Filho (PID=%d)\n", getpid(), processo_pai);
        printf("Processo Pai eliminado.\n");

        // Adiciona um novo sleep para garantir que o processo filho tenha sido adotado pelo avô
        sleep(1);

        // Obtém o PID do novo pai do processo filho
        novo_pai = getppid(); // Obtém o PID do pai do processo pai (o avô)
        printf("Novo Pai do Filho (PID=%d)\n", novo_pai);
    }

    return 0;
}
