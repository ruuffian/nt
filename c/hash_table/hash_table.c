#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "hash_table.h"

/**
 * Compares 'p1' to 'p2'. Returns 0 if they are identical, 1 otherwise.
 */
int _pair_cmp(pair p1, pair p2);

/**
  * Hashes 'key' for insertion in a hash_table with a capacity of 'size'
  * elements.
  */
unsigned int _hash(pair key, size_t size); 

hash_table *hash_table_create(size_t size) {
  hash_table *ht;
  ht = malloc(sizeof(hash_table));
  if (ht == NULL) return NULL;
  ht->size = size;
  ht->table = (ack **)calloc(size, sizeof(ack *));
  if (ht->table == NULL) {
    free(ht);
    return NULL;
  }
  return ht;
}

void hash_table_destroy(hash_table *ht) {
  free(ht->table);
  free(ht);
}

bool hash_table_insert(hash_table *ht, pair key, ack *value) {
  if (ht == NULL || value == NULL) return false;
  int index = _hash(key, ht->size);
  if (ht->table[index] != NULL) {
    return false;
  }
  ht->table[index] = value;
  return true;
}

ack *hash_table_delete(hash_table *ht, pair pair) {
  if (ht == NULL) return NULL;
  int index = _hash(pair, ht->size);
  if (ht->table[index] != NULL &&
    _pair_cmp(ht->table[index]->pair, pair) == 0) {
    ack *tmp = ht->table[index];
    ht->table[index] = NULL;
    return tmp;
  }
  return NULL; 
}

ack *hash_table_lookup(hash_table * ht, pair pair) {
  int index = _hash(pair, ht->size);
  if (ht->table[index] != NULL &&
    _pair_cmp(ht->table[index]->pair, pair) == 0) return ht->table[index];
  return NULL;
}

void print_hash_table(hash_table *ht) {
  printf("\tIndex\t---\tAck\t\n");
  size_t i;
  for (i=0; i < ht->size; i++) {
    if (ht->table[i] == NULL) {
      printf("\t%ld\t---\n", i);
    } else {
      ack *a = ht->table[i];
      printf("\t%ld\t---\t(%d, %d)=>%ld\t\n", i, a->pair.m, a->pair.n, a->value);
    }
  }
  printf("\n");
}

unsigned int _hash(pair pair, size_t size) {
  int m = pair.m;
  int n = pair.n;
  return ((m*m + m + 2*m*n + 3*n + n*n) / 2) % size;
}

int _pair_cmp(pair p1, pair p2) {
  if (p1.m == p2.m && p1.n == p2.n) return 0;
  return 1;
}
