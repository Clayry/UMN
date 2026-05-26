#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

void err_quit(char *msg) {
    perror(msg);
    exit(1);
}

int main(int argc, char *argv[]) {
    int fdin;
    char *src;
    struct stat statbuf;
    off_t len;

    if (argc != 2) {
        fprintf(stderr, "usage: %s <text file>\n", argv[0]);
        exit(1);
    }

    if ((fdin = open(argv[1], O_RDWR)) < 0)
        err_quit("open");

    if ((fstat(fdin, &statbuf)) < 0)
        err_quit("fstat");

    len = statbuf.st_size;

    if (len == 0) {
        printf("File is empty.\n");
        close(fdin);
        return 0;
    }

    if ((src = mmap(0, len, PROT_READ | PROT_WRITE, MAP_SHARED, fdin, 0)) ==
        (void *)-1)
        err_quit("mmap");

    for (off_t i = 0; i < len / 2; i++) {
        char temp = src[i];
        src[i] = src[len - 1 - i];
        src[len - 1 - i] = temp;
    }

    if (msync(src, len, MS_SYNC) < 0)
        err_quit("msync");

    printf("File contents have been successfully reversed!\n");

    if (munmap(src, len) < 0)
        err_quit("munmap");

    close(fdin);

    return 0;
}
