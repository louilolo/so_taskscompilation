#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main (int argc, char *argv[]) {
    if (argc != 2) {
        printf("Uso: %s <arquivo>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    char palavra[50], caractere[2];
    char* arquivo;
    int bytes, fd, contador, erro=0, ocorrencias;

    //pede e processa o cunjunto de caracteres a ser identificado 
    char msg1[] = "digite a palavra a ser identificada: ";
    write(STDOUT_FILENO, msg1, sizeof(msg1)-1);

    bytes = read(STDIN_FILENO, palavra, sizeof(palavra));
    if (bytes<=0) {
        perror("erro ao ler palavra");
        exit(1);
    }

    //abrindo o arquivo identificado no comando
    fd = open(argv[1], O_RDONLY);

    if(fd==-1){
        perror("erro ao abrir arquivo");
        exit(1);
    }

    //faz a comparação que encontra tanto palavras quanto partes de outras palavras
    while(read(fd, caractere, sizeof(char))>0){
        if(caractere[0]!=' '&&caractere[0]!='\0'&&caractere[0]!='\n'&&caractere[0]!='\t'){
            if(caractere[0]==palavra[contador]){
                contador++;
            }
            else{
                erro++;
            }
        }
        else{
            contador = 0;
            if(erro==0){
                ocorrencias++;
            }
            erro = 0;
        }
    }

    close(fd);

    
    char msg3[] = "numero de ocorrencias da palavra solicitada = ";
    write(STDERR_FILENO, msg3, sizeof(msg3)-1);
    printf("%d\n", ocorrencias);


    return 0;
}