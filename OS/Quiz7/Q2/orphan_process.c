#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
int main() {
  pid_t child1 = fork();

  if (child1 == 0) {
    sleep(2);
    printf("Deposit sukses oleh Child 1 (Pid: %d, Parent PID awal: %d)\n",
           getpid(), getppid());
    exit(0);
  }

  if (child1 > 0) {
    pid_t child2 = fork();

    sleep(3);
    printf("Withdrawal sukses oleh child2 (PID: %d, PPID: %d)\n", getpid(),
           getppid());
    exit(0);
  }

  printf("Parent Process (PID: %d) keluar lebih dulu.\n", getpid());
  exit(0);
}
