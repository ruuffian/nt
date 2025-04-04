#ifndef __HASH_TABLE_H
#define __HASH_TABLE_H

#include <stdio.h>
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

/*typedef struct {
  ack **table;
  int size;
} hash_table;*/

void init_hash_table();
ack *hash_table_lookup(pair);
bool hash_table_insert(ack *);
ack *hash_table_delete(ack *);
void print_hash_table();
int pair_cmp(pair p1, pair p2);
unsigned int hash(pair); 
#endif
