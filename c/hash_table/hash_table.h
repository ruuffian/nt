#include <stdio.h>
#include <stdbool.h>

#define TABLE_SIZE 20

typedef struct {
  int m;
  int n;
} pair;

typedef struct {
  pair pair;
  int value;
} ack;

void init_hash_table();
ack *hash_table_lookup(pair);
bool hash_table_insert(ack *);
ack *hash_table_delete(ack *);
void print_hash_table();
int pair_cmp(pair p1, pair p2);
unsigned int hash(pair); 
