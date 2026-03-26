#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>

typedef struct Node {
  int data;
  struct Node *next;
} Node;

typedef struct Queue {
  Node *front;
  Node *rear;
} Queue;

void initQueue(Queue *q) {
  q->front = NULL;
  q->rear = NULL;
}

int isEmpty(Queue *q) { return q->front == NULL; }

int isFull() { return 0; }

void enqueue(Queue *q, int value) {
  Node *newNode = (Node *)malloc(sizeof(Node));
  if (!newNode) {
    printf("Memory Allocation Failed\n");
    return;
  }
  newNode->data = value;
  newNode->next = NULL;

  if (isEmpty(q)) {
    q->front = newNode;
    q->rear = newNode;
  } else {
    q->rear->next = newNode;
    q->rear = newNode;
  }
  printf("[enqueue] %d successfully added.\n", value);
}

int dequeue(Queue *q) {
  if (isEmpty(q)) {
    printf("[dequeue] Error: Queue is empty\n");
    return -1;
  }

  Node *temp = q->front;
  int value = temp->data;

  q->front = q->front->next;

  if (q->front == NULL) {
    q->rear = NULL;
  }
  free(temp);

  printf("[dequeue] %d removed.\n", value);
  return value;
}

int peek(Queue *q) {
  if (isEmpty(q)) {
    printf("[peek] Queue is empty\n");
    return -1;
  }
  return q->front->data;
}

void printQueue(Queue *q) {
  if (isEmpty(q)) {
    printf("Queue: [empty]\n");
    return;
  }
  Node *current = q->front;
  printf("Queue: \n");
  while (current != NULL) {
    printf("%d -> ", current->data);
    current = current->next;
  }
  printf("NULL\n");
}

void clearQueue(Queue *q) {
  while (!isEmpty(q)) {
    dequeue(q);
  }
  printf("Queue cleared.\n");
}

int main() {
  Queue q;
  initQueue(&q);

  int choice = 0;
  int value;

  do {
    printf("\n==== Queue Menu ====\n");
    printf("1. Enqueue\n");
    printf("2. Dequeue\n");
    printf("3. isFull (Check Capacity)\n");
    printf("4. isEmpty (Check Status)\n");
    printf("5. Peek (Front Element)\n");
    printf("6. Print Queue\n");
    printf("7. Clear Queue\n");
    printf("8. Exit\n");
    printf("Choice: ");

    if (scanf("%d", &choice) != 1) {
      printf("Invalid input. Please enter a number.\n");
      while (getchar() != '\n')
        ;
      continue;
    }

    switch (choice) {
    case 1:
      printf("Enter value to enqueue: ");
      scanf("%d", &value);
      enqueue(&q, value);
      break;
    case 2:
      dequeue(&q);
      break;
    case 3:
      printf("Queue is %s.\n", isFull() ? "Full" : "Not Full (Dynamic)");
      break;
    case 4:
      printf("Queue is %s.\n", isEmpty(&q) ? "Empty" : "Not Empty");
      break;
    case 5:
      value = peek(&q);
      if (value != -1)
        printf("Front element is: %d\n", value);
      break;
    case 6:
      printQueue(&q);
      break;
    case 7:
      clearQueue(&q);
      break;
    case 8:
      clearQueue(&q);
      printf("Exiting...\n");
      break;
    default:
      printf("Invalid choice, try again.\n");
    }
  } while (choice != 8);

  return 0;
}
