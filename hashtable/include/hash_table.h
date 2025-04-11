/*
 * Author: Liam Mackay
 * Date: April 4th, 2025
 * Description: This is a C-implementation of a hash table which is attempting
 * to be type-agnostic.
 *  - Data is not typed
 *  - Key is a string
 *  - Size is dynamic (reallocates when table full)
 *  - If size reaches max, start external chaining
 */
#ifndef __HASH_TABLE_H
#define __HASH_TABLE_H

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

#define KEY_TYPE(type)

/* Table value type- we store the key in the value to double check the value
 * stored at the hashed index is actually the one we like, in case of
 * collisions.
 */
typedef struct {
  char *key;
  void *data;
} entry_t;

/* Function used to hash entry.key. Defaults to _hash(). */
typedef uint32_t (*hashfn_t)(char *, size_t);
/* Function used to free entry.value. Defaults to free(). */
typedef void (*cleanupfn_t)(void *);

typedef struct {
  entry_t **table;
  size_t size;
  size_t max_size;
  hashfn_t hash;
  cleanupfn_t cleanup;
} hash_table_t;

/**
 * Initialize a hash_table that can contain 'size' elements. hashfn_t and
 * cleanupfn_t can be NULL. max_size must be 1 or more.
 */
hash_table_t *hash_table_create(size_t max_size, hashfn_t hash,
                                cleanupfn_t cleanup);

/**
 * Frees a hash_table.
 */
void hash_table_destroy(hash_table_t *ht);

/**
 * Associate key -> value in ht. Returns a pointer to the entry that is stored
 * at key, returns NULL if insert fails.
 */
entry_t *hash_table_insert(hash_table_t *ht, char *key, void *d);

/**
 * Lookup a key in a hash_table. If 'key' is found in the table, returns the
 * value associted with it. Otherwise, returns NULL.
 */
entry_t *hash_table_lookup(hash_table_t *ht, char *key);

/**
 * Remove the value associated with 'key' from the given hash_table. If
 * 'key' or 'ht' are null or no value is associated with 'key' in the table,
 * returns NULL. Otherwise, returns the value associated with 'key'. Remember
 * to free() this value if it was allocated on the heap.
 */
entry_t *hash_table_delete(hash_table_t *ht, char *key);

/**
 * Prints a hash_table to stdout. Summarizes blank fields.
 */
void hash_table_print(hash_table_t *ht);
#endif
