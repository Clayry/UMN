#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define MAXREQ 50
#define MIN_VOL 0
#define MAX_VOL 199

int mainMenu() {
    int choice;
    while (1) {
        printf("Choose Which Action to Perform\n");
        printf("1. SSTF Disk Scheduling\n");
        printf("2. Scan/Elevator Disk Scheduling\n");
        printf("0. Quit Program\n");
        printf("Your Choice: ");
        scanf("%d", &choice);
        if (choice == 0 || choice == 1 || choice == 2)
            return choice;
        else {
            system("clear");
            printf("The Number you have chosen does not correspond to any menu "
                   "option...\n");
            printf("Try again...\n");
        }
    }
}

void DiskSched_input(int reqList[], int *numOfRequests) {
    int i, nr;
    system("clear");
    printf("===== Disk Scheduling Simulation =====\n");
    printf("Insert the Amount of Requests: ");
    scanf("%d", &nr);
    if (nr < 1 || nr > 50) {
        printf("Num of requests is not valid\n");
        exit(2);
    }
    *numOfRequests = nr;
    for (i = 0; i < nr; i++) {
        printf("Position of Requests %d: ", i);
        scanf("%d", &reqList[i]);
        if (reqList[i] < 0 || reqList[i] > 199) {
            printf("Vol/Track request is out of range\n");
            exit(2);
        }
    }
    system("clear");
    printf("Seek Sequence:\n");
    printf("{");
    for (i = 0; i < nr; i++) {
        if (i == nr - 1) {
            printf("%d}\n", reqList[i]);
        } else {
            printf("%d, ", reqList[i]);
        }
    }
}

void DiskSched_SSTF(int reqList[], int numOfRequests) {
    int dist = 0, step, head, i_min, min = INT_MAX;
    int i, j, flag[MAXREQ] = {0}, move[MAXREQ];
    printf("Insert the Starting Head Position: ");
    scanf("%d", &head);
    move[0] = head;
    for (j = 0; j < numOfRequests; j++) {
        for (i = 0; i < numOfRequests; i++) {
            if (flag[i])
                continue;
            step = abs(head - reqList[i]);
            if (step < min) {
                min = step;
                i_min = i;
            }
        }
        dist += min;
        head = reqList[i_min];
        flag[i_min] = 1;
        move[j + 1] = head;
        min = INT_MAX;
    }
    printf("Move Sequence:\n");
    printf("{");
    for (i = 0; i < numOfRequests + 1; i++) {
        if (i == numOfRequests) {
            printf("%d}\n", move[i]);
        } else {
            printf("%d, ", move[i]);
        }
    }
    printf("Total movement = %d", dist);
    printf("\nEnter Any Character to Continue to the Home Screen...\n");
    getchar();
    getchar();
    system("clear");
}

int main() {
    int choice;
    int numOfRequests;
    int reqList[MAXREQ];
    while (1) {
        system("clear");
        choice = mainMenu();
        getchar();
        if (choice) {
            if (choice == 1) {
                DiskSched_input(reqList, &numOfRequests);
                DiskSched_SSTF(reqList, numOfRequests);
            } else if (choice == 2) {}
        } else {
            printf("Bye Bye..., and have a nice day\n");
            break;
        }
    }
}
