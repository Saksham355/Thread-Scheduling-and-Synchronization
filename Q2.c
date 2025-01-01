#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>

struct server {
    int id;
    sem_t *left;
    sem_t *right;
};

struct server* server_new(int id, sem_t *left, sem_t *right) {
    struct server* s = malloc(sizeof(*s));
    s->id = id;
    s->left = left;
    s->right = right;
    return s;
}

sem_t c1;
sem_t c2;
sem_t c3;
sem_t c4;
sem_t c5;

void *mythread(void *arg) {
    struct server *s = (struct server *)arg;
    
    for (int i = 0; i < 3; i++) { 
        printf("Server %d is waiting \n", s->id);
        sem_wait(s->left);
        sem_wait(s->right);
        printf("Server %d is processing\n", s->id);
        sleep(1);
        sem_post(s->right);
        sem_post(s->left);
        sleep(1);
    }
    return NULL;
}

int main() {
    sem_init(&c1, 0, 1);
    sem_init(&c2, 0, 1);
    sem_init(&c3, 0, 1);
    sem_init(&c4, 0, 1);
    sem_init(&c5, 0, 1);
    pthread_t s1;
    pthread_t s2;
    pthread_t s3;
    pthread_t s4;
    pthread_t s5;

    struct server* serv1 = server_new(1, &c5, &c1);
    struct server* serv2 = server_new(2, &c1, &c2);
    struct server* serv3 = server_new(3, &c2, &c3);
    struct server* serv4 = server_new(4, &c3, &c4);
    struct server* serv5 = server_new(5, &c4, &c5);

    pthread_create(&s1, NULL, mythread, serv1);
    pthread_create(&s2, NULL, mythread, serv2);
    pthread_create(&s3, NULL, mythread, serv3);
    pthread_create(&s4, NULL, mythread, serv4);
    pthread_create(&s5, NULL, mythread, serv5);

    pthread_join(s1, NULL);
    pthread_join(s2, NULL);
    pthread_join(s3, NULL);
    pthread_join(s4, NULL);
    pthread_join(s5, NULL);

    sem_destroy(&c1);
    sem_destroy(&c2);
    sem_destroy(&c3);
    sem_destroy(&c4);
    sem_destroy(&c5);

    free(serv1);
    free(serv2);
    free(serv3);
    free(serv4);
    free(serv5);
    return 0;
}
