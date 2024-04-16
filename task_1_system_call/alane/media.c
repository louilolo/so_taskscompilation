#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
    int n1, n2;
    float media;
    int bytes_lidos;
    char buffer[10];
    char media_str[10];

    //exibe a mensagem para o 1º numero
    char msg1[] = "Digite o primeiro numero: \n";
    write(1, msg1, sizeof(msg1) - 1);

    //ler o primeiro numero
    bytes_lidos = read(0, buffer, sizeof(buffer));
    if (bytes_lidos <= 0) {
        perror("Erro ao ler dados");
        exit(1);
    }
    buffer[bytes_lidos] = '\0'; // Termina a string lida
    n1 = atoi(buffer);

    //exibe a mensagem para o 2º numero
    char msg2[] = "Digite o segundo numero: \n";
    write(1, msg2, sizeof(msg2) - 1);

    bytes_lidos = read(0, buffer, sizeof(buffer));
    if (bytes_lidos <= 0) {
        perror("Erro ao ler dados");
        exit(1);
    }
    buffer[bytes_lidos] = '\0'; // Termina a string lida
    n2 = atoi(buffer);

    media = ((float)n1 + (float)n2) / 2.0;

    snprintf(media_str, sizeof(media_str), "%.2f\n", media);

    //exibe a mensagem para a media
    char msg3[] = "A media é ";
    write(1, msg3, sizeof(msg3) - 1);
    write(1, media_str, sizeof(media_str) - 1);
    
    exit(0);
}
