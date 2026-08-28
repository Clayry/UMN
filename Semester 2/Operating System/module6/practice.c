#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define NUM_PHIL 5
#define SLEEP_TIME 2

pthread_mutex_t forks[NUM_PHIL];

void *philosopher(void *num) {
  int id = *(int *)num;
  int left_fork = id;
  int right_fork = (id + 1) % NUM_PHIL;

  while (1) {
    printf("philosopher %d is thinking.\n", id);
    sleep(rand() % SLEEP_TIME);
    printf("Philosopher %d is HUNGRY. \n", id);
    if (id == NUM_PHIL - 1) {
      pthread_mutex_lock(&forks[right_fork]);
      pthread_mutex_lock(&forks[left_fork]);
    } else {
      pthread_mutex_lock(&forks[left_fork]);
      pthread_mutex_lock(&forks[right_fork]);
    }

    printf("Philosopher %d picked up both forks and is EATING. \n", id);
    sleep(rand() % SLEEP_TIME);

    pthread_mutex_unlock(&forks[right_fork]);
    pthread_mutex_unlock(&forks[left_fork]);
    printf("Philosopher %d finished eating and put down forks.\n", id);
  }
}

int main() {
  pthread_t phils[NUM_PHIL];
  int phil_ids[NUM_PHIL];

  for (int i = 0; i < NUM_PHIL; i++) {
    pthread_mutex_init(&forks[i], NULL);
  }

  for (int i = 0; i < NUM_PHIL; i++) {
    phil_ids[i] = i;
    pthread_create(&phils[i], NULL, philosopher, &phil_ids[i]);
  }

  for (int i = 0; i < NUM_PHIL; i++) {
    pthread_join(phils[i], NULL);
  }

  return 0;
}
