#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *next;
} Node;

Node *stack = NULL;

int isEmpty() {
    return stack == NULL;
}

void push(int value) {
    Node *newNode = (Node*) malloc(sizeof(Node));
    if (newNode == NULL) {
        printf("Memory allocation failed!\n");
        return;
    }
    newNode->data = value;
    newNode->next = stack;
    stack = newNode;
    printf("Pushed %d to stack.\n", value);
}

void pop() {
    if (isEmpty()) {
        printf("Stack is empty! Nothing to pop.\n");
        return;
    }
    Node *trash = stack;
    printf("Popped: %d\n", trash->data);
    stack = stack->next;
    free(trash);
}

void peek() {
    if (isEmpty()) {
        printf("Stack is empty! No top element.\n");
        return;
    }
    printf("Top element: %d\n", stack->data);
}

void clearStack() {
    while (!isEmpty()) {
        Node *trash = stack;
        stack = stack->next;
        free(trash);
    }
    printf("Stack has been cleared.\n");
}

void printMenu() {
    printf("\n===== STACK MENU (Linked List) =====\n");
    printf("1. Push\n");
    printf("2. Pop\n");
    printf("3. IsEmpty\n");
    printf("4. Peek\n");
    printf("5. Clear Stack\n");
    printf("6. Exit\n");
    printf("Choose option: ");
}

int main() {
    int choice, value;

    do {
        printMenu();
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter integer to push: ");
                scanf("%d", &value);
                push(value);
                break;
            case 2:
                pop();
                break;
            case 3:
                printf("Stack is %s.\n", isEmpty() ? "EMPTY" : "NOT empty");
                break;
            case 4:
                peek();
                break;
            case 5:
                clearStack();
                break;
            case 6:
                clearStack();
                printf("Exiting program. Goodbye!\n");
                break;
            default:
                printf("Invalid option. Please try again.\n");
        }
    } while (choice != 6);

    return 0;
}