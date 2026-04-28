#include <malloc.h>
#include <stdio.h>
#include <stdlib.h>

// ── Struct Node (tambahan field height) ──────────────────────
typedef struct Node {
  int key, height;
  struct Node *left, *right;
} Node;

// ── Function untuk menghitung tinggi Tree ────────────────────
int height(struct Node *N) {
  if (N == NULL)
    return 0;
  return N->height;
}

// ── Function untuk mencari nilai terbesar ────────────────────
int max(int a, int b) { return (a > b) ? a : b; }

// ── Buat node baru ───────────────────────────────────────────
Node *newNode(int item) {
  Node *temp = (Node *)malloc(sizeof(Node));
  temp->key = item;
  temp->left = temp->right = NULL;
  temp->height = 1; // node baru selalu leaf, height = 1
  return temp;
}

// ── Left Rotate: putar ke kiri subtree dengan nilai x ────────
Node *leftRotate(Node *x) {
  Node *y = x->right;
  Node *T2 = y->left;

  // Perform rotation
  y->left = x;
  x->right = T2;

  // Update heights
  x->height = max(height(x->left), height(x->right)) + 1;
  y->height = max(height(y->left), height(y->right)) + 1;

  // Return new root
  return y;
}

// ── Right Rotate: putar ke kanan subtree dengan nilai y ──────
Node *rightRotate(Node *y) {
  Node *x = y->left;
  Node *T2 = x->right;

  // Perform rotation
  x->right = y;
  y->left = T2;

  // Update heights
  y->height = max(height(y->left), height(y->right)) + 1;
  x->height = max(height(x->left), height(x->right)) + 1;

  // Return new root
  return x;
}

// ── Mengambil nilai balance suatu node ───────────────────────
int getBalance(Node *N) {
  if (N == NULL)
    return 0;
  return height(N->left) - height(N->right);
}

// ── Insert (BST + AVL balancing) ─────────────────────────────
Node *insert(Node *node, int key) {
  /* 1. Lakukan insertion seperti BST */
  if (node == NULL)
    return newNode(key);

  if (key < node->key)
    node->left = insert(node->left, key);
  else if (key > node->key)
    node->right = insert(node->right, key);
  else
    return node; // Equal keys tidak diizinkan di BST

  /* 2. Update height (tinggi) node sekarang */
  node->height = 1 + max(height(node->left), height(node->right));

  /* 3. Hitung Balance Factor untuk menentukan
        apakah Tree ini merupakan Tree yang balance */
  int balance = getBalance(node);

  // Ada 4 case saat Tree tidak balance:

  // Left Left Case
  if (balance > 1 && key < node->left->key)
    return rightRotate(node);

  // Right Right Case
  if (balance < -1 && key > node->right->key)
    return leftRotate(node);

  // Left Right Case
  if (balance > 1 && key > node->left->key) {
    node->left = leftRotate(node->left);
    return rightRotate(node);
  }

  // Right Left Case
  if (balance < -1 && key < node->right->key) {
    node->right = rightRotate(node->right);
    return leftRotate(node);
  }

  return node;
}

// ── Traversal ────────────────────────────────────────────────
void printInorder(Node *node) {
  if (node == NULL)
    return;
  printInorder(node->left);
  printf("%d ", node->key);
  printInorder(node->right);
}

void printPreorder(Node *node) {
  if (node == NULL)
    return;
  printf("%d ", node->key);
  printPreorder(node->left);
  printPreorder(node->right);
}

void printPostorder(Node *node) {
  if (node == NULL)
    return;
  printPostorder(node->left);
  printPostorder(node->right);
  printf("%d ", node->key);
}

// ── minValueNode (dipakai deleteNode) ────────────────────────
Node *minValueNode(Node *node) {
  Node *current = node;
  /* looping ke node terbawah di kiri */
  while (current && current->left != NULL)
    current = current->left;
  return current;
}

// ── Delete node + rebalance ───────────────────────────────────
Node *deleteNode(Node *root, int key) {
  // base case
  if (root == NULL)
    return root;

  // Kalau key lebih kecil dari root, pindah ke kiri
  if (key < root->key)
    root->left = deleteNode(root->left, key);

  // Kalau key lebih besar dari root, pindah ke kanan
  else if (key > root->key)
    root->right = deleteNode(root->right, key);

  // Kalau key sama dengan root
  else {
    // node dengan 1 anak / tanpa anak
    if (root->left == NULL) {
      Node *temp = root->right;
      free(root);
      return temp;
    } else if (root->right == NULL) {
      Node *temp = root->left;
      free(root);
      return temp;
    }

    // node dengan 2 anak
    // ambil key terkecil di bawahnya
    Node *temp = minValueNode(root->right);

    // Copy nilai terkecilnya ke root
    root->key = temp->key;

    // Delete nilai terkecilnya
    root->right = deleteNode(root->right, temp->key);
  }
  return root;
}

// ── main ─────────────────────────────────────────────────────
int main() {
  Node *root = NULL;

  root = insert(root, 50);
  root = insert(root, 30);
  root = insert(root, 20);
  root = insert(root, 40);
  root = insert(root, 70);
  root = insert(root, 60);
  root = insert(root, 80);

  printf("Base Tree\n");
  printf("Preorder  : ");
  printPreorder(root);
  printf("\n");
  printf("Inorder   : ");
  printInorder(root);
  printf("\n");
  printf("Postorder : ");
  printPostorder(root);
  printf("\n\n");

  printf("Deleting node 20\n");
  root = deleteNode(root, 20);
  printf("Preorder  : ");
  printPreorder(root);
  printf("\n");
  printf("Inorder   : ");
  printInorder(root);
  printf("\n");
  printf("Postorder : ");
  printPostorder(root);
  printf("\n\n");

  printf("Deleting node 30\n");
  root = deleteNode(root, 30);
  printf("Preorder  : ");
  printPreorder(root);
  printf("\n");
  printf("Inorder   : ");
  printInorder(root);
  printf("\n");
  printf("Postorder : ");
  printPostorder(root);
  printf("\n\n");

  printf("Deleting node 70\n");
  root = deleteNode(root, 70);
  printf("Preorder  : ");
  printPreorder(root);
  printf("\n");
  printf("Inorder   : ");
  printInorder(root);
  printf("\n");
  printf("Postorder : ");
  printPostorder(root);
  printf("\n\n");

  return 0;
}
