#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct Student
{
    char name[100];
    char major [30];
    int nim;

    struct Student *next;
} Student;

void printLinkedList(Student *head){
    Student *current = head;
    while (current != NULL)
    {
        printf("Student ID  : %d\n", current->nim);
        printf("Name        : %d\n", current->name);
        printf("Major       : %d\n", current->major);
        printf("---------------------\n");

        current = current->next;
    }
}

Student* createNewNode(int id, char name[],char major[]){
    Student *newNode = (Student*) malloc(sizeof(Student));

    newNode->nim=id;
    strcpy(newNode->name, name);
    strcpy(newNode->major, major);
    newNode->next = NULL;

    return newNode;
}

int main(){
    Student *head, *node;
    head = NULL;

    node = (Student*) malloc (sizeof(Student));

    node->nim = 13531;
    strcpy(node->name, "Febe Febrita");
    strcpy(node->major, "Informatics");
    node->next=NULL;

    head = node;

    Student *tail;
    tail = node;

    node = createNewNode(11111, "Eliel", "Information Systems");

    tail->next = node;
    tail = node;

    node = createNewNode(22222, "Devi", "Informatics");
    node->next = head;
    head = node;

    printf("Data BEFORE deletion\n");
    printLinkedList(head);

    Student *temp, *prev;

    temp = head;
    
    while (strcmp(temp->next->name, "Febe Febrita") != 0)
    {
        printf("%s\n", temp->name);
        temp = temp->next;
    }
    
    if (temp->nim == head->nim)
        printf("true\n");
    else  
        printf("false\n");
    
    prev = temp;
    temp = temp->next;
    prev->next = temp->next;
    tail->next =NULL;
    free(temp);

    printf("Data AFTER deletion\n");
    printLinkedList(head);
    return 0;
}
