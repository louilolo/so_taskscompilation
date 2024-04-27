#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <pthread.h>

int array[100] = {
        63, 29, 55, 90, 12, 34, 78, 45, 67, 89,
        23, 56, 78, 91, 24, 75, 38, 82, 17, 49,
        92, 30, 84, 50, 72, 21, 96, 60, 15, 88,
        42, 73, 19, 68, 32, 66, 81, 35, 77, 11,
        53, 99, 61, 26, 74, 39, 80, 44, 95, 58,
        13, 47, 87, 22, 70, 16, 51, 94, 28, 85,
        52, 97, 64, 36, 79, 41, 83, 48, 76, 31,
        98, 57, 33, 69, 25, 86, 59, 14, 71, 37,
        93, 27, 54, 40, 18, 65, 20, 62, 43, 100,
        91, 10, 81, 73, 62, 58, 40, 37, 25, 16
    };

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
}

void* sort(void* retval){
    quicksort(0, 100);
    pthread_exit(retval);
}

int main(){
    int var, retval;

    printf("\no array é: ");
    for(int i=0; i<100; i++){
        printf("%d, ", array[i]);
    }
    printf("\n");

    pthread_t t;

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
            retval = pthread_create(&t, NULL, sort, (void*) &retval);
            if(retval!=0){
                printf("erro ao iniciar a thread");
                exit(1);
            }
            pthread_join(t, NULL);
            printf("\nvetor ordenado: ");
            for(int i=0; i<100; i++){
                printf("%d ", array[i]);
            }
        }
        printf("\n");
    }
    return 0;
}