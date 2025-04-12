#include <stdlib.h>

#include "hash_table.h"

/**
 * Compares 'p1' to 'p2'. Returns 0 if they are identical, 1 otherwise.
 */
int _keycmp(key_t p1, key_t p2);

/**
 * Hashes 'key' for insertion in a hash_table with a capacity of 'size'
 * elements.
 */
uint64_t _keyhash(key_t key, size_t size);

hash_table_t *hash_table_create(size_t size) {
  hash_table_t *ht;
  ht = malloc(sizeof(hash_table_t));
  if (ht == NULL)
    return NULL;
  ht->size = size;
  ht->table = (entry_t **)calloc(size, sizeof(entry_t *));
  if (ht->table == NULL) {
    free(ht);
    return NULL;
  }
  return ht;
}

void hash_table_destroy(hash_table_t *ht) {
  size_t i;
  for (i = 0; i < ht->size; i++) {
    free(ht->table[i]);
  }
  free(ht->table);
  free(ht);
}

entry_t *hash_table_insert(hash_table_t *ht, key_t key, entry_t *e) {
  if (ht == NULL || e == NULL)
    return NULL;
  uint64_t index = _keyhash(key, ht->size);
  entry_t *tmp = ht->table[index];
  ht->table[index] = e;
  if (tmp == NULL)
    return e;
  return tmp;
}

entry_t *hash_table_delete(hash_table_t *ht, key_t key) {
  if (ht == NULL)
    return NULL;
  uint64_t idx = _keyhash(key, ht->size);
  if (ht->table[idx] != NULL && _keycmp(ht->table[idx]->key, key) == 0) {
    entry_t *tmp = ht->table[idx];
    ht->table[idx] = NULL;
    return tmp;
  }
  return NULL;
}

entry_t *hash_table_lookup(hash_table_t *ht, key_t key) {
  uint64_t index = _keyhash(key, ht->size);
  if (ht->table[index] != NULL && _keycmp(ht->table[index]->key, key) == 0)
    return ht->table[index];
  return NULL;
}

void hash_table_print(hash_table_t *ht) {
  printf("\tHash\t---\tEntry\t\n");
  size_t i;
  for (i = 0; i < ht->size; i++) {
    if (ht->table[i] == NULL) {
      printf("\t%ld\t---\n", i);
    } else {
      entry_t *e = ht->table[i];
      printf("\t%ld\t---\t(%ld, %ld)=>%ld\t\n", i, e->key.m, e->key.n,
             e->value);
    }
  }
  printf("\n");
}

uint64_t _keyhash(key_t key, size_t size) {
  uint64_t m = key.m;
  uint64_t n = key.n;
  return ((((m + n + 1) * (m + n)) / 2) + n) % size;
}

int _keycmp(key_t k1, key_t k2) { return (k1.m == k2.m && k1.n == k2.n); }
