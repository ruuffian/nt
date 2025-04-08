#include <stdbool.h>
#include "libht.h"

#define TABLE_SIZE 50

void assert(bool, char*, char*);
bool TEST_table_allocation(hash_table *);
bool TEST_table_size(hash_table *, size_t);
bool TEST_fresh_table_empty(hash_table *);
bool TEST_insert_succeeds(hash_table *);

int tests_passed = 0;
int tests_failed = 0;

int main() {
  hash_table *table;
  table = hash_table_create(TABLE_SIZE);
  /*
  assert(TEST_table_allocation(table), "Table successfully created.", "Table creation failed.");
  assert(TEST_table_size(table, TABLE_SIZE), "Table size matches.", "Table size does not match.");
  assert(TEST_fresh_table_empty(table), "Fresh table is empty.", "Fresh table is not empty.");
  */
  pair key = {.m=2, .n=10};
  ack tmp = {.pair=key, .value=23};
  ack tmp1 = {.pair=key, .value=23};
  ack tmp2 = {.pair=key, .value=23};
  ack tmp3 = {.pair=key, .value=23};
  ack tmp4 = {.pair=key, .value=23};
  hash_table_insert(table, key, &tmp);
  hash_table_insert(table, key, &tmp1);
  hash_table_insert(table, key, &tmp2);
  hash_table_insert(table, key, &tmp3);
  hash_table_insert(table, key, &tmp4);
  print_hash_table(table);
  return 0;
}

bool TEST_table_allocation(hash_table *t) {
  return t != NULL;
}

bool TEST_table_size(hash_table *t, size_t size) {
  return t->size == size;
}

bool TEST_fresh_table_empty(hash_table *t) {
  size_t i;
  for (i=0; i < t->size; i++) {
    if (t->table[i] != NULL) return false;
  }
  return true;
}

void assert(bool result, char *success, char *failed) {
  if (result) {
      printf("%s\n", success);
      tests_passed++;
  } else {
      printf("%s\n", failed);
      tests_failed++;
  }
}
