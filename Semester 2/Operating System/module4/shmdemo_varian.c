#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#define SHM_SIZE 1024 

int main(int argc, char *argv[])
{
    key_t key;
    int shmid;
    char *data;

    if (argc > 2) {
        fprintf(stderr, "usage: ./shmdemo [data_string]\n");
        exit(1);
    }

    key = ftok("shmdemo.c", 'B'); 

    if (key == -1) {
        perror("ftok");
        exit(1);
    }

    shmid = shmget(key, SHM_SIZE, 0644 | IPC_CREAT);
    if (shmid == -1) {
        perror("shmget");
        exit(1);
    }

    data = (char *)shmat(shmid, (void *)0, 0);
    if (data == (char *)(-1)) {
        perror("shmat");
        exit(1);
    }

    if (argc == 2) {
        printf("Writing to segment (ID: %d): \"%s\"\n", shmid, argv[1]);
        strncpy(data, argv[1], SHM_SIZE);
    } else {
        printf("Reading from segment (ID: %d): \"%s\"\n", shmid, data);
        
    }

    // Detach
    shmdt(data);

    return 0;
}