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

    if ((fdin = open(argv[1], O_RDONLY)) < 0)
        err_quit("open");

    if ((fstat(fdin, &statbuf)) < 0)
        err_quit("fstat");

    len = statbuf.st_size;

    if ((src = mmap(0, len, PROT_READ, MAP_SHARED, fdin, 0)) == (void *)-1)
        err_quit("mmap");

    write(1, src, len);

    close(fdin);
    munmap(src, len);

    return 0;
}
