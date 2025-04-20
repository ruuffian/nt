#include <stdlib.h>

#include "hash_table.h"

/**
 * Compares 'p1' to 'p2'. Returns 0 if they are identical, 1 otherwise.
 */
int _tuplecmp(tuple p1, tuple p2);

/**
 * Hashes 'key' for insertion in a hash_table with a capacity of 'size'
 * elements.
 */
uint64_t _hash(tuple key, size_t size);

hash_table *ht_create(size_t size) {
  hash_table *ht;
  ht = malloc(sizeof(hash_table));
  if (ht == NULL)
    return NULL;
  ht->size = size;
  ht->table = (record **)calloc(size, sizeof(record *));
  if (ht->table == NULL) {
    free(ht);
    return NULL;
  }
  return ht;
}

void ht_destroy(hash_table *ht) {
  size_t i;
  for (i = 0; i < ht->size; i++) {
    free(ht->table[i]);
  }
  free(ht->table);
  free(ht);
}

record *ht_insert(hash_table *ht, tuple key, record *r) {
  if (ht == NULL || r == NULL)
    return NULL;
  uint64_t index = _hash(key, ht->size);
  record *tmp = ht->table[index];
  ht->table[index] = r;
  if (tmp == NULL)
    return r;
  return tmp;
}

record *ht_lookup(hash_table *ht, tuple key) {
  uint64_t index = _hash(key, ht->size);
  if (ht->table[index] != NULL && _tuplecmp(ht->table[index]->key, key) == 0)
    return ht->table[index];
  return NULL;
}

void ht_print(hash_table *ht) {
  printf("\tHash\t---\tEntry\t\n");
  size_t i;
  for (i = 0; i < ht->size; i++) {
    if (ht->table[i] == NULL) {
      printf("\t%ld\t---\n", i);
    } else {
      record *e = ht->table[i];
      printf("\t%ld\t---\t(%ld, %ld)=>%ld\t\n", i, e->key.m, e->key.n,
             e->value);
    }
  }
  printf("\n");
}

uint64_t _hash(tuple key, size_t size) {
  uint64_t m = key.m;
  uint64_t n = key.n;
  return ((((m + n + 1) * (m + n)) / 2) + n) % size;
}

int _tuplecmp(tuple k1, tuple k2) {
  if (k1.m == k2.m && k1.n == k2.n)
    return 0;
  return 1;
}
