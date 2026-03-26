#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Song {
  char singer[100];
  char album[100];
  char title[100];
  int year;

  struct Song *next;
  struct Song *prev;
} Song;

Song *makeNode(const char *singer, const char *album, const char *title,
               int year) {
  Song *n = (Song *)malloc(sizeof(Song));
  strcpy(n->singer, singer);
  strcpy(n->album, album);
  strcpy(n->title, title);
  n->year = year;
  n->next = n->prev = NULL;
  return n;
}

void appendNode(Song **head, Song **tail, Song *newNode) {
  if (*tail == NULL) {
    *head = *tail = newNode;
  } else {
    newNode->prev = *tail;
    (*tail)->next = newNode;
    *tail = newNode;
  }
}

void freeList(Song **head, Song **tail) {
  Song *curr = *head;
  while (curr != NULL) {
    Song *tmp = curr->next;
    free(curr);
    curr = tmp;
  }
  *head = *tail = NULL;
}

void menu1(Song **head, Song **tail) {
  freeList(head, tail);

  FILE *fp = fopen("playlist.txt", "r");
  if (fp == NULL) {
    printf("Error: playlist.txt not found!\n");
    return;
  }

  char line[400];
  while (fgets(line, sizeof(line), fp)) {
    line[strcspn(line, "\r\n")] = '\0';
    if (strlen(line) == 0)
      continue;

    char singer[100], album[100], title[100];
    int year;

    char *token = strtok(line, "*");
    if (!token)
      continue;
    strcpy(singer, token);

    token = strtok(NULL, "*");
    if (!token)
      continue;
    strcpy(album, token);

    token = strtok(NULL, "*");
    if (!token)
      continue;
    strcpy(title, token);

    token = strtok(NULL, "*");
    if (!token)
      continue;
    year = atoi(token);

    appendNode(head, tail, makeNode(singer, album, title, year));
  }
  fclose(fp);

  printf("\n%-20s %-30s %-25s %s\n", "Singer", "Song Title", "Album",
         "Released Year");
  printf("%-20s %-30s %-25s %s\n", "------", "----------", "-----",
         "-------------");

  Song *curr = *head;
  while (curr != NULL) {
    printf("%-20s %-30s %-25s %d\n", curr->singer, curr->title, curr->album,
           curr->year);
    curr = curr->next;
  }
  printf("\n");
}

void menu2(Song **head, Song **tail) {
  char singer[100], album[100], title[100];
  int year;

  printf("\nInput Singer      : ");
  fgets(singer, sizeof(singer), stdin);
  singer[strcspn(singer, "\r\n")] = '\0';

  printf("Album             : ");
  fgets(album, sizeof(album), stdin);
  album[strcspn(album, "\r\n")] = '\0';

  printf("Title             : ");
  fgets(title, sizeof(title), stdin);
  title[strcspn(title, "\r\n")] = '\0';

  printf("Released Year     : ");
  scanf("%d", &year);
  while (getchar() != '\n')
    ;

  appendNode(head, tail, makeNode(singer, album, title, year));

  FILE *fp = fopen("playlist.txt", "w");
  if (fp == NULL) {
    printf("Error: cannot open playlist.txt for writing!\n");
    return;
  }
  Song *curr = *head;
  while (curr != NULL) {
    fprintf(fp, "%s*%s*%s*%d\n", curr->singer, curr->album, curr->title,
            curr->year);
    curr = curr->next;
  }
  fclose(fp);

  printf("Data berhasil ditambahkan!\n\n");
}

void menu3(Song **head, Song **tail) {
  if (*tail == NULL) {
    printf("List is already empty!\n\n");
    return;
  }

  char deletedTitle[100];
  strcpy(deletedTitle, (*tail)->title);

  Song *trash = *tail;
  if (*head == *tail) {
    *head = *tail = NULL;
  } else {
    *tail = trash->prev;
    (*tail)->next = NULL;
  }
  free(trash);

  FILE *fp = fopen("playlist.txt", "w");
  if (fp != NULL) {
    Song *curr = *head;
    while (curr != NULL) {
      fprintf(fp, "%s*%s*%s*%d\n", curr->singer, curr->album, curr->title,
              curr->year);
      curr = curr->next;
    }
    fclose(fp);
  }

  printf("Lagu %s berhasil dihapus dari list.\n\n", deletedTitle);
}

int main() {
  Song *head = NULL;
  Song *tail = NULL;
  int choice;

  do {
    printf("===== PLAYLIST MENU =====\n");
    printf("1. Tampilkan data\n");
    printf("2. Tambah data\n");
    printf("3. Hapus data\n");
    printf("4. Exit\n");
    printf("Pilihan : ");
    scanf("%d", &choice);
    while (getchar() != '\n')
      ;
    printf("\n");

    switch (choice) {
    case 1:
      menu1(&head, &tail);
      break;
    case 2:
      menu2(&head, &tail);
      break;
    case 3:
      menu3(&head, &tail);
      break;
    case 4:
      freeList(&head, &tail);
      printf("Program selesai. Memory berhasil dibebaskan.\n");
      break;
    default:
      printf("Pilihan tidak valid!\n\n");
    }
  } while (choice != 4);

  return 0;
}
