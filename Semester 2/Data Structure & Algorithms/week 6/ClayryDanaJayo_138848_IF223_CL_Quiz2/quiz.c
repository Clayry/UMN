#include <malloc.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Client {
    char name[50];
    char tipe[20];
    int jumlahTransaksi;
    char tanggal[12];
} Client;

typedef struct Node {
    Client data;
    struct Node *next;
    struct Node *prev;
} Node;

typedef struct Stack {
    Node *top;
} Stack;

void init(Stack *stack) { 
    stack->top = NULL; 
}

void push(Stack *stack, const char *name, const char *tipe, int jumlahTransaksi, const char *tanggal) {
    Node *newNode = (Node *)malloc(sizeof(Node));
    if (newNode == NULL) {
        printf("Memory Error\n");
        return;
    }

    strcpy(newNode->data.name, name);
    strcpy(newNode->data.tipe, tipe);
    newNode->data.jumlahTransaksi = jumlahTransaksi;
    strcpy(newNode->data.tanggal, tanggal);

    newNode->next = stack->top;
    newNode->prev = NULL;
    if (stack->top)
        stack->top->prev = newNode;
    stack->top = newNode;
}

void pop(Stack *stack) {
    if (stack->top == NULL) {
        printf("Tidak ada transaksi untuk dibatalkan.\n");
        return;
    }
    Node *temp = stack->top;
    stack->top = stack->top->next;
    if (stack->top) {
        stack->top->prev = NULL;
    }
    printf("Transaksi terakhir oleh %s berhasil dibatalkan.\n", temp->data.name);
    free(temp);
}

void loadFromFile(Stack *stack) {
    FILE *fp = fopen("atm_log.txt", "r");
    if (fp == NULL) return;

    char name[50], tipe[20], tanggal[12];
    int jumlah;
    Stack tempStack;
    init(&tempStack);

    while (fscanf(fp, " %[^#]#%[^#]#%d#%[^\n]\n", name, tipe, &jumlah, tanggal) == 4) {
        push(&tempStack, name, tipe, jumlah, tanggal);
    }
    fclose(fp);

    Node *cur = tempStack.top;
    while (cur) {
        push(stack, cur->data.name, cur->data.tipe, cur->data.jumlahTransaksi, cur->data.tanggal);
        cur = cur->next;
    }

    while (tempStack.top) {
        Node *temp = tempStack.top;
        tempStack.top = tempStack.top->next;
        free(temp);
    }
}

void saveToFile(Stack *stack) {
    FILE *fp = fopen("atm_log.txt", "w");
    if (fp == NULL) return;

    Node *cur = stack->top;
    Stack tempStack;
    init(&tempStack);

    while (cur) {
        push(&tempStack, cur->data.name, cur->data.tipe, cur->data.jumlahTransaksi, cur->data.tanggal);
        cur = cur->next;
    }

    cur = tempStack.top;
    while (cur) {
        fprintf(fp, "%s#%s#%d#%s\n", cur->data.name, cur->data.tipe, cur->data.jumlahTransaksi, cur->data.tanggal);
        cur = cur->next;
    }
    fclose(fp);

    while (tempStack.top) {
        Node *temp = tempStack.top;
        tempStack.top = tempStack.top->next;
        free(temp);
    }
}

void displayLog(Stack *stack) {
    if (stack->top == NULL) {
        printf("Riwayat transaksi kosong.\n");