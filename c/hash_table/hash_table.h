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

hash_table *hash_table_create(size_t);
void hash_table_destroy(hash_table *);
bool hash_table_insert(hash_table *, ack *);
ack *hash_table_lookup(hash_table *, pair);
ack *hash_table_delete(ack *);
void print_hash_table(hash_table *);
int pair_cmp(pair p1, pair p2);
unsigned int hash(pair, size_t); 
#endif
