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

void diskSched_input(int reqList[], int *numOfRequests) {
  int i, nr;
  system("clear");

  printf("===== Disk Scheduling Simulation =====\n");
  printf("Insert the Amount of Requests: ");
  scanf("%d", &nr);

  if (nr < 1 || nr > MAXREQ) {
    printf("Num of requests is not valid\n");
    exit(2);
  }

  *numOfRequests = nr;

  for (i = 0; i < nr; i++) {
    printf("Position of Requests %d: ", i);
    scanf("%d", &reqList[i]);
    if (reqList[i] < MIN_VOL || reqList[i] > MAX_VOL) {
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

  printf("Enter the initial head position: ");
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

  printf("Total head movement: %d\n", dist);
  printf("Enter Any Character to Continue to the Home Screen...\n");
  getchar();
  getchar();
  system("clear");
}

void DiskSched_SCAN(int reqList[], int numOfRequests) {
  int head, direction, dist = 0;
  int i, j, temp;
  int left[MAXREQ], right[MAXREQ + 2];
  int leftCount = 0, rightCount = 0;
  int move[MAXREQ + 5];
  int moveCount = 0;

  printf("Insert the Starting Head Position: ");
  scanf("%d", &head);

  printf("Choose Initial Direction (0 for Left/To 0, 1 for Right/To 199): ");
  scanf("%d", &direction);

  int sortedReq[MAXREQ];
  for (i = 0; i < numOfRequests; i++)
    sortedReq[i] = reqList[i];

  for (i = 0; i < numOfRequests - 1; i++) {
    for (j = 0; j < numOfRequests - i - 1; j++) {
      if (sortedReq[j] > sortedReq[j + 1]) {
        temp = sortedReq[j];
        sortedReq[j] = sortedReq[j + 1];
        sortedReq[j + 1] = temp;
      }
    }
  }

  for (i = 0; i < numOfRequests; i++) {
    if (sortedReq[i] < head) {
      left[leftCount++] = sortedReq[i];
    } else if (sortedReq[i] == head) {
      right[moveCount++] = sortedReq[i];
    } else {
      if (direction == 0)
        left[leftCount++] = sortedReq[i];
      else
        right[rightCount++] = sortedReq[i];
    }
  }

  for (i = 0; i < leftCount / 2; i++) {
    temp = left[i];
    left[i] = left[leftCount - i - 1];
    left[leftCount - i - 1] = temp;
  }

  move[moveCount++] = head;

  if (direction == 0) {
    for (i = 0; i < leftCount; i++) {
      move[moveCount++] = left[i];
    }

    if (leftCount > 0) {
      move[moveCount++] = MIN_VOL;
    }

    for (i = 0; i < rightCount; i++) {
      move[moveCount++] = right[i];
    }

  } else {

    for (i = 0; i < rightCount; i++) {
      move[moveCount++] = right[i];
    }

    if (rightCount > 0) {
      move[moveCount++] = MAX_VOL;
    }

    for (i = 0; i < leftCount; i++) {
      move[moveCount++] = left[i];
    }
  }

  int finalMove[MAXREQ + 5];
  int finalCount = 0;

  finalMove[finalCount++] = move[0];

  for (i = 1; i < finalCount; i++) {
    if (move[i] != finalMove[finalCount - 1]) {
      finalMove[finalCount++] = move[i];
    }
  }

  for (i = 0; i < finalCount - 1; i++) {
    dist += abs(finalMove[i] - finalMove[i + 1]);
  }

  printf("Move Sequence:\n");
  printf("{");

  for (i = 0; i < finalCount; i++) {
    if (i == finalCount - 1) {
      printf("%d}\n", finalMove[i]);
    } else {
      printf("%d, ", finalMove[i]);
    }
  }

  printf("Total movement: %d\n", dist);
  printf("Enter Any Character to Continue to the Home Screen...\n");
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

    if (choice == 1) {
      diskSched_input(reqList, &numOfRequests);
      DiskSched_SSTF(reqList, numOfRequests);
    } else if (choice == 2) {
      diskSched_input(reqList, &numOfRequests);
      DiskSched_SCAN(reqList, numOfRequests);
    } else {
      printf("Bye Bye.., and have a nice day\n");
      break;
    }
  }

  return 0;
}
