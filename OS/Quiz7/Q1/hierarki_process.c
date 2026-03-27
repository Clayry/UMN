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

  printf("Masukkan String: ");
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

  pid_c = fork();
  if (pid_c < 0) {
    perror("fork C");
    exit(EXIT_FAILURE);
  }

  if (pid_c == 0) {
    close(pipe_ac[1]);
  }
}
