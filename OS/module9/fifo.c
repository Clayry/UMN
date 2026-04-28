#include <stdio.h>
#include <stdlib.h>

void fifo(int pages[], int max_frames, int num_pages) {
  int *frames;
  int page_faults = 0, next_frame = 0;
  frames = (int *)malloc(max_frames * sizeof(int));
  for (int i = 0; i < max_frames; i++)
    frames[i] = -1;
  for (int i = 0; i < num_pages; i++) {
    int current_page = pages[i];
    int found = 0;
    for (int j = 0; j < max_frames; j++) {
      if (frames[j] == current_page) {
        found = 1;
        break;
      }
    }
    if (!found) {
      frames[next_frame] = current_page;
      next_frame = (next_frame + 1) % max_frames;
      page_faults++;
    }
    printf("%d -> [", current_page);
    for (int j = 0; j < max_frames; j++) {
      frames[j] != -1 ? printf(" %d ", frames[j]) : printf(" - ");
    }
    printf("]");
    if (!found)
      printf("   PF");
    printf("\n");
  }
  printf("Total Page Faults: %d\n", page_faults);
  free(frames);
}

int main(int argc, char *argv[]) {
  int max_frames, max_length;
  int *pageref_string;
  int i, n;
  FILE *fp;
  if (argc != 4) {
    printf("Use: ./fifo #frames #max_length string_file\n");
    exit(2);
  }
  max_frames = atoi(argv[1]);
  max_length = atoi(argv[2]);
  pageref_string = (int *)malloc(max_length * sizeof(int));
  fp = fopen(argv[3], "r");
  i = 0;
  while (fscanf(fp, "%d", &(pageref_string[i++])) != EOF)
    ;
  n = i - 1;
  fclose(fp);
  fifo(pageref_string, max_frames, n);
  free(pageref_string);
  return 0;
}
