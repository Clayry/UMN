#include <asm-generic/errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct Student {
  char nim[13];
  char name[13];
  char major[50];

  struct Student *next;
} Student;

int isEmpty(Student *queue) {
  if (queue == NULL)
    return 1;
  return 0;
}

void enqueue(Student **head, Student **tail, char nim[], char name[],
             char major[]) {
  Student *data = (Student *)malloc(sizeof(Student));

  strcpy(data->nim, nim);
  strcpy(data->name, name);
  strcpy(data->major, major);
  data->next = NULL;

  if (isEmpty(*head))
    *head = data;
  else
    (*tail)->next = data;

  *tail = data;

  printf("Adding %s to queue\n", name);
}

void dequeue(Student **head) {
  printf("Removing queue's front element\n");

  if (isEmpty(*head)) {
    printf("Nothing to dequeue. Queue already empty\n");
    return;
  }

  Student *trash = *head;
  *head = trash->next;
  free(trash);

  printf("Dequeueing success\n");
}

Student *front(Student *queue) {
  if (queue == NULL)
    return NULL;
  return queue;
}

int main() {
  printf("QUEUE TUTORIAL\n");
  printf("--------------\n\n");

  printf("Initializing Queue\n\n");

  Student *headQueue, *tailQueue;
  headQueue = tailQueue = NULL;

  printf("Is Queue empty? %s\n", isEmpty(headQueue) ? "Yes" : "No");
  printf("What is the name of the front? %s\n\n", front(headQueue) == NULL
                                                      ? "No one. Queue is empty"
                                                      : front(headQueue)->name);

  enqueue(&headQueue, &tailQueue, "L12312", "Febe", "Informatics");

  printf("What is the name of the front? %s\n\n", front(headQueue) == NULL
                                                      ? "No one. Queue is empty"
                                                      : front(headQueue)->name);

  printf("Is Queue empty? %s\n", isEmpty(headQueue) ? "Yes" : "No");

  dequeue(&headQueue);

  printf("Is Queue empty? %s\n", isEmpty(headQueue) ? "Yes" : "No");

  printf("What is the name of the front? %s\n\n", front(headQueue) == NULL
                                                      ? "No one. Queue is empty"
                                                      : front(headQueue)->name);
}
