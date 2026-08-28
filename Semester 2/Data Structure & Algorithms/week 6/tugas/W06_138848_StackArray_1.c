#include <malloc.h>
#include <stdbool.h>
#include <stdio.h>

#define MAX_SIZE 100

typedef struct {
  int arr[MAX_SIZE];
  int top;
} Stack;

void initialize(Stack *stack) { stack->top = -1; }

bool isEmpty(Stack *stack) { return stack->top == -1; }

bool isFull(Stack *stack) { return stack->top >= MAX_SIZE - 1; }

void push(Stack *stack, int value) {
  if (isFull(stack)) {
    printf("Stack Overflow\n");
    return;
  }
  stack->arr[++stack->top] = value;
  printf("Pushed %d onto the stack\n", value);
}

int pop(Stack *stack) {
  if (isEmpty(stack)) {
    printf("Stack Underflow");
    return -1;
  }

  int popped = stack->arr[stack->top];
  stack->top--;
  printf("Popped %d from the stack\n", popped);
  return popped;
}

int peek(Stack *stack) {
  if (isEmpty(stack)) {
    printf("Stack is empty\n");
    return -1;
  }
  return stack->arr[stack->top];
}

void display(Stack *stack){
  if (isEmpty(stack)) {
    printf("Stack is empty\n");
  } else {
    printf("Stack : \n");
    for (int i = stack->top; i>=0; i--) {
      printf("%d", stack->arr[i]);
    }
  }
}

int main() {
  Stack stack;
  initialize(&stack);
  int choice;
  int num;
  do {
    printf("---------MENU----------\n");
    printf("1. Push\n");
    printf("2. Pop\n");
    printf("3. isFull\n");
    printf("4. isEmpty\n");
    printf("5. Peek\n");
    printf("6. Clear Stack\n");
    printf("7. Display stack\n");
    printf("8. Exit\n");
    scanf("%d", &choice);

    switch (choice) {
    case 1:
      printf("What number you want to push: ");
      scanf("%d", &num);

      push(&stack, num);
      break;

    case 2:
      pop(&stack);
      break;

    case 3:
      if (isFull(&stack) == true) {
        printf("Stack is full\n");
      } else {
        printf("Stack is not full\n");
      }
      break;
    case 4:
      if (isEmpty(&stack)) {
        printf("Stack is empty\n");
      } else {
        printf("Stack isn't empty\n");
      }
      break;
    case 5:
      printf("Top is %d\n", peek(&stack));
      break;
    case 6:
      initialize(&stack);
      break;
    case 7:
      display(&stack);
      break;
    case 8:
      printf("EXIT\n");
    default:
      printf("Error enter valid number\n");
    }
  } while (choice != 8);

  return 0;
}
