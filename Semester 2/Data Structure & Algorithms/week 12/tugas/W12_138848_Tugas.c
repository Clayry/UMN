#include <stdio.h>
#include <stdlib.h>

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

int heapify(int *bil, int n, int i) {
    int maks = i;
    int l = 2 * i + 1;
    int r = 2 * i + 2;
    if (l < n && bil[l] > bil[maks])
        maks = l;
    if (r < n && bil[r] > bil[maks])
        maks = r;
    if (maks != i) {
        swap(&bil[i], &bil[maks]);
        heapify(bil, n, maks);
    }
    return 0;
}

int heapSort(int *bil, int n) {
    int i;
    for (i = n / 2 - 1; i >= 0; i--)
        heapify(bil, n, i);
    for (i = n - 1; i > 0; i--) {
        swap(&bil[0], &bil[i]);
        heapify(bil, i, 0);
    }
    for (int l = 0, r = n - 1; l < r; l++, r--)
        swap(&bil[l], &bil[r]);
    return 0;
}

void merge(int *bil, int l, int m, int r) {
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;
    int L[n1], R[n2];
    for (i = 0; i < n1; i++)
        L[i] = bil[l + i];
    for (j = 0; j < n2; j++)
        R[j] = bil[m + 1 + j];
    i = 0;
    j = 0;
    k = l;
    while (i < n1 && j < n2) {
        if (L[i] >= R[j]) {
            bil[k] = L[i];
            i++;
        } else {
            bil[k] = R[j];
            j++;
        }
        k++;
    }
    while (i < n1) {
        bil[k++] = L[i++];
    }
    while (j < n2) {
        bil[k++] = R[j++];
    }
}

void mergeSort(int *bil, int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;
        mergeSort(bil, l, m);
        mergeSort(bil, m + 1, r);
        merge(bil, l, m, r);
    }
}

int partition(int *bil, int l, int r) {
    int pivor = bil[r];
    int i = l - 1;
    for (int j = l; j <= r - 1; j++) {
        if (bil[j] > pivor) {
            i++;
            swap(&bil[i], &bil[j]);
        }
    }
    swap(&bil[i + 1], &bil[r]);
    return (i + 1);
}

void quickSort(int *bil, int l, int r) {
    if (l < r) {
        int pi = partition(bil, l, r);
        quickSort(bil, l, pi - 1);
        quickSort(bil, pi + 1, r);
    }
}

void shellSort(int *bil, int n) {
    int i, j, gap;
    for (gap = n / 2; gap > 0; gap /= 2) {
        for (i = gap; i < n; i++) {
            int temp = bil[i];
            for (j = i; j >= gap && bil[j - gap] < temp; j -= gap)
                bil[j] = bil[j - gap];
            bil[j] = temp;
        }
    }
}

void printArray(int *bil, int n) {
    for (int i = 0; i < n; i++)
        printf("%d ", bil[i]);
    printf("\n");
}

int main() {
    int n, i, choice;

    printf("Masukkan jumlah bilangan: ");
    scanf("%d", &n);

    do {
        int *bil = (int *)malloc(n * sizeof(int));
        for (i = 0; i < n; i++) {
            printf("Input bilangan ke-%d: ", i + 1);
            scanf("%d", &bil[i]);
        }

        printf("1. HeapSort\n");
        printf("2. MergeSort\n");
        printf("3. QuickSort\n");
        printf("4. ShellSort\n");
        printf("5. Keluar\n");
        printf("Pilih Sort: ");
        scanf("%d", &choice);

        switch (choice) {
        case 1:
            heapSort(bil, n);
            printf("Hasil heap sort:\n");
            printArray(bil, n);
            break;
        case 2:
            mergeSort(bil, 0, n - 1);
            printf("Hasil merge sort:\n");
            printArray(bil, n);
            break;
        case 3:
            quickSort(bil, 0, n - 1);
            printf("Hasil quick sort:\n");
            printArray(bil, n);
            break;
        case 4:
            shellSort(bil, n);
            printf("Hasil shell sort:\n");
            printArray(bil, n);
            break;
        case 5:
            printf("Keluar.\n");
            break;
        default:
            printf("Pilihan tidak valid.\n");
        }

        free(bil);
    } while (choice != 5);

    return 0;
}
