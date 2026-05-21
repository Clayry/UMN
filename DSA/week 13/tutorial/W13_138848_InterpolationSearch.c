#include <stdio.h>

int interpolationSearch(int *arr, int size, int key) {
    int low, pos, high;

    low = 0;
    high = size - 1;
    printf("sizeof arr = %d\n", high);

    do {
        pos = ((key - arr[low]) * (high - low) / (arr[high] - arr[low])) + low;

        if (arr[pos] == key)
            return pos;
        if (arr[pos] > key)
            high = pos - 1;
        else
            low = pos + 1;
    } while (key >= arr[low] && key <= arr[high]);

    return -1;
}

void shellSort(int *arr, int size) {
    int gap, i, j, temp;

    for (gap = size / 2; gap > 0; gap /= 2) {
        for (i = gap; i < size; i++) {
            temp = arr[i];
            for (j = i; j >= gap && arr[j - gap] > temp; j -= gap) {
                arr[j] = arr[j - gap];
            }
            arr[j] = temp;
        }
    }
}

void printArray(int *arr, int size) {
    int i = 0;

    for (i = 0; i < size; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

int main() {
    int numbers[] = {2, 4, 3, 123, 23, 56, 7895, 456, 342, 67, 2345};
    int size = sizeof(numbers) / 4;
    int searchKey;
    int found = 0;

    printf("Array before sorting: ");
    printArray(numbers, size);
    shellSort(numbers, size);
    printf("Array after sorting: ");
    printArray(numbers, size);

    printf("Masukkan angka yang ingin dicari: ");
    scanf("%d", &searchKey);

    found = interpolationSearch(numbers, size, searchKey);

    if (found != -1) {
        printf("Angka %d ditemukan pada index %d", searchKey, found);
    } else {
        printf("Angka %d tidak ditemukan pada array numbers", searchKey);
    }

    return 0;
}
