#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
int main() {
  char input_string[256];

  printf("Masukkan string: ");
  fgets(input_string, sizeof(input_string), stdin);
  input_string[strcspn(input_string, "\n")] = 0;

  printf("Process A: %d %d : %s\n", getpid(), getppid(), input_string);

  pid_t pid_B = fork();

  if (pid_B == 0) {
    printf("Process B: %d %d : %s\n", getpid(), getppid(), input_string);
    pid_t pid_D = fork();
    if (pid_D == 0) {
      printf("Process B: %d %d : %s\n", getpid(), getppid(), input_string);
      exit(0);
    } else if (pid_D > 0) {
      waitpid(pid_D, NULL, 0);
      exit(0);
    }
  } else if (pid_B > 0) {
    waitpid(pid_B, NULL, 0);

    pid_t pid_C = fork();
    if (pid_C == 0) {
      for (int i = 0; input_string[i]; i++) {
        input_string[i] = toupper(input_string[i]);
      }
      printf("Process C: %d %d : %s\n", getpid(), getppid(), input_string);
      exit(0);
    } else if (pid_C > 0) {
      waitpid(pid_C, NULL, 0);
    }
  }
  return 0;
}
