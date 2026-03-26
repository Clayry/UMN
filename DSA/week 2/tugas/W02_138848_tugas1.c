#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STUDENTS 20

struct Student {
    char name[64];
    char major[32];
    float gpa;
};

void printLine() {
    printf("-----------------------------------------------------------------------\n");
}

void displayStudents(struct Student students[], int count) {
    printf("\n");
    printf("                      List of Student Information\n");
    printLine();
    printf("| No. |             Name              |         Major         |  GPA  |\n");
    printLine();
    
    if (count == 0) {
        printf("|                          No students in database                    |\n");
        printLine();
    } else {
        for (int i = 0; i < count; i++) {
            printf("| %-3d | %-29s | %-21s | %.2f  |\n", i + 1, students[i].name, students[i].major, students[i].gpa);
        }
        printLine();
    }
}

int main() {
    struct Student students[MAX_STUDENTS];
    int count = 0;
    int choice;
    
    do {
        printf("\nWELCOME TO SIMPLE STUDENT DATABASE (%d/%d)\n", count, MAX_STUDENTS);
        printf("1. Show All Students\n");
        printf("2. Input New Student\n");
        printf("3. Exit\n");
        printf("Choose: ");
        scanf("%d", &choice);
            switch (choice)
            {
            case 1:
                displayStudents(students, count);
                break;

            case 2:
                if (count >= MAX_STUDENTS)
                {
                    printf("Database is full");
                } else {
                    printf("\n===== INPUT NEW STUDENT =====\n");
                    printf("Student %d\n", count + 1);
                            
                    printf("Name    : ");
                    scanf(" %[^\n]", students[count].name);
                            
                    printf("Major   : ");
                    scanf(" %[^\n]", students[count].major);
                            
                    printf("GPA     : ");
                    scanf("%f", &students[count].gpa);
                            
                    count++;
                    printf("\nStudent added successfully!\n");
                }
                break;

            case 3:
                printf("\nThank you for using the database. Goodbye!\n");
                break;
                

            default:
                break;
            }
    } while (choice != 3);
    return 0;
}