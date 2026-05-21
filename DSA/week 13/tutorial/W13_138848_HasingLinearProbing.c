#include <stdbool.h>
#include <stdio.h>

void hashFunction(int input, int hashTable[]);

int main() {
    int HashT[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    int inputKey;

    while (1) {
        printf("Input a number: ");
        scanf("%d", &inputKey);
        printf("Processing in Hash Function\n");

        hashFunction(inputKey, HashT);

        int i;
        printf("Current Hash Table: ");
        for (i = 0; i < 10; i++) {
            printf("[%d]", HashT[i]);
        }
        printf("\n\n");
    }

    return 0;
}

void hashFunction(int input, int hashTable[]) {
    int hash;
    bool check = false;
    hash = input % 10;
    int temp = hash;
    while (1) {
        if (hashTable[temp] == 0) {
            printf("Inserting data to Hash Table\n");
            hashTable[temp] = input;
            break;
        }
        temp++;
        if (hash == temp) {
            printf("HashTable Full\n");
            break;
        }
        if (temp > 9) {
            temp = 0;
        }
    }
}
