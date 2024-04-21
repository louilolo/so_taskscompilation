#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main (){
    char palavra[50], caractere;
    char* arquivo;
    int bytes, fd, tamanhopalavra, contador, letraigual=0, ocorrencias;

    char msg1[] = "digite a palavra a ser identificada";
    write(STDOUT_FILENO, msg1, sizeof(msg1)-1);

    bytes = read(STDIN_FILENO, palavra, sizeof(palavra));
    if (bytes<=0) {
        perror("erro ao ler palavra");
        exit(1);
    }
    tamanhopalavra = bytes-1;

    char msg2[] = "digite o caminho do arquivo que voce quer checar: ";
    write(STDOUT_FILENO, msg2, sizeof(msg2)-1);
    bytes = read(STDIN_FILENO, arquivo, sizeof(arquivo));
    if (bytes<=0) {
        perror("erro ao ler nome do arquivo");
        exit(1);
    }

    fd = open(arquivo, O_RDONLY);

    if(fd==-1){
        perror("erro ao abrir arquivo");
        exit(1);
    }
    while(read(arquivo, caractere, sizeof(char))!=-1){
        if(caractere!=' '&&caractere!='\0'&&caractere!='\n'&&caractere!='\t'){
            if(caractere==palavra[contador]){
                letraigual++;
                contador++;
            }
        }
        else{
            contador = 0;
            if(letraigual==tamanhopalavra){
                ocorrencias++;
            }
            letraigual = 0;
        }
    }

    close(arquivo);

    char msg3[] = "numero de ocorrencias da palavra solicitada = " + itoa(ocorrencias);
    write(STDERR_FILENO, msg3, sizeof(msg3)-1);


    return 0;
}