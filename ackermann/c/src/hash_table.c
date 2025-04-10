#include <stdlib.h>

#include "hash_table.h"

/**
 * Compares 'p1' to 'p2'. Returns 0 if they are identical, 1 otherwise.
 */
int _keycmp(key p1, key p2);

/**
 * Hashes 'key' for insertion in a hash_table with a capacity of 'size'
 * elements.
 */
uint64_t _keyhash(key key, size_t size);

hash_table *hash_table_create(size_t size) {
  hash_table *ht;
  ht = malloc(sizeof(hash_table));
  if (ht == NULL)
    return NULL;
  ht->size = size;
  ht->table = (entry **)calloc(size, sizeof(entry *));
  if (ht->table == NULL) {
    free(ht);
    return NULL;
  }
  return ht;
}

void hash_table_destroy(hash_table *ht) {
  /* Since we make no assumptions about our clients data, freeing individual
   * table entries is up to the user.
   */
  free(ht->table);
  free(ht);
}

entry *hash_table_insert(hash_table *ht, key key, entry *v) {
  if (ht == NULL || v == NULL)
    return NULL;
  uint64_t index = _keyhash(key, ht->size);
  entry *tmp = ht->table[index];
  ht->table[index] = v;
  if (tmp == NULL)
    return v;
  return tmp;
}

entry *hash_table_delete(hash_table *ht, key key) {
  if (ht == NULL)
    return NULL;
  uint64_t idx = _keyhash(key, ht->size);
  if (ht->table[idx] != NULL && _keycmp(ht->table[idx]->key, key) == 0) {
    entry *tmp = ht->table[idx];
    ht->table[idx] = NULL;
    return tmp;
  }
  return NULL;
}

entry *hash_table_lookup(hash_table *ht, key key) {
  uint64_t index = _keyhash(key, ht->size);
  if (ht->table[index] != NULL && _keycmp(ht->table[index]->key, key) == 0)
    return ht->table[index];
  return NULL;
}

void hash_table_print(hash_table *ht) {
  printf("\tHash\t---\tEntry\t\n");
  size_t i;
  for (i = 0; i < ht->size; i++) {
    if (ht->table[i] == NULL) {
      printf("\t%ld\t---\n", i);
    } else {
      entry *a = ht->table[i];
      printf("\t%ld\t---\t(%ld, %ld)=>%ld\t\n", i, a->key.m, a->key.n,
             a->value);
    }
  }
  printf("\n");
}

uint64_t _keyhash(key key, size_t size) {
  uint64_t m = key.m;
  uint64_t n = key.n;
  return ((((m + n + 1) * (m + n)) / 2) + n) % size;
}

int _keycmp(key k1, key k2) {
  if (k1.m == k2.m && k1.n == k2.n)
    return 0;
  return 1;
}
