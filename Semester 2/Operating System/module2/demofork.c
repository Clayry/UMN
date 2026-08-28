#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main() {
  pid_t parentPID, childPID, x = 0;
  printf("Main: x = %d\n", x);
  parentPID = getpid();
  childPID = fork();
  if (childPID == 0) {
    printf("In child process\t %d\t%d\n", parentPID, getpid());
    x = 5;
    printf("Child: x = %d\n", x);
    for (;;)
      ;
  } else {
    printf("In parent process\t %d\t%d\n", parentPID, childPID);
    x = 11;
    printf("Parent: x = %d\n", x);
    for (;;)
      ;
  }
}
