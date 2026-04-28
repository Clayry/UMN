#include <stdio.h>
#include <stdlib.h>

void lru(int *pages, int max_frames, int num_pages) {
  int *frames;
  int *last_access; 
  int page_faults = 0;
  int current_time = 0; 
  frames = (int *)malloc(max_frames * sizeof(int));
  last_access = (int *)malloc(max_frames * sizeof(int));
  for (int i = 0; i < max_frames; i++) {
    frames[i] = -1;
    last_access[i] = 0;
  }
  printf("Page\tFrames\t\tStatus\n");
  for (int i = 0; i < num_pages; i++) {
    int current_page = pages[i];
    int found = 0;
    current_time++; 
    for (int j = 0; j < max_frames; j++) {
      if (frames[j] == current_page) {
        found = 1;
        last_access[j] =
            current_time; 
        break;
      }
    }

    if (!found) {
      int replace_idx = -1;
      for (int j = 0; j < max_frames; j++) {
        if (frames[j] == -1) {
          replace_idx = j;
          break;
        }
      }
      
      if (replace_idx == -1) {
        int min_time = last_access[0];
        replace_idx = 0;
        for (int j = 1; j < max_frames; j++) {
          if (last_access[j] < min_time) {
            min_time = last_access[j];
            replace_idx = j;
          }
        }
      }
      frames[replace_idx] = current_page;
      last_access[replace_idx] = current_time;
      page_faults++;
    }
    printf("%d\t", current_page);
    for (int j = 0; j < max_frames; j++) {
      if (frames[j] != -1)
        printf("%d ", frames[j]);
      else
        printf("- ");
    }
    if (!found)
      printf("\tPF");
    printf("\n");
  }
  printf("Total Page Faults: %d\n", page_faults);
  free(frames);
  free(last_access);
}
int main(int argc, char *argv[]) {
  int max_frames, max_length;
  int *pageref_string;
  int i = 0, n;
  FILE *fp;
  if (argc != 4) {
    printf("Use: ./lru #frames #max_length string_file\n");
    exit(2);
  }
  max_frames = atoi(argv[1]);
  max_length = atoi(argv[2]);
  pageref_string = (int *)malloc(max_length * sizeof(int));
  fp = fopen(argv[3], "r");
  if (fp == NULL) {
    printf("File tidak ditemukan!\n");
    exit(1);
  }
  while (fscanf(fp, "%d", &(pageref_string[i++])) != EOF)
    ;
  n = i - 1;
  fclose(fp);
  lru(pageref_string, max_frames, n);
  free(pageref_string);
  return 0;
}
