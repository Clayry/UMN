#include <stdio.h>
#include <stdlib.h>

void swap(int *a, int *b) {
  int temp = *a;
  *a = *b;
  *b = temp;
}

int partition(int *bil, int l, int r) {
  int pivor = bil[r];
  int i = l - 1;

  for (int j = l; j <= r - 1; j++) {
    if (bil[j] < pivor) {
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

int main() {
  int i, n, *bil;

  printf("Banyak bulangan: ");
  scanf("%d", &n);
  bil = malloc(sizeof(int) * n);

  for (i = 0; i < n; i++) {
    printf("Input bulangan ke-%d: ", i + 1);
    scanf("%d", &bil[i]);
  }

  quickSort(bil, 0, n - 1);

  printf("Hasill quick sort: \n");
  for (i = 0; i < n; i++) {
    printf("%d ", bil[i]);
  }

  free(bil);
  return 0;
}
