#include <stdio.h>

int main() {
    int numbers[] = {2, 4, 3, 123, 23, 56, 7895, 456, 342, 67, 2345};
    int size = sizeof(numbers);
    int searchKey;
    int found;
    int i;

    printf("Masukkan angka yang ingin dicari: ");
    scanf("%d", &searchKey);

    for (i = 0; i < size; i++) {
        if (searchKey == numbers[i]) {
            found = 1;
            break;
        }
    }

    if (found) {
        printf("Angka %d ditemukan pada index %d", searchKey, i);
    } else {
        printf("Angka %d tidak ditemukan pada array numbers", searchKey);
    }

    return 0;
}
