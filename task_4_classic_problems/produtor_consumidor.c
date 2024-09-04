#include "stdio.h"
#include "stdlib.h"
#include "unistd.h"

#define READ 0
#define WRITE 1
#define TRUE 1

/* protótipos */
void cria_item(int i);
void consome_item(int i);
void produtor(int fd[2], int qtde_itens);
void consumidor(int fd[2]);

int main (){
int fd[2];

/* criando pipe */
pipe (fd);

/* criando novo processo */
int pid = fork();

if (pid == -1) {
perror("Erro ao criar um novo processo!");
} else if (pid == 0) {
/* o novo processo funciona como produtor */
produtor(fd, 15);
} else {
/* o processo pai funciona como consumidor */
consumidor(fd);
}

return 0;
}

void produtor(int fd[2], int qtde_itens) {
close(fd[READ]);

int i, bytesEscritos;
for (i = 1 ; i <= qtde_itens; i++) {
sleep( rand() % 5 );
cria_item(i);

/* escreve no pipe */
bytesEscritos = write(fd[WRITE], &i, sizeof(int));

if (bytesEscritos == -1) {
   perror("Erro de escrita no pipe!");
}
}
close (fd[WRITE]);
}


void consumidor(int fd[2]){
close (fd[WRITE]);

int i, bytesLidos;
while (TRUE) {
/* lê do pipe */
bytesLidos = read (fd[READ], &i, sizeof(int));
sleep( rand() % 5 );
consome_item(i);

if (bytesLidos == -1) {
   perror("Erro de leitura no pipe!");
} else if (bytesLidos == 0) {
   break;
}
}
close (fd[READ]);
}

void cria_item(int i){
printf("Produtor criou o %d.o item.\n", i);
}

void consome_item(int i){
printf("Consumidor consumiu o %d.o item.\n", i);
}
