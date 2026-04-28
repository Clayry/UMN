#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Student {
  char nim[16];
  char nama[26];
  int score;
} Student;

typedef struct Node {
  Student data;
  struct Node *left, *right;
} Node;

Node *newNode(Student s) {
  Node *n = (Node *)malloc(sizeof(Node));
  n->data = s;
  n->left = n->right = NULL;
  return n;
}

Node *insert(Node *root, Student s) {
  if (root == NULL)
    return newNode(s);

  int cmp = strcmp(s.nim, root->data.nim);
  if (cmp < 0)
    root->left = insert(root->left, s);
  else if (cmp > 0)
    root->right = insert(root->right, s);
  else
    printf("  [!] NIM %s sudah ada, data duplikat diabaikan.\n", s.nim);

  return root;
}

Node *minNode(Node *root) {
  Node *cur = root;
  while (cur && cur->left)
    cur = cur->left;
  return cur;
}

Node *deleteNode(Node *root, const char *nim) {
  if (root == NULL)
    return root;

  int cmp = strcmp(nim, root->data.nim);

  if (cmp < 0)
    root->left = deleteNode(root->left, nim);
  else if (cmp > 0)
    root->right = deleteNode(root->right, nim);
  else {
    if (root->left == NULL) {
      Node *tmp = root->right;
      free(root);
      return tmp;
    } else if (root->right == NULL) {
      Node *tmp = root->left;
      free(root);
      return tmp;
    }
    Node *tmp = minNode(root->right);
    root->data = tmp->data;
    root->right = deleteNode(root->right, tmp->data.nim);
  }
  return root;
}

Node *search(Node *root, const char *nim) {
  if (root == NULL)
    return NULL;
  int cmp = strcmp(nim, root->data.nim);
  if (cmp == 0)
    return root;
  else if (cmp < 0)
    return search(root->left, nim);
  else
    return search(root->right, nim);
}

void printHeader() {
  printf("  %-16s %-26s %5s\n", "NIM", "Nama", "Score");
  printf("  %s\n", "--------------------------------------------------------");
}

void printNode(Node *n) {
  printf("  %-16s %-26s %5d\n", n->data.nim, n->data.nama, n->data.score);
}

void inorder(Node *root) {
  if (root == NULL)
    return;
  inorder(root->left);
  printNode(root);
  inorder(root->right);
}

void preorder(Node *root) {
  if (root == NULL)
    return;
  printNode(root);
  preorder(root->left);
  preorder(root->right);
}

void postorder(Node *root) {
  if (root == NULL)
    return;
  postorder(root->left);
  postorder(root->right);
  printNode(root);
}

void inputStudent(Student *s) {
  printf("  NIM   (maks 15 karakter) : ");
  scanf("%15s", s->nim);

  int c;
  while ((c = getchar()) != '\n' && c != EOF)
    ;

  printf("  Nama  (maks 25 karakter) : ");
  fgets(s->nama, sizeof(s->nama), stdin);
  s->nama[strcspn(s->nama, "\n")] = '\0';

  printf("  Score                    : ");
  scanf("%d", &s->score);
  while ((c = getchar()) != '\n' && c != EOF)
    ;
}

void freeTree(Node *root) {
  if (root == NULL)
    return;
  freeTree(root->left);
  freeTree(root->right);
  free(root);
}

int main() {
  Node *root = NULL;
  int choice;
  char nimBuf[16];

  printf("╔══════════════════════════════════════╗\n");
  printf("║   BST Mahasiswa  –  W09 Tugas 1      ║\n");
  printf("╚══════════════════════════════════════╝\n\n");

  do {
    printf("┌─ MENU ───────────────────────────────┐\n");
    printf("│  1. Insert data mahasiswa             │\n");
    printf("│  2. Delete data (by NIM)              │\n");
    printf("│  3. Search data (by NIM)              │\n");
    printf("│  4. Tampilkan Inorder  (urut NIM)     │\n");
    printf("│  5. Tampilkan Preorder                │\n");
    printf("│  6. Tampilkan Postorder               │\n");
    printf("│  0. Keluar                            │\n");
    printf("└───────────────────────────────────────┘\n");
    printf("Pilihan: ");
    scanf("%d", &choice);
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
      ;
    printf("\n");

    switch (choice) {
    case 1: {
      Student s;
      printf("-- Insert Data Mahasiswa --\n");
      inputStudent(&s);
      root = insert(root, s);
      printf("  [OK] Data berhasil dimasukkan.\n\n");
      break;
    }
    case 2: {
      printf("-- Delete Data --\n");
      printf("  NIM yang akan dihapus: ");
      scanf("%15s", nimBuf);
      int ch;
      while ((ch = getchar()) != '\n' && ch != EOF)
        ;
      if (search(root, nimBuf))
        root = deleteNode(root, nimBuf);
      else
        printf("  [!] NIM %s tidak ditemukan.\n", nimBuf);
      printf("\n");
      break;
    }
    case 3: {
      printf("-- Search Data --\n");
      printf("  NIM yang dicari: ");
      scanf("%15s", nimBuf);
      int ch;
      while ((ch = getchar()) != '\n' && ch != EOF)
        ;
      Node *found = search(root, nimBuf);
      if (found) {
        printf("  [FOUND]\n");
        printHeader();
        printNode(found);
      } else {
        printf("  [!] NIM %s tidak ditemukan.\n", nimBuf);
      }
      printf("\n");
      break;
    }
    case 4:
      printf("-- Inorder Traversal (urut NIM ascending) --\n");
      if (root) {
        printHeader();
        inorder(root);
      } else
        printf("  Tree kosong.\n");
      printf("\n");
      break;
    case 5:
      printf("-- Preorder Traversal --\n");
      if (root) {
        printHeader();
        preorder(root);
      } else
        printf("  Tree kosong.\n");
      printf("\n");
      break;
    case 6:
      printf("-- Postorder Traversal --\n");
      if (root) {
        printHeader();
        postorder(root);
      } else
        printf("  Tree kosong.\n");
      printf("\n");
      break;
    case 0:
      printf("Keluar. Sampai jumpa!\n");
      break;
    default:
      printf("  [!] Pilihan tidak valid.\n\n");
    }
  } while (choice != 0);

  freeTree(root);
  return 0;
}
