#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(){
    int var, var2;

    var = fork();

    if(var<0){//deu eerro
        printf("erro ao criar processo filho1");
        exit(1);
    }
    else{
        if(var == 0){ //é o processo filho1
            printf("sou o processo filho 1: %d, meu pai é %d", getpid(), getppid());
        }
        else{//é o processo pai
            wait(0); //espera o filho1 

            if(fork()<0){
                printf("erro ao criar o filho2");
                exit(1);
            }
            else{
                if(fork()>0){
                    wait(0);
                }
                else{
                    printf("sou o processo filho 2: %d, meu pai é: %d\n", getpid(), getppid());
                }
            }
        }
    }
    return 0;
}