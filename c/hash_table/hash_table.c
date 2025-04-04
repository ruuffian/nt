#include "hash_table.h"

ack *hash_table[TABLE_SIZE];
int main() {
  init_hash_table();
  print_hash_table();
  ack zero_0 = { .pair={.m=0, .n=0}, .value=1};
  ack three_10 = { .pair={.m=3, .n=10}, .value=8189};
  ack  four_1 = { .pair={.m=4, .n=0}, .value=13};
  hash_table_insert(&zero_0);
  hash_table_insert(&three_10);
  hash_table_insert(&four_1);
  print_hash_table();
  // Does exist
  ack *tmp = hash_table_lookup((pair){.m=3, .n=10});
  printf("Checking (3, 10):\t");
  if (tmp == NULL) {
    printf("Check failed! Oops!\n");
  } else {
    printf("%d\n",  tmp->value);
  }
  // Doesn't exist
  tmp = hash_table_lookup((pair){.m=2, .n=10});
  printf("Checking (2, 10):\t");
  if (tmp == NULL) {
    printf("Check failed! Oops!\n");
  } else {
    printf("%d\n",  tmp->value);
  }
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
  return 0;
}

void init_hash_table() {
  for (int i=0; i < TABLE_SIZE; i++){
    hash_table[i] = NULL;
  }
}

bool hash_table_insert(ack *p) {
  if (p == NULL) return false;
  int index = hash(p->pair);
  if (hash_table[index] != NULL) {
    return false;
  }
  hash_table[index] = p;
  return true;
}

ack *hash_table_delete(ack *p) {
  if (p == NULL) return NULL;
  int index = hash(p->pair);
  if (hash_table[index] != NULL &&
    pair_cmp(hash_table[index]->pair, p->pair) == 0) {
    ack *tmp = hash_table[index];
    hash_table[index] = NULL;
    return tmp;
  }
  return NULL;
}

ack *hash_table_lookup(pair p) {
  int index = hash(p);
  if (hash_table[index] != NULL &&
    pair_cmp(hash_table[index]->pair, p) == 0) return hash_table[index];
  return NULL;
}

unsigned int hash(pair pair) {
  int m = pair.m;
  int n = pair.n;
  return ((m*m + m + 2*m*n + 3*n + n*n) / 2) % TABLE_SIZE;
}

int pair_cmp(pair p1, pair p2) {
  if (p1.m == p2.m && p1.n == p2.n) return 0;
  return 1;
}

void print_hash_table() {
  printf("\tHash\t---\tPair\t\n");
  for (int i=0; i < TABLE_SIZE; i++) {
    if (hash_table[i] == NULL) {
      printf("\t%i\t---\n", i);
    } else {
      pair p = hash_table[i]->pair;
      printf("\t%i\t---\t(%d, %d)\t\n", i, p.m, p.n);
    }
  }
  printf("\n");
}
