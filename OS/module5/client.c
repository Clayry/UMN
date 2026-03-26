#include <fcntl.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#define SHMSZ 27
char SEM_NAME[] = "mysem";

int main() {
  char ch;
  int shmid;
  key_t key;
  char *shm, *s;
  sem_t *mutex;

  key = 1000;
  mutex = sem_open(SEM_NAME, O_CREAT, 0644, 1);
  shmid = shmget(key, SHMSZ, IPC_CREAT | 0666);
  shm = shmat(shmid, NULL, 0);

  while (*shm != 'A') {
    sleep(1);
  }

  for (s = shm; *s != '\0'; s++) {
    sem_wait(mutex);
    putchar(*s);
    sem_post(mutex);
  }
  printf("\n");

  *shm = '*';
  sem_close(mutex);
  sem_unlink(SEM_NAME);
  shmctl(shmid, IPC_RMID, 0);
  exit(0);
}
