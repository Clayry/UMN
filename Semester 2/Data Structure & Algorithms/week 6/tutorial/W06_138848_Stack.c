#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>

// #1 Prepare the Struct data type that will be used
// As the base of the stack
typedef struct Student{
    char nim[13];
    char name[50];
    char major[30];

    // Don't forget to prepare a pointer to access
    // data inside the Stack
    struct Student *next;
} Student;


// #2 Create four functions for basic Stack operations
// The order of creation is: isEmpty, push, pop, top

// #2.1 Create the isEmpty function
int isEmpty(Student *stack){

    // Check whether the stack has elements
    if (stack == NULL)
        return 1; // 1 if the stack is empty
    return 0;     // 0 if the stack has elements
}


// #2.2 Create the push function. Used to insert data into the Stack
void push(Student **stack, char nim[], char name[], char major[]){
    Student *data = (Student*) malloc(sizeof(Student));
    strcpy(data->nim, nim);
    strcpy(data->name, name);
    strcpy(data->major, major);
    data->next = NULL;

    if (!isEmpty(*stack)) data->next = *stack;
    *stack = data;

    printf("Adding %s to Stack\n", name);
}


// #2.3 Create the pop function. Used to remove data from the Stack
void pop(Student **stack){
    printf("Removing Stack's top element\n");

    if (*stack == NULL){ // Check whether the stack is empty or not
        // If it is already empty, there is nothing left to pop
        printf("Nothing to pop. Stack already empty\n");
        return;
    }

    // trash is used to store the data that will be removed
    Student *trash = *stack;
    *stack = trash->next;
    free(trash);

    printf("Popping Stack success\n");
}


int main(){
    printf("STACK TUTORIAL\n");
    printf("-------------\n\n");
    printf("Initializing Stack\n\n");
    Student *stackMhs; // stackMhs as the main Stack
    stackMhs = NULL;   // Initialize the Stack as empty

    printf("Is Stack empty? %s\n", isEmpty(stackMhs) ? "Yes" : "No");
    printf("What is the name at the top? %s\n",
        stackMhs==NULL ? "No one. Stack is empty" : stackMhs->name
    );

    push(&stackMhs, "11111", "Febe Febrita", "Informatics");
    printf("What is the name at the top? %s\n",
        stackMhs==NULL ? "No one. Stack is empty" : stackMhs->name
    );

    printf("Is Stack empty? %s\n\n", isEmpty(stackMhs) ? "Yes" : "No");

    pop(&stackMhs);
    printf("Is Stack empty? %s\n", isEmpty(stackMhs) ? "Yes" : "No");
    printf("What is the name at the top? %s\n",
        stackMhs==NULL ? "No one. Stack is empty" : stackMhs->name
    );

    push(&stackMhs, "22222", "Emilio", "Electrical Engineering");
    push(&stackMhs, "33333", "Valdo", "Information Systems");
    push(&stackMhs, "44444", "Evan", "Engineering Physics");

    printf("What is the name at the top? %s\n",
        stackMhs==NULL ? "No one. Stack is empty" : stackMhs->name
    );

    pop(&stackMhs);
    printf("What is the name at the top? %s\n",
        stackMhs==NULL ? "No one. Stack is empty" : stackMhs->name
    );

    pop(&stackMhs);
    printf("What is the name at the top? %s\n",
        stackMhs==NULL ? "No one. Stack is empty" : stackMhs->name
    );

    pop(&stackMhs);
    printf("\n");
    pop(&stackMhs);

    return 0;
}