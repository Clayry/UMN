#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

void to_uppercase(char *str) {
  for (int i = 0; str[i]; i++) {
    str[i] = toupper((unsigned char)str[i]);
  }
}

int main() {
  char input[256];

  printf("Masukkan string: ");
  fflush(stdout);
  if (fgets(input, sizeof(input), stdin) == NULL) {
    perror("fgets");
    exit(EXIT_FAILURE);
  }
  input[strcspn(input, "\n")] = '\0';

  int pipe_ac[2];
  int pipe_bd[2];

  if (pipe(pipe_ac) == -1 || pipe(pipe_bd) == -1) {
    perror("pipe");
    exit(EXIT_FAILURE);
  }

  pid_t pid_b, pid_c;

  // Fork process C
  pid_c = fork();
  if (pid_c < 0) {
    perror("fork C");
    exit(EXIT_FAILURE);
  }

  if (pid_c == 0) {
    close(pipe_ac[1]);

    close(pipe_bd[0]);
    close(pipe_bd[1]);

    char buf;
    read(pipe_ac[0], &buf, 1);
    close(pipe_ac[0]);

    char upper_str[256];
    strncpy(upper_str, input, sizeof(upper_str));
    to_uppercase(upper_str);

    printf("Process C: %d %d : %s\n", getpid(), getppid(), upper_str);
    fflush(stdout);
    exit(EXIT_SUCCESS);
  }

  // Fork process B
  pid_b = fork();
  if (pid_b < 0) {
    perror("fork B ");
    exit(EXIT_FAILURE);
  }

  if (pid_b == 0) {
    close(pipe_ac[0]);
    close(pipe_ac[1]);

    close(pipe_bd[0]);

    pid_t pid_d;
    pid_d = fork();
    if (pid_d < 0) {
      perror("fork D ");
      exit(EXIT_FAILURE);
    }

    if (pid_d == 0) {
      // Process D
      close(pipe_bd[1]);

      char buf;
      read(pipe_bd[0], &buf, 1);
      close(pipe_bd[0]);

      printf("Process D: %d %d : %s\n", getpid(), getppid(), input);
      fflush(stdout);
      exit(EXIT_FAILURE);
    }
    // Process B
    printf("Process B: %d %d : %s\n", getpid(), getppid(), input);
    fflush(stdout);

    char signal = 1;
    write(pipe_bd[1], &signal, 1);
    close(pipe_bd[1]);

    waitpid(pid_d, NULL, 0);

    exit(EXIT_SUCCESS);
  }

  close(pipe_ac[0]);

  close(pipe_bd[0]);
  close(pipe_bd[1]);

  printf("Process A: %d %d : %s\n", getpid(), getppid(), input);
  fflush(stdout);

  waitpid(pid_b, NULL, 0);

  char signal = 1;
  write(pipe_ac[1], &signal, 1);
  close(pipe_ac[1]);

  waitpid(pid_c, NULL, 0);

  return 0;
}
