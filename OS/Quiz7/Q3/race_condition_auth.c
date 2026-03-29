#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define LOG_FILE "auth_log.txt"
#define NUM_USERS 2

typedef struct {
  char username[32];
  char password[32];
  int auth_result;
  int logged_in;
} AuthData;

AuthData users[NUM_USERS] = {{"alice", "pass123", 0, 0},
                             {"bob", "wrongpw", 0, 0}};

const char *correct_user[] = {"alice", "bob"};
const char *correct_pass[] = {"pass123", "pass456"};

void *verify_thread(void *arg) {
  int idx = *(int *)arg;
  free(arg);

  printf("[VERIFY] Memulai verifikasi untuk user: %s\n", users[idx].username);
  fflush(stdout);

  sleep(1);

  int valid = 0;
  for (int i = 0; i < NUM_USERS; i++) {
    if (strcmp(users[idx].username, correct_user[i]) == 0 &&
        strcmp(users[idx].password, correct_pass[i]) == 0) {
      valid = 1;
      break;
    }
  }

  users[idx].auth_result = valid;

  printf("[VERIFY] Verifikasi %s: %s\n", users[idx].username,
         valid ? "SUSKES" : "GAGAL");
  fflush(stdout);

  return NULL;
}

void *logging_thread(void *arg) {
  int idx = *(int *)arg;
  free(arg);

  printf("[LOG] Mencatat login untuk user: %s (auth_result saat ni: %d)\n",
         users[idx].username, users[idx].auth_result);
  fflush(stdout);

  FILE *fp = fopen(LOG_FILE, "a");
  if (fp == NULL) {
    perror("fopen log");
    return NULL;
  }

  fprintf(fp, "User: %-10s | Status: %s\n", users[idx].username,
          users[idx].auth_result ? "LOGIN_SUCESS" : "LOGIN_FAILED");
  fflush(fp);
  fclose(fp);

  users[idx].logged_in = 1;

  printf("[LOG] Selesai mencatat untuk user: %s\n", users[idx].username);
  fflush(stdout);

  return NULL;
}

int main() {
  pthread_t verify_tid[NUM_USERS];
  pthread_t logging_tid[NUM_USERS];

  remove(LOG_FILE);

  printf("=== Sistem Autentikasi (WITH Race Condition) ===\n");
  printf("2 User login bersamaan...\n\n");
  fflush(stdout);

  for (int i = 0; i < NUM_USERS; i++) {
    int *idx_v = malloc(sizeof(int));
    int *idx_1 = malloc(sizeof(int));
    *idx_v = i;
    *idx_1 = i;

    pthread_create(&verify_tid[i], NULL, verify_thread, idx_v);
    pthread_create(&logging_tid[i], NULL, logging_thread, idx_1);
  }

  for (int i = 0; i < NUM_USERS; i++) {
    pthread_join(verify_tid[i], NULL);
    pthread_join(logging_tid[i], NULL);
  }

  printf("\n=== Isi File Log %s\n", LOG_FILE);
  FILE *fp = fopen(LOG_FILE, "r");
  if (fp) {
    char line[128];
    while (fgets(line, sizeof(line), fp)) {
      printf("%s", line);
    }
    fclose(fp);
  }

  printf("\n[PERHATIAN] Log mungkin TIDAK AKURAT karena race condition\n");
  return 0;
}
