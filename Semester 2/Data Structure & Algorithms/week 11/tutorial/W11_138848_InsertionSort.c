#include <stdio.h>
#include <stdlib.h>

void insertionSort(int *bil, int n) {
    int i, j, temp;
    for (i = 1; i < n; i++) {
        temp = bil[i];

        for (j = i - 1; j >= 0 && bil[j] > temp; j--) {
            bil[j + 1] = bil[j];
        }
        bil[j + 1] = temp;
    }
}

int main() {
    int i, n, *bil;

    printf("Banyak Bilangan: ");
    scanf("%d", &n);
    bil = malloc(sizeof(int) * n);

    for (i = 0; i < n; i++) {
        printf("Input Bilangan ke-%d: ", i + 1);
        scanf("%d", &bil[i]);
    }

    insertionSort(bil, n);

    printf("Hasil insertion sort: \n");
    for (i = 0; i < n; i++) {
        printf("%d ", bil[i]);
    }

    free(bil);

    return 0;
}
