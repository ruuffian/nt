#ifndef __HASH_TABLE_H
#define __HASH_TABLE_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct {
  int m;
  int n;
} pair;

typedef struct {
  pair pair;
  int value;
} ack;

typedef struct {
  ack **table;
  size_t size;
} hash_table;

/** 
 * Initialize a hash_table that can contain 'size' elements.
 */
hash_table *hash_table_create(size_t size);
/**
 * Frees a hash_table.
 */
void hash_table_destroy(hash_table *ht);
/**
 * Associate key -> value in ht. Returns true if successful, false otherwise
 */
bool hash_table_insert(hash_table *ht, pair key, ack *value);
ack *hash_table_lookup(hash_table *ht, pair key);
/**
 * Remove the value associated with 'key' from the given hash_table. If 
 * 'key' or 'ht' are null or no value is associated with 'key' in the table,
 * returns NULL. Otherwise, returns the value associated with 'key'. Remember
 * to free() this value if it was allocated on the heap.
 */
ack *hash_table_delete(hash_table *ht, pair key);
/**
 * Prints a hash_table to stdout.
 */
void print_hash_table(hash_table *ht);
/**
 * Compares 'p1' to 'p2'. Returns 0 if they are identical, 1 otherwise.
 */
static int _pair_cmp(pair p1, pair p2);
/**
  * Hashes 'key' for insertion in a hash_table with a capacity of 'size'
  * elements.
  */
static unsigned int _hash(pair key, size_t size); 
#endif
