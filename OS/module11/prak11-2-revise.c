#include <dirent.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>

int main(int argc, char *argv[]) {
  struct dirent *direntp;
  DIR *dirp;
  struct stat sb;
  char fullpath[1024];

  if (argc != 2) {
    fprintf(stderr, "Usage: %s directory_name\n", argv[0]);
    return 1;
  }

  if ((dirp = opendir(argv[1])) == NULL) {
    perror("Failed to open directory");
    return 1;
  }

  printf("%-25s %-15s %-15s\n", "Filename", "Inode", "Size (bytes)");
  printf("-------------------------------------------------------------\n");

  while ((direntp = readdir(dirp)) != NULL) {
    snprintf(fullpath, sizeof(fullpath), "%s/%s", argv[1], direntp->d_name);

    if (stat(fullpath, &sb) == -1) {
      perror("Failed to get file status");
      continue;
    }

    printf("%-25s %-15ld %-15lld\n", direntp->d_name, (long)sb.st_ino,
           (long long)sb.st_size);
  }

  while ((closedir(dirp) == -1) && (errno == EINTR))
    ;
  return EXIT_SUCCESS;
}
