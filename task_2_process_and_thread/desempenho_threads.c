#include <pthread.h>

typedef struct {
    int *arr;
    int start;
    int end;
    int sum;
} ThreadData;

void *thread_sum(void *arg) {
    ThreadData *data = (ThreadData *)arg;
    data->sum = 0;
    for (int i = data->start; i < data->end; i++) {
        data->sum += data->arr[i];
    }
    pthread_exit(NULL);
}

double measure_threads() {
    int arr[SIZE];
    init_array(arr, SIZE);

    pthread_t threads[4];
    ThreadData thread_data[4];
    int step = SIZE / 4;

    struct timeval start, end;
    gettimeofday(&start, NULL);

    for (int i = 0; i < 4; i++) {
        thread_data[i].arr = arr;
        thread_data[i].start = i * step;
        thread_data[i].end = (i + 1) * step;
        pthread_create(&threads[i], NULL, thread_sum, &thread_data[i]);
    }

    int total_sum = 0;
    for (int i = 0; i < 4; i++) {
        pthread_join(threads[i], NULL);
        total_sum += thread_data[i].sum;
    }

    gettimeofday(&end, NULL);
    printf("Soma total usando threads: %d\n", total_sum);

    return (end.tv_sec - start.tv_sec) * 1000000 + (end.tv_usec - start.tv_usec);
}
