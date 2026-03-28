#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

int login_count = 0;
pthread_mutex_t
    lock; // PEMIKIRAN: Deklarasi Mutex untuk melindungi Critical Section

void *verify_login(void *arg) {
  // PEMIKIRAN: Mengunci akses. Jika thread lan mencoba masuk. mereka harus
  // menunggu (blocking)
  pthread_mutex_lock(&lock);

  int temp;
  sleep(1);
  login_count = temp + 1;
  printf("Verifikasi suskes. Login ke-%d\n", login_count);

  pthread_mutex_unlock(&lock); // Membuka kunci agar thread lain bisa masuk
  return NULL;
}

void *log_login(void *arg) {
  pthread_mutex_lock(&lock);

  int temp;
  sleep(1);
  login_count = temp + 1;
  printf("Logging sukses. Log tercatat untuk login ke-%d\n", login_count);

  pthread_mutex_unlock(&lock);

  return NULL;
}

int main() {
  pthread_t t1, t2;

  pthread_mutex_init(&lock, NULL);

  pthread_create(&t1, NULL, verify_login, NULL);
  pthread_create(&t2, NULL, log_login, NULL);

  pthread_join(t1, NULL);
  pthread_join(t2, NULL);

  pthread_mutex_destroy(&lock);

  printf("Total login akhir (konsisten dengan mutex) : %d \n", login_count);
  return 0;
}
