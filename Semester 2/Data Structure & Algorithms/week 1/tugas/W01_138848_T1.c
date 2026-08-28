#include <stdio.h>
#include <ctype.h>

void display(){
    printf("1. Uppercase\n");
    printf("2. Lowercase\n");
    printf("3. Switching\n");
    printf("4. Keluar\n");

    int choice;
    scanf("%d", &choice);
    printf("Masukkan Kata: \n");
    char word[64];
    getchar();
    fgets(word, sizeof(word), stdin);

    switch (choice)
    {
    case 1:
        for (size_t i = 0; word[i] != '\0'; i++)
        {
            word[i] = toupper(word[i]);
        }
        printf("%s", word);
        break;
    
    case 2:
        for (size_t i = 0; word[i] != '\0'; i++)
        {
            word[i] = tolower(word[i]);
        }
        printf("%s", word);
        break;

    case 3:
        for (size_t i = 0; word[i] != '\0'; i++)
        {
        if (islower(word[i])) {
            word[i] = toupper(word[i]);
        }
        else if (isupper(word[i])) {
            word[i] = tolower(word[i]);
        }
        }
        printf("%s", word);
        break;

    case 4:
        break;
    default:
        break;
    }
}
int main(){
    display();
    return 0;
}