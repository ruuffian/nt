#ifndef __HASH_TABLE_H
#define __HASH_TABLE_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define TABLE_SIZE 15

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

// Initializes a hash_table struct. Remember to free() when done.
hash_table *init_hash_table(hash_table *, size_t);
ack *hash_table_lookup(pair);
bool hash_table_insert(ack *);
ack *hash_table_delete(ack *);
void print_hash_table(hash_table);
int pair_cmp(pair p1, pair p2);
unsigned int hash(pair); 
#endif
