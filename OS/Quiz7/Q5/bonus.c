#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#define NUM_CONTESTANTS 3

int cups_remaining;
int race_over = 0;

pthread_mutex_t mutex_cups = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutex_print = PTHREAD_MUTEX_INITIALIZER;

typedef struct {
  int id;
  char name[16];
  int cups_drunk;
} Contestant;

Contestant contestants[NUM_CONTESTANTS] = {
    {0, "Andi", 0},
    {1, "Budi", 0},
    {2, "Cici", 0},
};

void *contestant_thread(void *arg) {
  Contestant *c = (Contestant *)arg;

  while (1) {
    pthread_mutex_lock(&mutex_cups);
    if (cups_remaining <= 0) {
      pthread_mutex_unlock(&mutex_cups);
      break;
    }

    cups_remaining--;
    c->cups_drunk++;
    int sisa = cups_remaining;
    int diminum = c->cups_drunk;

    pthread_mutex_unlock(&mutex_cups);

    pthread_mutex_lock(&mutex_print);
    printf("[%-4s] Minum cangkir ke-%d | Sisa Cangkir: %d\n", c->name, diminum,
           sisa);
    fflush(stdout);
    pthread_mutex_unlock(&mutex_print);

    struct timespec ts;
    ts.tv_sec = 0;
    ts.tv_nsec = (100 + rand() % 301) * 1000000L;
    nanosleep(&ts, NULL);
  }

  pthread_mutex_lock(&mutex_print);
  printf("[%-4s] Selesai! Total diminum lagi: %d cangkir\n", c->name,
         c->cups_drunk);
  fflush(stdout);
  pthread_mutex_unlock(&mutex_print);

  return NULL;
}

void *status_thread(void *arg) {
  (void)arg;

  while (1) {
    sleep(1);

    pthread_mutex_lock(&mutex_cups);
    int sisa = cups_remaining;
    int done = race_over;
    pthread_mutex_unlock(&mutex_cups);

    pthread_mutex_lock(&mutex_print);
    printf("\n--- [STATUS] Cangkir tersisa: %d | ", sisa);
    for (int i = 0; i < NUM_CONTESTANTS; i++) {
      printf("%s: %d", contestants[i].name, contestants[i].cups_drunk);
    }
    printf("---\n\n ");
    fflush(stdout);
    pthread_mutex_unlock(&mutex_print);

    if (done || sisa <= 0) {
      break;
    }
  }
  return NULL;
}

int cmp_desc(const void *a, const void *b) {
  const Contestant *ca = (const Contestant *)a;
  const Contestant *cb = (const Contestant *)b;
  return cb->cups_drunk - ca->cups_drunk;
}

int main() {
  srand(time(NULL));

  int n;
  printf("=== LOMBA MINUM KOPI ===\n ");
  printf("Masukkan jumlah cangkir kopi (10 < n < 200)");
  fflush(stdout);

  if (scanf("%d", &n) != 1 || n <= 10 || n >= 200) {
    printf("Input tidak valid! Harus 10 < n < 200\n");
    return 1;
  }

  cups_remaining = n;

  printf("\nLomba dimulai! %d cangkir kopi tersedia.\n", n);
  printf("Peserta: Andi, Budi, Cici\n");
  printf("==========================================\n\n");
  fflush(stdout);

  pthread_t tid_contestant[NUM_CONTESTANTS];
  pthread_t tid_status;

  pthread_create(&tid_status, NULL, status_thread, NULL);
  for (int i = 0; i < NUM_CONTESTANTS; i++) {
    pthread_create(&tid_contestant[i], NULL, contestant_thread,
                   &contestants[i]);
  }

  for (int i = 0; i < NUM_CONTESTANTS; i++) {
    pthread_join(tid_contestant[i], NULL);
  }

  pthread_mutex_lock(&mutex_cups);
  race_over = 1;
  pthread_mutex_unlock(&mutex_cups);

  pthread_join(tid_status, NULL);

  Contestant ranking[NUM_CONTESTANTS];
  memcpy(ranking, contestants, sizeof(contestants));
  qsort(ranking, NUM_CONTESTANTS, sizeof(Contestant), cmp_desc);

  printf("\n===========================================\n");
  printf("         HASIL AKHIR LOMBA MINUM KOPI\n");
  printf("\n===========================================\n");

  const char *medals[] = {"JUARA 1", "JUARA 2", "JUARA 3"};
  for (int i = 0; i < NUM_CONTESTANTS; i++) {
    printf("%s : %-4s - %d cangkir\n", medals[i], ranking[i].name,
           ranking[i].cups_drunk);
  }

  printf("=====================================\n");
  printf("Total cangkir diminum: %d/%d\n",
         ranking[0].cups_drunk + ranking[1].cups_drunk + ranking[2].cups_drunk,
         n);

  pthread_mutex_destroy(&mutex_cups);
  pthread_mutex_destroy(&mutex_print);

  return 0;
}
