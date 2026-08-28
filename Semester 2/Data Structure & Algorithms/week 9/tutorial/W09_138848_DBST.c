#include <malloc.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
  int key;
  struct Node *left, *right;
} Node;

Node *newNode(int item) {
  Node *temp = (Node *)malloc(sizeof(Node));
  temp->key = item;
  temp->left = temp->right = NULL;
  return temp;
}

Node *insert(Node *node, int key) {
  if (node == NULL)
    return newNode(key);

  if (key < node->key)
    node->left = insert(node->left, key);
  else if (key > node->key)
    node->right = insert(node->right, key);

  return node;
}

void printPreorder(Node *node) {
  if (node == NULL)
    return;
  printf("%d ", node->key);
  printPreorder(node->left);
  printPreorder(node->right);
}

void printInorder(Node *node) {
  if (node == NULL)
    return;
  printInorder(node->left);
  printf("%d ", node->key);
  printInorder(node->right);
}

void printPostorder(Node *node) {
  if (node == NULL)
    return;
  printPostorder(node->left);
  printPostorder(node->right);
  printf("%d ", node->key);
}

Node *minValueNode(Node *node) {
  Node *current = node;
  while (current && current->left != NULL)
    current = current->left;
  return current;
}

Node *deleteNode(Node *root, int key) {
  if (root == NULL)
    return root;

  if (key < root->key)
    root->left = deleteNode(root->left, key);

  else if (key > root->key)
    root->right = deleteNode(root->right, key);

  else {
    if (root->left == NULL) {
      Node *temp = root->right;
      free(root);
      return temp;
    } else if (root->right == NULL) {
      Node *temp = root->left;
      free(root);
      return temp;
    }

    Node *temp = minValueNode(root->right);

    root->key = temp->key;

    root->right = deleteNode(root->right, temp->key);
  }
  return root;
}

int main() {
  Node *root = NULL;

  root = insert(root, 50);
  insert(root, 50);
  insert(root, 30);
  insert(root, 20);
  insert(root, 40);
  insert(root, 70);
  insert(root, 60);
  insert(root, 80);

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
