#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <pthread.h>

int array[100];
pthread_t threadids[];

int particao(int low, int high){
    int temp;
    int pivo = array[high];
    int i = low-1;

    for(int j=low; j<high; j++){
        if(array[j]<pivo){
            i++;

            //troca os caras de posicao
            temp = array[i];
            array[i] = array[j];
            array[j] = temp;
        }
    }
    temp = array[i+1];
    array[i+1] = array[high];
    array[high] = temp;

    return i+1;
}

void quicksort(int low, int high){
    if(low<high){
        int posici = particao(low, high);

        quicksort(low, posici-1);
        quicksort(posici+1, high);
    }
    pthread_exit();
}

int main(){
    int var;

    printf("digite os 100 números do vetor: ");
    for(int i=0; i<100; i++);{
        scanf("%d", &array[i]);
    }

    printf("o array é: ")
    for(int i=0; i<100; i++){
        printf("%d, ", array[i]);
    }
    
    var = fork();

    if(var<0){
        printf("erro ao criar filho");
        exit(1);
    }
    else{
        if(var>0){
            wait(0);
        }
        else{
            if(pthread_create(threadid[0], NULL, quicksort, (int)0, (int)100)!=0){
                printf("erro ao iniciar a thread");
                exit(1)
            }
        }
    }

}