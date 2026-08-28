#include <stdio.h>
#define MAX 5

int queue[MAX];
int front = -1;
int rear = -1;

int isFull() { return rear == MAX - 1; }

int isEmpty() { return front == -1 || front > rear; }

void peek() {
  if (isEmpty()) {
    printf("Queue is empty\n");
    return;
  }
  printf("Front element: %d\n", queue[front]);
}

void enqueue(int value) {
  if (isFull()) {
    printf("Queue Overflow\n");
    return;
  }
  if (front == -1)
    front = 0;
  rear++;
  queue[rear] = value;
  printf("%d enqueued\n", value);
}

void dequeue() {
  if (isEmpty()) {
    printf("Queue Underflow\n");
    return;
  }
  printf("%d dequeued\n", queue[front]);
  front++;
  if (front > rear) {
    front = -1;
    rear = -1;
  }
}

void printQueue() {
  if (isEmpty()) {
    printf("Queue: [Empty]\n");
    return;
  }
  for (int i = front; i <= rear; i++) {
    printf("[%d]\t", queue[i]);
  }
  printf("\n");
}

void clearQueue() {
  front = -1;
  rear = -1;
  printf("Queue cleared\n");
}

int main() {
  int choice;
  int value;

  do {
    printf("\n==== Menu ====\n");
    printf("1. Enqueue\n");
    printf("2. Dequeue\n");
    printf("3. isFull\n");
    printf("4. isEmpty\n");
    printf("5. Peek\n");
    printf("6. PrintQueue\n");
    printf("7. Clear Queue\n");
    printf("8. Exit\n");
    printf("Type Answer: ");

    if (scanf("%d", &choice) != 1) {
      while (getchar() != '\n')
        ;
      continue;
    }

    switch (choice) {
    case 1:
      printf("Enter Value: ");
      scanf("%d", &value);
      enqueue(value);
      break;
    case 2:
      dequeue();
      break;
    case 3:
      printf(isFull() ? "Queue is full\n" : "Queue isn't full\n");
      break;
    case 4:
      printf(isEmpty() ? "Queue is empty\n" : "Queue isn't empty\n");
      break;
    case 5:
      peek();
      break;
    case 6:
      printQueue();
      break;
    case 7:
      clearQueue();
      break;
    case 8:
      printf("Exiting...\n");
      break;
    }
  } while (choice != 8);

  return 0;
}
