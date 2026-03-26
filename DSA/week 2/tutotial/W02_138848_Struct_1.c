#include <stdio.h>

struct Student{
    char name[50];
    char major[35];
    float gpa;
};

int main(){
    struct Student waldo = {"waldo", "Informatika", 3.98};

    printf("Name    : %s\n", waldo.name);
    printf("Major   : %s\n", waldo.major);
    printf("GPA     : %.2f\n", waldo.gpa);
    return 0;
}