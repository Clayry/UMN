#include <pthread.h>
#include <sched.h>
#include <stdio.h>
#include <unistd.h>

#define NITERS 100000000
pthread_mutex_t mutex_1 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutex_2 = PTHREAD_MUTEX_INITIALIZER;
void *thread_1(void *arg);
void *thread_2(void *arg);

int main() {
  pthread_t tid1, tid2;

  pthread_create(&tid1, NULL, thread_1, NULL);
  pthread_create(&tid2, NULL, thread_2, NULL);
  pthread_join(tid1, NULL);
  pthread_join(tid2, NULL);
}

void *thread_1(void *arg) {
  int i;

  for (i = 0; i < NITERS; i++) {
    pthread_mutex_lock(&mutex_1);
    pthread_mutex_lock(&mutex_2);
    printf("Thread 1\n");
    pthread_mutex_unlock(&mutex_2);
    pthread_mutex_unlock(&mutex_1);
  }
  return NULL;
}

void *thread_2(void *arg) {
  int i;

  for (i = 0; i < NITERS; i++) {
    pthread_mutex_lock(&mutex_2);
    pthread_mutex_lock(&mutex_1);
    printf("Thread 2 \n");
    pthread_mutex_unlock(&mutex_1);
    pthread_mutex_unlock(&mutex_2);
  }
  return NULL;
}
