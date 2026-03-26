#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

void run_loop(const char *name) {
  printf("\n[%s] starting  PID=%d  PPID=%d\n\n", name, getpid(), getppid());
  for (int i = 1; i <= 5; i++) {
    printf("[%s] loop %d/5  PID=%d  PPID=%d\n", name, i, getpid(), getppid());
    sleep(1);
  }
  printf("\n[%s] exiting   PID=%d\n\n", name, getpid());
}

pid_t spawn(void (*child_fn)(void)) {
  pid_t pid = fork();
  if (pid < 0) {
    perror("fork");
    exit(EXIT_FAILURE);
  }
  if (pid == 0) {
    child_fn();
    exit(EXIT_SUCCESS);
  }
  return pid; /* parent receives child PID */
}

void reap(pid_t pid, const char *parent_name) {
  int status;
  pid_t done = waitpid(pid, &status, 0);
  if (done == -1) {
    perror("waitpid");
    exit(EXIT_FAILURE);
  }
  if (WIFEXITED(status))
    printf("[%s] child %d exited with status %d\n", parent_name, done,
           WEXITSTATUS(status));
}

void process_D(void) { run_loop("D"); }

void process_E(void) { run_loop("E"); }

void process_B(void) {
  printf("\n[B] starting  PID=%d  PPID=%d\n\n", getpid(), getppid());

  pid_t pid_D = spawn(process_D);
  pid_t pid_E = spawn(process_E);

  /* B also does its own work */
  for (int i = 1; i <= 5; i++) {
    printf("[B] loop %d/5  PID=%d  PPID=%d\n", i, getpid(), getppid());
    sleep(1);
  }

  reap(pid_D, "B");
  reap(pid_E, "B");

  printf("\n[B] exiting   PID=%d\n\n", getpid());
}

void process_C(void) { run_loop("C"); }

int main(void) {
  printf("\n[A] starting  PID=%d  PPID=%d\n\n", getpid(), getppid());

  pid_t pid_B = spawn(process_B);
  pid_t pid_C = spawn(process_C);

  /* A also does its own work */
  for (int i = 1; i <= 5; i++) {
    printf("[A] loop %d/5  PID=%d  PPID=%d\n", i, getpid(), getppid());
    sleep(1);
  }

  reap(pid_B, "A");
  reap(pid_C, "A");

  printf("\n[A] exiting   PID=%d\n\n", getpid());
  return EXIT_SUCCESS;
}
