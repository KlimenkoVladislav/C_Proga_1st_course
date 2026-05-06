#define _POSIX_C_SOURCE 199309L

#include <stdio.h>
#include <pthread.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutex2 = PTHREAD_MUTEX_INITIALIZER;

struct timespec start, end;
double time_spent;

struct info_for_thread{
    int str_start;
    int str_end;
    int n;
    int *A;
    int *B;
    int *C;
};

void clean(void *i){
    printf("поток №%d помер\n", (int)i);
}

void *print_5_string(void *j){
    int pid = (int)j;

    if (pid == 1){
        for (int i = 0; i<5; i++){
            pthread_mutex_lock(&mutex1);
            printf("thread: %d; Строка %d\n", pid, i);
            pthread_mutex_unlock(&mutex2);
        }
    }
    else{
        for (int i = 0; i<5; i++){
            pthread_mutex_lock(&mutex2);
            printf("thread: %d; Строка %d\n", pid, i);
            pthread_mutex_unlock(&mutex1);
        }
    }

    return NULL;
}

void *time_to_sleep(void *elem){
    sleep((int)elem);
    printf(" %d", (int)elem);
    return NULL;
}

void SleepSort(int *massiv, int n){
    pthread_t pid[20];
    for (int i = 0; i<n; i++){
        int result = pthread_create(&pid[i], NULL, time_to_sleep, (void *)massiv[i]);
        if (result){
            printf("Проблема с созданием потока №%i\n", i);
            return;
        }
    }
    for (int i = 0; i<n; i++){
        pthread_join(pid[i], NULL);
    }
    printf("\n");
}

void *A_mult_B(void *information){
    struct info_for_thread *info = (struct info_for_thread *)information;
    int n = info->n;
    int *A = info->A;
    int *B = info->B;
    int *C = info->C;
    
    for (int i = info->str_start; i < info->str_end; i++){
        for (int j = 0; j < n; j++){
            int sum = 0;
            for (int k = 0; k < n; k++){
                sum += A[i * n + k] * B[k * n + j];
            }
            C[i * n + j] = sum;
        }
    }
    
    return NULL;
}

int main(){
    srand(time(NULL));

    // просто работа с потоками на 3

    // pthread_t pid[4];
    // for (int i = 0; i<4; i++){
    //     int result = pthread_create(&pid[i], NULL, print_5_string, (void *)i);
    //     if (result){
    //         printf("Проблема с созданием потока №%i\n", i);
    //         return -1;
    //     }
    // }
    // sleep(2);
    // for (int i = 0; i<4; i++){
    //     pthread_cancel(pid[i]);
    // }
    // for (int i = 0; i<4; i++){
    //     pthread_join(pid[i], NULL);
    // }

    // сортировка на 3

    // int n = 20;
    // int *massiv = malloc(n*sizeof(int));
    // for (int i = 0; i<n; i++){
    //     massiv[i] = rand()%20;
    // }
    // SleepSort(massiv, n);

    // задание на 4 просто потоки

    // pthread_mutex_lock(&mutex1);

    // pthread_t pid;
    // int result = pthread_create(&pid, NULL, print_5_string, 1);
    // print_5_string(0);
    // if (result){
    //     printf("Проблема с созданием потока\n");
    //     return -1;
    // }
    
    // pthread_join(pid, NULL);

    // задание на 4 матрицы

    for (int n = 16; n<4096; n*=2){
        float res_for_one_n[6];
        res_for_one_n[0] = n;
        for (int stepen = 0; stepen<=4; stepen++){
            int kol_threads = pow(2, stepen);
            int str_to_one_thread = n / kol_threads;
            pthread_t pid[kol_threads];

            int A[n][n];
            int B[n][n];
            int C[n][n];

            for (int i = 0; i<n; i++){
                for (int j = 0; j<n; j++){
                    A[i][j] = 1;
                    B[i][j] = 1;
                    C[i][j] = 0;
                }
            }

            clock_gettime(CLOCK_MONOTONIC, &start);

            for (int i = 0; i<n; i++){
                if (i % (n/kol_threads) == 0){
                    struct info_for_thread *info = malloc(sizeof(struct info_for_thread));
                    *info = (struct info_for_thread){i, i + str_to_one_thread, n, &A[0][0], &B[0][0], &C[0][0]};
                    if (pthread_create(&pid[i / (n/kol_threads)], NULL, A_mult_B, (void *)info)){
                        printf("Проблема с созданием потока\n");
                        return -1;
                    }
                }
            }

            for (int i = 0; i<kol_threads; i++){
                pthread_join(pid[i], NULL);
            }

            clock_gettime(CLOCK_MONOTONIC, &end);

            res_for_one_n[stepen+1] = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;
        }

        FILE *file = fopen("results.txt", "a");
    
        if (file != NULL) {
            for (int i = 0; i < 6; i++) {
                fprintf(file, " %f", res_for_one_n[i]);
            }
            fprintf(file, "\n");
        }

        fclose(file);
    }
}