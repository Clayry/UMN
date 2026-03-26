#include <malloc.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  char name[50];
  char tanggal[12];
  int jumlahTransaksi;
} Client;

typedef struct {
  Client data;
  struct Node *next;
  struct Node *prev;
} Node;

typedef struct {
  Node *top;
} Stack;

void init(Stack *stack) { stack->top = NULL; }

void push(Stack *stack, const char *name, const char *tanggal,
          int jumlahTransaksi) {
  Node *newNode = (Node *)malloc(sizeof(Node));
  if (newNode == NULL) {
    printf("Memory Error\n`");
    return;
  }

  strcpy(newNode->data.name, name);
  strcpy(newNode->data.tanggal, tanggal);
  newNode->data.jumlahTransaksi = jumlahTransaksi;

  newNode->next = stack->top;
  newNode->prev = NULL;
  if (stack->top)
    stack->top->prev = newNode;
  stack->top = newNode;
}

void saveToFile(Stack *stack) {
  FILE *fp = fopen("atm_log.txt", "a");

  Node *cur = stack->top;
  while (cur) {
    Client t = cur->data;
    fprintf(fp, "%s#%s#d#s\n", t.name, t.tanggal, t.jumlahTransaksi);
    cur = cur->next;
  }

  fclose(fp);
}

int main() {
  char name[50];
  char tanggal[12];
  int jumlahTransaksi;
  int choice;
  Stack s = {0};
  init(&s);

  do {
    printf("==== ATM TRANSACTION LOG ====\n");
    printf("1. Tambah transaksi baru\n");
    printf("2. Tampilkan seluruh riwayat transaksi\n");
    printf("3. Batalkan transaksi terakhir\n");
    printf("4. Exit\n");
    printf("Pilih Menu: ");
    scanf("%d", &choice);

    switch (choice) {
    case 1:
      printf("Name : \n");
      fgets(name, sizeof(name), stdin);
      name[strcspn(name, "\n")] = 0;

      printf("Tanggal : \n");
      fgets(tanggal, sizeof(tanggal), stdin);
      tanggal[strcspn(tanggal, "\n")] = 0;

      printf("Jumlah transaksi : \n");
      scanf("%d", &jumlahTransaksi);
      getchar();

      push(&s, name, tanggal, jumlahTransaksi);
      break;

    case 2:
    case 3:
    case 4:
      printf("EXITING\n");

    default:
      break;
    }
  } while (choice != 4);
  return 0;
}
