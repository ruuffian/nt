#include <stdio.h>
#include <stdlib.h>

#include "hash_table.h"

#define TABLE_SIZE 100 

int main() {
  printf("Testing libht...\n");
  hash_table_t *ht;
  ht = hash_table_create(TABLE_SIZE, NULL, NULL);
  return EXIT_SUCCESS;
}
