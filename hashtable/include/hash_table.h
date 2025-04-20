/*
 * Author: Liam Mackay
 * Date: April 4th, 2025
 * Description: This is a C-implementation of a hash table which is attempting
 * to be type-agnostic.
 *  - Data is not typed
 *  - Key is a string
 *  - Supports external chaining for 'infinite' table size, but compromises
 *    lookup speed.
 */
#ifndef __HASH_TABLE_H
#define __HASH_TABLE_H

#include <stdbool.h>
#include <stdio.h>

/* Table value type- we store the key in the value to double check the value
 * stored at the hashed index is actually the one we like, in case of
 * collisions. Each entry in the hash table is a linked list.
 */
typedef struct entry {
  char *key;
  void *data;
  struct entry *next;
} entry;

/* Cleans up whatever data is stored in entry->data. Defaults to free(). */
typedef void (*cleanup_fn)(void *);

typedef struct {
  size_t size;
  entry **table;
  cleanup_fn cleanup;
} hash_table;

/**
 * Initialize a hash_table that can contain 'size' elements. If cleanup is NULL,
 * defaults to stdlib.free(). max_size must be 1 or more.
 */
hash_table *hash_table_create(size_t max_size, cleanup_fn cleanup);

/**
 * Frees a hash_table.
 */
void hash_table_destroy(hash_table *ht);

/**
 * Associate key -> value in ht. Returns a pointer to the new entry if succeeds,
 * returns NULL if insert fails.
 */
entry *hash_table_insert(hash_table *ht, char *key, void *d);

/**
 * Lookup a key in a hash_table. If 'key' is found in the table, returns the
 * value associted with it. Otherwise, returns NULL.
 */
entry *hash_table_lookup(hash_table *ht, char *key);

/**
 * Remove the value associated with 'key' from the given hash_table. If
 * 'key' or 'ht' are null or no value is associated with 'key' in the table,
 * returns NULL. Otherwise, returns the value associated with 'key'. Remember
 * to free() this value if it was allocated on the heap.
 */
entry *hash_table_delete(hash_table *ht, char *key);

/**
 * Prints a hash_table to stdout. Summarizes blank fields.
 */
void hash_table_print(hash_table *ht);
#endif
