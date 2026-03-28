#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

int login_count = 0; // PEMIKIRAN: Shared resource yang akan diakses bersamaan

void *verfiy_login(void *arg) {
  int temp = login_count;
  sleep(1); // PEMIKIRAN: Jeda ini memaksa context switch, memastikan race
            // condition terjadi
  login_count = temp + 1;
  printf("Verifikasi sukses. Login ke-%d", login_count);
  return NULL;
}

void *log_login(void *arg) {
  int temp = login_count;
  sleep(1);
  login_count = temp + 1;
  printf("Logging suskes. log tercata untuk login ke-%d\b", login_count);
  return NULL;
}

int main() {
  pthread_t t1, t2;

  // PEMIKIRAN: Dua thread mengakses dan memodifikasi login_count di waktu yang
  // hampir bersamaan tanpa mekanisme sinkronisasi. Hasil akhir login_count akan
  // tidak konsisten (kemungkinan bernilai 1, bukan 2)

  pthread_create(&t1, NULL, verfiy_login, NULL);
  pthread_create(&t2, NULL, log_login, NULL);

  pthread_join(t1, NULL);
  pthread_join(t2, NULL);

  printf("Total login akhir (Seharusnya 2, tapi karena race condition "
         "menjadi): %d\n",
         login_count);
  return 0;
}
