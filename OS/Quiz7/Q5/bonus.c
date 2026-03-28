#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

int total_kopi;
int sisa_kopi;
int skor[3] = {0, 0, 0};
pthread_mutex_t lock;

void *kontestan(void *arg) {
  int id = *(int *)arg;
  while (1) {
    pthread_mutex_lock(&lock);
    if (sisa_kopi <= 0) {
      pthread_mutex_unlock(&lock);
      break;
    }
    sisa_kopi--;
    skor[id]++;
    pthread_mutex_unlock(&lock);

    usleep(10000);
  }
  return NULL;
}

void *monitor(void *arg) {
  while (1) {
    pthread_mutex_lock(&lock);
    printf("\r[STATUS] Sisa Kopi: %d | K1: %d, K2: %d, K3: %d", sisa_kopi,
           skor[0], skor[1], skor[2]);
    fflush(stdout);
    if (sisa_kopi <= 0) {
      pthread_mutex_unlock(&lock);
      break;
    }
    pthread_mutex_unlock(&lock);
    usleep(50000);
  }
  printf("\nLomba Selesai!\n ");
  return NULL;
}

int main() {
  printf("Masukkan jumlah cangkir kopi ()\n");
  scanf("%d", &total_kopi);

  if (total_kopi <= 10 || total_kopi >= 200) {
    printf("Jumlah tidak valid!\n");
    return NULL;
  }

  sisa_kopi = total_kopi;
  pthread_t threads[4];
  int ids[3] = {0, 1, 2};
  pthread_mutex_init(&lock, NULL);

  for (int i = 0; i < 3; i++)
    pthread_create(&threads[i], NULL, kontestan, &ids[i]);
  pthread_create(&threads[3], NULL, monitor, NULL);

  for (int i = 0; i < 4; i++)
    pthread_join(threads[i], NULL);

  printf("\n--- HASIL AKHIR ---\n");
  for (int i = 0; i < 3; i++)
    printf("Kontestan %d: %d cangkir\n", i + 1, skor[i]);

  pthread_mutex_destroy(&lock);
  return 0;
}
