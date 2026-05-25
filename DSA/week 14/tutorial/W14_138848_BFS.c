#include <stdio.h>
#include <stdlib.h>

typedef struct Edge {
  int dest;
  struct Edge *next;
} Edge;

typedef struct Queue {
  int data;
  struct Queue *next;
} Queue;

void addEdge(Edge *adjList[], int src, int dest) {
  Edge *temp;

  temp = (Edge *)malloc(sizeof(Edge));
  temp->dest = dest;
  temp->next = NULL;

  if (adjList[src] == NULL) {
    adjList[src] = temp;
  } else {
    Edge *ptr = adjList[src];
    while (ptr->next != NULL) {
      ptr = ptr->next;
    }
    ptr->next = temp;
  }
}

int isEmpty(Queue *queue) {
  if (queue == NULL)
    return 1;
  return 0;
}

void enqueue(Queue **queue, int start) {
  Queue *data = (Queue *)malloc(sizeof(Queue));
  data->data = start;
  data->next = NULL;

  if (isEmpty(*queue))
    *queue = data;
  else {
    Queue *temp = *queue;
    while (temp->next != NULL) {
      temp = temp->next;
    }
    temp->next = data;
  }
}

void dequeue(Queue **head) {
  if (isEmpty(*head)) {
    return;
  }

  Queue *trash = *head;
  *head = trash->next;
  free(trash);
}

int front(Queue *queue) {
  if (queue == NULL)
    return 0;
  return queue->data;
}

void BFS(int start, int visited[], Edge *ajdList[]) {
  Queue *queue = NULL;

  visited[start] = 1;
  enqueue(&queue, start);

  while (!isEmpty(queue)) {
    int v = front(queue);
    printf("%d", v);
    dequeue(&queue);

    Edge *it;
    for (it = ajdList[v]; it != NULL; it = it->next) {
      if (!visited[it->dest]) {
        visited[it->dest] = 1;
        enqueue(&queue, it->dest);
      }
    }
  }
}

int main() {
  int i;
  int src, dest;
  int start;

  int V;

  printf("Jumlah Vertex = ");
  scanf("%d", &V);
  Edge *ajdList[V];

  for (i = 0; i < V; i++) {
    ajdList[i] = NULL;
  }

  i = 0;
  while (1) {
    printf("Ajacency List ke-%d", ++i);
    printf("Source: ");
    scanf("%d", &src);
    printf("Destinantion: ");
    scanf("%d", &dest);
    printf("\n");

    if (src <= -1 || dest <= -1)
      break;
    else {
      addEdge(ajdList, src, dest);
      addEdge(ajdList, dest, src);
    }
  }

  int visited[V + 2];
  for (i = 0; i < V + 2; i++) {
    visited[i] = 0;
  }

  printf("Starting Node: ");
  scanf("%d", &start);
  BFS(start, visited, ajdList);

  return 0;
}