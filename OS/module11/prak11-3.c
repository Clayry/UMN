#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  struct flock fl;
  int fd;

  if (argc != 2) {
    printf("Usage: %s <file>\n", argv[0]);
    exit(EXIT_FAILURE);
  }

  if ((fd = open(argv[1], O_RDWR)) == -1) {
    perror("open file");
    exit(1);
  }

  fl.l_type = F_WRLCK;
  fl.l_whence = SEEK_SET;
  fl.l_start = 0;
  fl.l_len = 0;
  fl.l_pid = getpid();

  printf("PID=%d: Press <RETURN> to try to get lock: ", getpid());
  getchar();

  printf("got lock: \t flock.l_pid=%d\n", fl.l_pid);
  printf("Press <RETURN> to release lock: ");
  getchar();

  fl.l_type = F_UNLCK;
  if (fcntl(fd, F_SETLK, &fl) == -1) {
    perror("fcntl");
    exit(1);
  }

  printf("Unlocked.\n");
  close(fd);

  return EXIT_SUCCESS;
}
