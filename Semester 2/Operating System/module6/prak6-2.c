#include <pthread.h>
#include <sched.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define NITERS 10000000
void *count(void *arg);
unsigned int cnt = 0;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

int main() {
  pthread_t tid1, tid2;

  pthread_create(&tid1, NULL, count, NULL);
  pthread_create(&tid2, NULL, count, NULL);
  pthread_join(tid1, NULL);
  pthread_join(tid2, NULL);
  if (cnt != (unsigned)NITERS * 2)
    printf("Wrong... cnt = %d\n", cnt);
  else
    printf("OK...\tcnt=%d\n", cnt);
  exit(0);
}

void *count(void *arg) {
  int i;

  for (i = 0; i < NITERS; i++) {
    pthread_mutex_lock(&mutex);
    cnt++;
    pthread_mutex_unlock(&mutex);
  }

  return count;
}
