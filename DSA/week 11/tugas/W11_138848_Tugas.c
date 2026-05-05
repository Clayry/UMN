#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void bubbleSort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] < arr[j + 1]) {
                swap(&arr[j], &arr[j + 1]);
            }
        }
    }
}

void insertionSort(int arr[], int n) {
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] < key) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}

void selectionSort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int min_idx = i;
        for (int j = i + 1; j < n; j++) {
            if (arr[j] > arr[min_idx]) {
                min_idx = j;
            }
        }
        swap(&arr[min_idx], &arr[i]);
    }
}

void radixSort(int arr[], int n) {
    int max = arr[0];
    for (int i = 1; i < n; i++) {
        if (arr[i] > max) {
            max = arr[i];
        }
    }

    for (int exp = 1; max / exp > 0; exp *= 10) {
        int output[n];
        int count[10] = {0};

        for (int i = 0; i < n; i++) {
            count[(arr[i] / exp) % 10]++;
        }

        for (int i = 8; i >= 0; i--) {
            count[i] += count[i + 1];
        }

        for (int i = n - 1; i >= 0; i--) {
            output[count[(arr[i] / exp) % 10] - 1] = arr[i];
            count[(arr[i] / exp) % 10]--;
        }

        for (int i = 0; i < n; i++) {
            arr[i] = output[i];
        }
    }
}

int main() {
    int arr[20];
    int n = sizeof(arr) / sizeof(arr[0]);

    do {
        printf("\n");
        srand(time(NULL));
        for (int i = 0; i < 20; i++) {
            arr[i] = rand() % 20;
            printf("%d ", arr[i]);
        }

        printf("\n");
        printf("Pilih Sort: \n");
        printf("1. BubbleSort\n");
        printf("2. InsertionSort\n");
        printf("3. SelectionSort\n");
        printf("4. RadixSort\n");
        printf("5. Keluar\n");
        int choice;
        scanf("%d", &choice);

        switch (choice) {
        case 1:
            bubbleSort(arr, n);
            break;
        case 2:
            insertionSort(arr, n);
            break;
        case 3:
            selectionSort(arr, n);
            break;
        case 4:
            radixSort(arr, n);
            break;
        case 5:
            return 0;
        default:
            printf("Pilihan tidak valid\n");
        }

        printf("Array setelah diurutkan: ");
        for (int i = 0; i < n; i++) {
            printf("%d ", arr[i]);
        }
        printf("\n");

    } while (n > 0);
    return 0;
}
