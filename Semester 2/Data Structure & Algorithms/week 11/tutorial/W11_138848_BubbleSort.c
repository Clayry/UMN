#include <stdio.h>
#include <stdlib.h>

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void bubbleSort(int *bil, int n) {
    int i, j;

    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - i - 1; j++) {
            if (bil[j] > bil[j + 1]) {
                swap(&bil[j], &bil[j + 1]);
            }
        }
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

    bubbleSort(bil, n);

    printf("Hasil bubble sort: \n");
    for (i = 0; i < n; i++) {
        printf("%d ", bil[i]);
    }

    free(bil);

    return 0;
}
