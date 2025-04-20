#include <stdio.h>
#include <stdlib.h>

int count_lines(char *file);

int main() {
  printf("Hello world!\n");
  return 0;
}

int count_lines(char *file) {
  FILE *fp;
  fp = fopen(file, "r");
  if (fp == NULL) {
    fprintf(stderr, "Failed to open %s.\n", file);
    abort();
    /* NOT REACHED */
  }
  fclose(fp);
  return 0;
}
