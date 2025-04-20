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

typedef struct {
  uint64_t m;
  uint64_t n;
} tuple;

typedef struct {
  tuple key;
  uint64_t value;
} record;

typedef struct {
  record **table;
  size_t size;
} hash_table;

/**
 * Initialize a hash_table that can contain 'size' elements. Cleanup handled by
 * ht_destroy().
 */
hash_table *ht_create(size_t size);

/**
 * Cleans up a hash table. Note that elements that are overwritten must be
 * cleaned up at that time, otherwise memory leaks are possible.
 */
void ht_destroy(hash_table *ht);

/**
 * Inserts a record into the table. If successful, returns a pointer to the
 * record that *was* stored (to be free()-d). Returns NULL if insert fails.
 */
record *ht_insert(hash_table *ht, tuple key, record *v);

/**
 * Lookup a key in a hash_table. If 'key' is found in the table, returns the
 * value associted with it. Otherwise, returns NULL.
 */
record *ht_lookup(hash_table *ht, tuple key);

/**
 * Prints a hash_table to stdout.
 */
void ht_print(hash_table *ht);
#endif
