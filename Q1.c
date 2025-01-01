#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <assert.h>

pthread_mutex_t lockA;
pthread_mutex_t lockB; 
void *mythread(void *arg) {
    char *thread = (char*)arg;
    for (int i = 0; i < 3; i++) {
        printf("%s waiting for lock A\n",thread);
        pthread_mutex_lock(&lockA);
        printf("%s acquired lock A\n",thread);

        printf("%s waiting for lock B\n",thread);
        pthread_mutex_lock(&lockB);
        printf("%s acquired lock B\n",thread);
        sleep(1);
        pthread_mutex_unlock(&lockB);
        printf("%s released lock B\n",thread);
        pthread_mutex_unlock(&lockA);
        printf("%s released lock A\n",thread);
        sleep(1);
    }
    printf("%s: done\n", (char *)arg);
    return NULL;
}

int main() {
    pthread_t T1, T2, T3;
    pthread_mutex_init(&lockA, NULL);
    pthread_mutex_init(&lockB, NULL);
    pthread_create(&T1, NULL, mythread, "T1");
    pthread_create(&T2, NULL, mythread, "T2");
    pthread_create(&T3, NULL, mythread, "T3");

    pthread_join(T1, NULL);
    pthread_join(T2, NULL);
    pthread_join(T3, NULL);
    pthread_mutex_destroy(&lockA);
    pthread_mutex_destroy(&lockB);
    return 0;
}
