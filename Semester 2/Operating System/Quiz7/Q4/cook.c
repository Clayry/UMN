#include <fcntl.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <time.h>
#include <unistd.h>

#define SHM_KEY 1234
#define SEM_MUTEX "/sem_mutex"
#define SEM_EMPTY "/sem_empty"
#define SEM_FULL "/sem_full"

int main() {
  int shmid = shmget(SHM_KEY, sizeof(int), 0666);
  int *buffer = (int *)shmat(shmid, NULL, 0);

  sem_t *mutex = sem_open(SEM_MUTEX, 0);
  sem_t *empty = sem_open(SEM_EMPTY, 0);
  sem_t *full = sem_open(SEM_FULL, 0);

  srand(time(NULL) + 1);
  printf("Restoran Bobi: Koki mulai memasak...\n ");

  while (1) {
    sleep(rand() % 4);

    sem_wait(full);
    sem_wait(mutex);

    (*buffer)--;
    printf("[Cook] Pesanan selesai dimasak! Sisa di bffer: %d \n", *buffer);

    sem_post(mutex);
    sem_post(empty);
  }

  shmdt(buffer);
  return 0;
}
