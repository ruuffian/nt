/*
 * Author: Liam Mackay
 * Date: April 4th, 2025
 * Description: This is a C-implementation of a hash table, using a tuple of
 * ints as its key and a long as its value. Lookup performance is increidbly
 * important to this implementation- external chaining and linear probing both
 * had extremely negative impacts on performance. It turns out that ackermann's
 * function's cache lookups are fairly local within the algorithm.
 */
#ifndef __HASH_TABLE_H
#define __HASH_TABLE_H

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

/* Table key type */
typedef struct {
  uint64_t m;
  uint64_t n;
} key;

/* Table value type- we store the key in the value to double check the value
 * stored at the hashed index is actually the one we like, in case of
 * collisions.
 */
typedef struct {
  key key;
  uint64_t value;
} entry;

typedef struct {
  entry **table;
  size_t size;
} hash_table;

/**
 * Initialize a hash_table that can contain 'size' elements.
 */
hash_table *hash_table_create(size_t size);

/**
 * Frees a hash_table. If the table contains heap-allocated memory, it MUST
 * be free()-d before invoking this function.
 */
void hash_table_destroy(hash_table *ht);

/**
 * Associate key -> value in ht. Returns a pointer to the entry that is stored
 * at key, returns NULL if insert fails.
 */
entry *hash_table_insert(hash_table *ht, key key, entry *v);

/**
 * Lookup a key in a hash_table. If 'key' is found in the table, returns the
 * value associted with it. Otherwise, returns NULL.
 */
entry *hash_table_lookup(hash_table *ht, key key);

/**
 * Remove the value associated with 'key' from the given hash_table. If
 * 'key' or 'ht' are null or no value is associated with 'key' in the table,
 * returns NULL. Otherwise, returns the value associated with 'key'. Remember
 * to free() this value if it was allocated on the heap.
 */
entry *hash_table_delete(hash_table *ht, key key);

/**
 * Prints a hash_table to stdout.
 */
void hash_table_print(hash_table *ht);
#endif
