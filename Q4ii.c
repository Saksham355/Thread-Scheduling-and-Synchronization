#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include <unistd.h>

#define MAX_THREADS 4

typedef struct {
    int row, col, n;
    int** A;
    int** B;
    int** C;
} Task;

typedef struct {
    Task* tasks;
    int total_tasks;
    int current_task;
    pthread_mutex_t lock;
} SharedData;

void* thread_pool_worker(void* arg) {
    SharedData* data = (SharedData*)arg;

    while (1) {
        Task* task = NULL;

        pthread_mutex_lock(&data->lock);
        if (data->current_task < data->total_tasks) {
            task = &data->tasks[data->current_task++];
        }
        pthread_mutex_unlock(&data->lock);

        if (!task) break;

        int sum = 0;
        for (int i = 0; i < task->n; i++) {
            sum += task->A[task->row][i] * task->B[i][task->col];
        }
        task->C[task->row][task->col] = sum;
    }
    return NULL;
}

void sequential_multiply(int** A, int** B, int** C, int m, int n, int p) {
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < p; j++) {
            int sum = 0;
            for (int k = 0; k < n; k++) {
                sum += A[i][k] * B[k][j];
            }
            C[i][j] = sum;
        }
    }
}

int main() {
    int m, n, p;
    printf("Enter dimensions of Matrix A (m x n): ");
    scanf("%d %d", &m, &n);
    printf("Enter dimensions of Matrix B (n x p): ");
    scanf("%d %d", &n, &p);

    int** A = malloc(m * sizeof(int*));
    int** B = malloc(n * sizeof(int*));
    int** C = malloc(m * sizeof(int*));
    int** C_sequential = malloc(m * sizeof(int*));

    for (int i = 0; i < m; i++) {
        A[i] = malloc(n * sizeof(int));
        C[i] = malloc(p * sizeof(int));
        C_sequential[i] = malloc(p * sizeof(int));
    }
    for (int i = 0; i < n; i++) {
        B[i] = malloc(p * sizeof(int));
    }

    printf("Enter elements of Matrix A:\n");
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &A[i][j]);
        }
    }

    printf("Enter elements of Matrix B:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < p; j++) {
            scanf("%d", &B[i][j]);
        }
    }

    clock_t start_seq = clock();
    sequential_multiply(A, B, C_sequential, m, n, p);
    clock_t end_seq = clock();
    double sequential_time = (double)(end_seq - start_seq) / CLOCKS_PER_SEC;

    Task* tasks = malloc(m * p * sizeof(Task));
    SharedData shared_data = {tasks, m * p, 0, PTHREAD_MUTEX_INITIALIZER};

    int task_index = 0;
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < p; j++) {
            tasks[task_index++] = (Task){i, j, n, A, B, C};
        }
    }

    pthread_t threads[MAX_THREADS];
    clock_t start_parallel = clock();
    for (int i = 0; i < MAX_THREADS; i++) {
        pthread_create(&threads[i], NULL, thread_pool_worker, &shared_data);
    }
    for (int i = 0; i < MAX_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }
    clock_t end_parallel = clock();
    double parallel_time = (double)(end_parallel - start_parallel) / CLOCKS_PER_SEC;

    printf("Resultant Matrix C (Parallel):\n");
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < p; j++) {
            printf("%d ", C[i][j]);
        }
        printf("\n");
    }

    printf("\nSequential Execution Time: %f seconds\n", sequential_time);
    printf("Parallel Execution Time: %f seconds\n", parallel_time);
    printf("Speedup: %f\n", sequential_time / parallel_time);

    for (int i = 0; i < m; i++) {
        free(A[i]);
        free(C[i]);
        free(C_sequential[i]);
    }
    for (int i = 0; i < n; i++) {
        free(B[i]);
    }
    free(A);
    free(B);
    free(C);
    free(C_sequential);
    free(tasks);

    return 0;
}
