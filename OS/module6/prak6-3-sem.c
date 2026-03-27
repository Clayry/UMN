#include <fcntl.h>
#include <pthread.h>
#include <sched.h>
#include <semaphore.h>
#include <stdio.h>
#include <unistd.h>

#define NITERS 100000000

sem_t *sem1, *sem2;
void *thread_1(void *arg);
void *thread_2(void *arg);

int main() {
  pthread_t tid1, tid2;

  sem_unlink("/sem1");
  sem_unlink("/sem2");
  sem1 = sem_open("/sem1", O_CREAT, 0644, 1);
  sem2 = sem_open("/sem2", O_CREAT, 0644, 1);

  pthread_create(&tid1, NULL, thread_1, NULL);
  pthread_create(&tid2, NULL, thread_2, NULL);
  pthread_join(tid1, NULL);
  pthread_join(tid2, NULL);

  sem_close(sem1);
  sem_unlink("/sem1");
  sem_close(sem2);
  sem_unlink("/sem2");
  return 0;
}

void *thread_1(void *arg) {
  int i;
  for (i = 0; i < NITERS; i++) {
    sem_wait(sem1);
    sem_wait(sem2);
    printf("Thread 1\n");
    sem_post(sem2);
    sem_post(sem1);
  }
  return NULL;
}

void *thread_2(void *arg) {
  int i;
  for (i = 0; i < NITERS; i++) {
    sem_wait(sem2);
    sem_wait(sem1);
    printf("Thread 2\n");
    sem_post(sem1);
    sem_post(sem2);
  }
  return NULL;
}
