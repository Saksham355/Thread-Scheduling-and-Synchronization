#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define BUFFER_SIZE 10
#define MAX_PRODUCTS 5

typedef struct {
    int c_buffer[BUFFER_SIZE];
    int inc;
    int dec;
    int count;
} buffer;

buffer b = {.inc = 0, .dec = 0, .count = 0};
pthread_mutex_t mutex;
sem_t load, store;

void* delivery_truck(void* arg) {
    int id = *(int*)arg;
    while (1) {
        int products = rand() % MAX_PRODUCTS + 1;
        sem_wait(&load);
        pthread_mutex_lock(&mutex);
        if (b.count + products <= BUFFER_SIZE) {
            b.c_buffer[b.inc] = products;
            b.inc = (b.inc + 1) % BUFFER_SIZE;
            b.count += products;
            printf("Truck %d delivered %d products, buffer count: %d\n",id,products, b.count);
        }
        pthread_mutex_unlock(&mutex);
        sem_post(&store);
        sleep(rand() % 4 + 1);
    }
    return NULL;
}

void* storage_manager(void*arg) {
    int id = *(int*)arg;
    while (1) {
        int products = rand() % MAX_PRODUCTS + 1;
        sem_wait(&store);
        pthread_mutex_lock(&mutex);
        if (b.count > 0) {
            int remove = (products > b.count) ? b.count : products;
            b.dec = (b.dec + 1) % BUFFER_SIZE;
            b.count -= remove;
            printf("Manager %d stored %d products, buffer count: %d\n",id,remove, b.count);
        }
        pthread_mutex_unlock(&mutex);
        sem_post(&load);
        sleep(rand() % 4 + 1);
    }
    return NULL;
}

int main() {
    int trucks;
    printf("Enter the number of trucks:");
    scanf("%d",&trucks);
    int managers;
    printf("Enter the number of managers:");
    scanf("%d",&managers);
    pthread_t truck_threads[trucks], manager_threads[managers];
    sem_init(&load, 0, BUFFER_SIZE);
    sem_init(&store, 0, 0);
    pthread_mutex_init(&mutex, NULL);

    
    for (int i = 0; i < managers; i++) {
        int*id = malloc(sizeof(int));
        *id = i+1;
        pthread_create(&manager_threads[i], NULL, storage_manager, id);
        }
    for (int i = 0; i < trucks; i++) {
        int*id = malloc(sizeof(int));
        *id = i+1;
        pthread_create(&truck_threads[i], NULL, delivery_truck, id);
    }
    sleep(b.count);

    for (int i = 0; i < trucks; i++) pthread_cancel(truck_threads[i]);
    for (int i = 0; i < managers; i++) pthread_cancel(manager_threads[i]);

    for (int i = 0; i < trucks; i++) pthread_join(truck_threads[i], NULL);
    for (int i = 0; i < managers; i++) pthread_join(manager_threads[i], NULL);

    sem_destroy(&load);
    sem_destroy(&store);
    pthread_mutex_destroy(&mutex);

    printf("Simulation complete.\n");
    return 0;
}
