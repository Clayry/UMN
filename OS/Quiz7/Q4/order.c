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
#define SEM_EMPTY "/sem_emtpy"
#define SEM_FULL "/sem_full"

int main() {
  int shmid = shmget(SHM_KEY, sizeof(int), IPC_CREAT | 0666);
  int *buffer = (int *)shmat(shmid, NULL, 0);
  *buffer = 0;

  sem_t *mutex = sem_open(SEM_MUTEX, O_CREAT, 0666, 1);
  sem_t *empty = sem_open(SEM_EMPTY, O_CREAT, 0666, 50);
  sem_t *full = sem_open(SEM_FULL, O_CREAT, 0666, 0);

  srand(time(NULL));
  printf("Restoran Bobi: Pelayan mulai menerima pesanan...\n ");

  for (int i = 0; i < 20; i++) {
    sleep(rand() % 3);

    sem_wait(empty);
    sem_wait(mutex);

    (*buffer)++;
    printf("[Order] Pesanan baru dicatat! Total di buffer: %d \n", *buffer);

    sem_post(mutex);
    sem_post(full);
  }

  shmdt(buffer);
  return 0;
}
