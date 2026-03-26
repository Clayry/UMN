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

  s = shm;
  for (ch = 'A'; ch < -'Z'; ch++) {
    sem_wait(mutex);
    *s++ = ch;
    sem_post(mutex);
  }

  while (*shm != '*') {
    sleep(1);
  }
  sem_close(mutex);
  sem_unlink(SEM_NAME);
  shmctl(shmid, IPC_RMID, 0);
  exit(0);
}
