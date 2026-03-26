#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

#define NITERS 10000000

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER; [cite: 48]
unsigned int cnt = 0;

void *count(void *arg) {
    int i;
    for (i = 0; i < NITERS; i++) {
        pthread_mutex_lock(&mutex);   // Lock [cite: 50]
        cnt++;                        // Critical Region [cite: 51]
        pthread_mutex_unlock(&mutex); // Unlock [cite: 52]
    }
    return NULL;
}

int main() {
    pthread_t tid1, tid2;
    pthread_create(&tid1, NULL, count, NULL);
    pthread_create(&tid2, NULL, count, NULL);
    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);

    printf("Final cnt = %u\n", cnt);
    return 0;
}