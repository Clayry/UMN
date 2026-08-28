#include <stdio.h>

void inputMatrix(int matrix[3][3], char name) {
    printf("Masukkan elemen matriks %c (3x3):\n", name);
    for(int i = 0; i < 3; i++) {
        for(int j = 0; j < 3; j++) {
            printf("Elemen [%d][%d]: ", i, j);
            scanf("%d", &matrix[i][j]);
        }
    }
}

void displayMatrix(int matrix[3][3], char *name) {
    printf("\n%s:\n", name);
    for(int i = 0; i < 3; i++) {
        for(int j = 0; j < 3; j++) {
            printf("%4d ", matrix[i][j]);
        }
        printf("\n");
    }
}

void addMatrix(int A[3][3], int B[3][3], int result[3][3]) {
    for(int i = 0; i < 3; i++) {
        for(int j = 0; j < 3; j++) {
            result[i][j] = A[i][j] + B[i][j];
        }
    }
}

void multiplyMatrix(int A[3][3], int B[3][3], int result[3][3]) {
    for(int i = 0; i < 3; i++) {
        for(int j = 0; j < 3; j++) {
            result[i][j] = 0;
            for(int k = 0; k < 3; k++) {
                result[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

void transposeMatrix(int matrix[3][3], int result[3][3]) {
    for(int i = 0; i < 3; i++) {
        for(int j = 0; j < 3; j++) {
            result[j][i] = matrix[i][j];
        }
    }
}

int main() {
    int A[3][3], B[3][3];
    int sum[3][3], product[3][3];
    int transposeA[3][3], transposeB[3][3];

    inputMatrix(A, 'A');
    printf("\n");
    
    inputMatrix(B, 'B');
    
    displayMatrix(A, "Matriks A");
    displayMatrix(B, "Matriks B");
    
    printf("\n");
    printf("1. Perkalian Dua Buah Matrix\n");
    printf("2. Penjumlahan Dua Buah Matrix\n");
    printf("3. Transpose Dua Buah Matrix\n");
    printf("4. Keluar\n");
    printf("Pilihan: ");

    int choice;
    scanf("%d", &choice);

    switch (choice)
    {
    case 1:
        multiplyMatrix(A, B, product);
        displayMatrix(product, "Perkalian");
        break;
    case 2:
        addMatrix(A, B, sum);
        displayMatrix(sum, "Penjumlahan");
    case 3:
        transposeMatrix(A, transposeA);
        transposeMatrix(B, transposeB);
        displayMatrix(transposeA, "Transpose Matriks A");
        displayMatrix(transposeB, "Transpose Matriks B");
        break;
    case 4:
        break;

    default:
        break;
    }
    return 0;
}