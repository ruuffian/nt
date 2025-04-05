#include "hash_table.h"

int main() {
  hash_table *table = hash_table_create(15);
  if (table == NULL) printf("Failed to create hash table...");
  print_hash_table(table);
  ack zero_0 = { .pair={.m=0, .n=0}, .value=1};
  ack three_10 = { .pair={.m=3, .n=10}, .value=8189};
  ack four_0 = { .pair={.m=4, .n=0}, .value=13};
  ack ten_3 = { .pair={.m=10, .n=3}, .value=0};
  printf("Inserting (0,0), (3,10), (4,0)...\n");
  hash_table_insert(table, zero_0.pair, &zero_0);
  hash_table_insert(table, three_10.pair, &three_10);
  hash_table_insert(table, four_0.pair, &four_0);
  print_hash_table(table);
  ack *tmp;
  // Does exist
  tmp = hash_table_lookup(table, three_10.pair);
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
  printf("Deleting (3, 10):\t");
  tmp = hash_table_delete(table, three_10.pair);
  if (tmp == NULL) {
    printf("Could not find (3,10)...something bad happened.\n");
  } else {
    printf("Deleted (3, 10)!\n");
  }
  printf("Deleting (3, 10):\t");
  tmp = hash_table_delete(table, three_10.pair);
  if (tmp == NULL) {
    printf("Could not find (3, 10)!\n");
  } else {
    printf("Deleted (3, 10)...something bad happened.\n");
  }
  print_hash_table(table);
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
  return ht;
}

void hash_table_destroy(hash_table *ht) {
  free(ht->table);
  free(ht);
}

bool hash_table_insert(hash_table *ht, pair key, ack *value) {
  if (ht == NULL || value == NULL) return false;
  int index = _hash(key, ht->size);
  if (ht->table[index] != NULL) {
    return false;
  }
  ht->table[index] = value;
  return true;
}

ack *hash_table_delete(hash_table *ht, pair pair) {
  if (ht == NULL) return NULL;
  int index = _hash(pair, ht->size);
  if (ht->table[index] != NULL &&
    _pair_cmp(ht->table[index]->pair, pair) == 0) {
    ack *tmp = ht->table[index];
    ht->table[index] = NULL;
    return tmp;
  }
  return NULL; 
}

ack *hash_table_lookup(hash_table * ht, pair pair) {
  int index = _hash(pair, ht->size);
  if (ht->table[index] != NULL &&
    _pair_cmp(ht->table[index]->pair, pair) == 0) return ht->table[index];
  return NULL;
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

static unsigned int _hash(pair pair, size_t size) {
  int m = pair.m;
  int n = pair.n;
  return ((m*m + m + 2*m*n + 3*n + n*n) / 2) % size;
}

static int _pair_cmp(pair p1, pair p2) {
  if (p1.m == p2.m && p1.n == p2.n) return 0;
  return 1;
}
