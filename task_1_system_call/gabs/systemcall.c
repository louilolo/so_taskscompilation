#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

#define BUFFER_SIZE 4096

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Uso: %s <arquivo>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    char buffer[BUFFER_SIZE];
    int fd, blido, i, contagem_palavras = 0;
    char prev_char = ' ';
    
    fd = open(argv[1], O_RDONLY);
    if (fd == -1) {
        perror("Erro ao abrir o arquivo");
        exit(EXIT_FAILURE);
    }

    while ((blido = read(fd, buffer, BUFFER_SIZE)) > 0) {
        for (i = 0; i < blido; i++) {
            if ((buffer[i] == ' ' || buffer[i] == '\n' || buffer[i] == '\t') && prev_char != ' ') {
                contagem_palavras++;
            }
            prev_char = buffer[i];
        }
    }

    printf("O arquivo possui %d palavras.\n", contagem_palavras);

    close(fd);
    return 0;
}
