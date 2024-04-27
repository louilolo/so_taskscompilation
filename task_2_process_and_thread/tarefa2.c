#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(){
    int var, var2;

    printf("olá, eu sou o processo: %d\n", getpid());

    var = fork();

    if(var<0){//deu eerro
        printf("erro ao criar processo filho1\n");
        exit(1);
    }
    else{
        if(var == 0){ //é o processo filho1
            printf("sou o processo filho 1: %d, meu pai é: %d\n", getpid(), getppid());
        }
        else{//é o processo pai
            wait(0); //espera o filho1

	    var2 = fork();//cria o filho 2, pois aqui ainda é o pai
            if(var2<0){//erro
                printf("erro ao criar o filho2\n");
                exit(1);
            }
            else{
                if(var2>0){//ainda é o pai ai ele espera
                    wait(0);
                }
                else{//é o filho2
                    printf("sou o processo filho 2: %d, meu pai é: %d\n", getpid(), getppid());
                }
            }
        }
    }
    return 0;
}
