#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "hash_table.h"

/**
 * Hashes 'key' for insertion in a hash_table with a capacity of 'size'
 * elements.
 */
uint32_t _hash(char *key, size_t size);

hash_table *hash_table_create(size_t size, cleanup_fn c) {
  if (size < 1)
    return NULL;
  if (c == NULL)
    c = &free;
  hash_table *ht;
  ht = malloc(sizeof(hash_table));
  if (ht == NULL)
    return NULL;
  ht->size = size;
  ht->table = (entry **)calloc(ht->size, sizeof(entry *));
  ht->cleanup = c;
  if (ht->table == NULL) {
    free(ht);
    return NULL;
  }
  return ht;
}

void hash_table_destroy(hash_table *ht) {
  size_t i;
  for (i = 0; i < ht->size; i++) {
    entry *prev, *e = ht->table[i];
    /* Need to free linked list stored in each bucket. */
    while (e != NULL) {
      free(e->key);
      ht->cleanup(e->data);
      prev = e;
      e = e->next;
      free(prev);
    }
  }
  free(ht->table);
  free(ht);
}

entry *hash_table_insert(hash_table *ht, char *key, void *d) {
  if (ht == NULL || d == NULL)
    return NULL;
  uint32_t index = _hash(key, ht->size);
  entry *new_entry = malloc(sizeof(entry));
  /* Need to allocate memory for key in case char *key is stack-allocated */
  char *new_key = strdup(key);
  if (new_entry == NULL)
    return NULL;
  new_entry->key = new_key;
  new_entry->data = d;
  entry *current = ht->table[index];
  ht->table[index] = new_entry;
  if (current != NULL)
    new_entry->next = current;
  else
    new_entry->next = NULL;
  return new_entry;
}

entry *hash_table_delete(hash_table *ht, char *key) {
  if (ht == NULL)
    return NULL;
  uint32_t idx = _hash(key, ht->size);
  entry *prev = NULL, *cur = ht->table[idx];
  while (cur != NULL) {
    if (strcmp(cur->key, key) == 0) {
      /* Deleting the head. */
      if (prev == NULL) {
        ht->table[idx] = NULL;
        return cur;
      }
      prev->next = cur->next;
      return cur;
    }
    prev = cur;
    cur = cur->next;
  }
  return NULL;
}

entry *hash_table_lookup(hash_table *ht, char *key) {
  uint32_t index = _hash(key, ht->size);
  entry *cur = ht->table[index];
  while (cur != NULL) {
    if (strcmp(cur->key, key) == 0)
      return cur;
    cur = cur->next;
  }
  return NULL;
}

void hash_table_print(hash_table *ht) {
  printf("\tHash\t---\tEntry\t\n");
  size_t i;
  for (i = 0; i < ht->size; i++) {
    if (ht->table[i] == NULL) {
      printf("\t%ld\t---\n", i);
    } else {
      entry *e = ht->table[i];
      printf("\t%ld\t---\t%s", i, e->key);
      while (e->next != NULL) {
        e = e->next;
        printf("---%s", e->key);
      }
      printf("\n");
    }
  }
  printf("\n");
}

uint32_t _hash(char *key, size_t size) {
  char *tmp = key;
  uint32_t hash = 5381;
  int c;
  while ((c = *tmp++))
    hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
  return hash % size;
}
