#include "hash_table.h"

ack *hash_t[TABLE_SIZE];
int main() {
  hash_table *table = hash_table_create(15);
  if (table == NULL) printf("Failed to create hash table...");
  print_hash_table(table);
  ack zero_0 = { .pair={.m=0, .n=0}, .value=1};
  ack three_10 = { .pair={.m=3, .n=10}, .value=8189};
  ack four_0 = { .pair={.m=4, .n=0}, .value=13};
  ack ten_3 = { .pair={.m=10, .n=3}, .value=0};
  printf("Inserting (0,0), (3,10), (4,0)...\n");
  hash_table_insert(table, &zero_0);
  hash_table_insert(table, &three_10);
  hash_table_insert(table, &four_0);
  print_hash_table(table);
  // Does exist
  ack *tmp = hash_table_lookup(table, three_10.pair);
  printf("Checking (3, 10):\t");
  if (tmp == NULL) {
    printf("Could not find (3,10)...something is wrong.\n");
  } else {
    printf("(%d, %d) => %d\n", tmp->pair.m, tmp->pair.n, tmp->value);
  }
  // Doesn't exist
  tmp = hash_table_lookup(table, ten_3.pair);
  printf("Checking (10, 3):\t");
  if (tmp == NULL) {
    printf("Could not find (10, 3).\n");
  } else {
    printf("Found (10, 3)...something went wrong.\n");
  }
  /*
  printf("Deleting (3, 10)...\t");
  tmp = hash_table_delete(&three_10);
  if (tmp == NULL) {
    printf("Object not found...\n");
  } else {
    printf("Deleted (%d, %d)\n", tmp->pair.m, tmp->pair.n);
  }
  printf("Deleting (3, 10)...\t");
  tmp = hash_table_delete(&three_10);
  if (tmp == NULL) {
    printf("Object not found...\n");
  } else {
    printf("Deleted (%d, %d)\n", tmp->pair.m, tmp->pair.n);
  }
  print_hash_table();
  */
  hash_table_destroy(table);
  return 0;
}

hash_table *hash_table_create(size_t size) {
  hash_table *ht;
  ht = malloc(sizeof(hash_table));
  if (ht == NULL) return NULL;
  ht->size = size;
  ht->table = (ack **)calloc(size, sizeof(ack *));
  if (ht->table == NULL) return NULL;
  //hash_table->table[size - 1] = NULL;
  return ht;
}

void hash_table_destroy(hash_table *ht) {
  free(ht->table);
  free(ht);
}

bool hash_table_insert(hash_table *hash_table, ack *p) {
  if (hash_table == NULL || p == NULL) return false;
  int index = hash(p->pair, hash_table->size);
  if (hash_table->table[index] != NULL) {
    return false;
  }
  hash_table->table[index] = p;
  return true;
}
/*
ack *hash_table_delete(ack *p) {
  if (p == NULL) return NULL;
  int index = hash(p->pair);
  if (hash_t[index] != NULL &&
    pair_cmp(hash_t[index]->pair, p->pair) == 0) {
    ack *tmp = hash_t[index];
    hash_t[index] = NULL;
    return tmp;
  }
  return NULL;
}
*/

ack *hash_table_lookup(hash_table * ht, pair pair) {
  int index = hash(pair, ht->size);
  if (ht->table[index] != NULL &&
    pair_cmp(ht->table[index]->pair, pair) == 0) return ht->table[index];
  return NULL;
}

unsigned int hash(pair pair, size_t size) {
  int m = pair.m;
  int n = pair.n;
  return ((m*m + m + 2*m*n + 3*n + n*n) / 2) % size;
}

int pair_cmp(pair p1, pair p2) {
  if (p1.m == p2.m && p1.n == p2.n) return 0;
  return 1;
}

void print_hash_table(hash_table *ht) {
  printf("\tIndex\t---\tAck\t\n");
  for (int i=0; i < ht->size; i++) {
    if (ht->table[i] == NULL) {
      printf("\t%i\t---\n", i);
    } else {
      ack *a = ht->table[i];
      printf("\t%i\t---\t(%d, %d)=>%d\t\n", i, a->pair.m, a->pair.n, a->value);
    }
  }
  printf("\n");
}
