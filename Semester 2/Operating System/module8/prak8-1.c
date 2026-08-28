
#include <stdio.h>
#include <stdlib.h>

int global_var = 10;
int unitialized_global_var;

void func1(int param) {
  int local_var = 20;
  printf("Address of local_var (stack): %p\n", (void *)&local_var);
  printf("Address of function parameter (Stack): %p\n", (void *)&param);
}

void func2(int param) {
  static int local_var = 50;
  printf("Address of static local_var (static): %p\n", (void *)&local_var);
  printf("Address of function parameter (stack): %p\n", (void *)&param);
}

int main() {
  int main_local_var = 30;
  char *heap_ptr = malloc(50 * sizeof(char));
  printf("Location of main() code : %p\n", main);
  printf("Location of func1() code : %p\n", func1);
  printf("Location of func2() code : %p\n", func2);
  printf("Address of global_var (data_segment): %p\n", (void *)&global_var);
  printf("Address of unitialized_global_var (BSS segment): %p\n",
         (void *)&unitialized_global_var);
  printf("Address of main_local_var (stack): %p\n", (void *)&main_local_var);
  printf("Address of heap_ptr (stack, pointer value points to heap): %p\n",
         (void *)&heap_ptr);
  printf("Address of memory allocated on heap: %p\n", (void *)heap_ptr);
  func1(100);
  func2(200);
  func2(300);
  free(heap_ptr);
  return 0;
}
