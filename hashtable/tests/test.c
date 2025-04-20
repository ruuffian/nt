#include <stdio.h>
#include <stdlib.h>

#include "hash_table.h"

#define TABLE_SIZE 8
#define LOOPS 20

struct data {
  int a;
  char *b;
} data;

void cleanup_data(void *);

int main() {
  printf("Testing libht...\n");
  /** Testing struct with cleanup function */
  hash_table *ht;
  ht = hash_table_create(TABLE_SIZE, &cleanup_data);
  for (int i = 0; i < LOOPS; i++) {
    struct data *data = malloc(sizeof(struct data));
    if (data == NULL) {
      printf("Memory allocation failed.\n");
      abort();
      /* NOT REACHED */
    }
    data->a = i;
    data->b = calloc(5, sizeof(char));
    char key[20];
    sprintf(key, "[%d|%d]", i, i % 3);
    entry *tmp = hash_table_insert(ht, key, data);
    if (tmp == NULL)
      printf("%d-th Insertion failed.\n", i);
  }
  hash_table_print(ht);
  hash_table_destroy(ht);
  printf("Test complete!");
  return EXIT_SUCCESS;
}

void cleanup_data(void *d) {
  struct data *data = (struct data *)d;
  free(data->b);
  free(data);
}
