#include "hash_table.h"

ack *hash_t[TABLE_SIZE];
int main() {
  hash_table table;
  init_hash_table(&table, 15);
  print_hash_table(table);
  ack zero_0 = { .pair={.m=0, .n=0}, .value=1};
  ack three_10 = { .pair={.m=3, .n=10}, .value=8189};
  ack  four_1 = { .pair={.m=4, .n=0}, .value=13};
  hash_table_insert(&zero_0);
  hash_table_insert(&three_10);
  hash_table_insert(&four_1);
  print_hash_table();
  // Does exist
  /*
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
  */
  return 0;
}

hash_table *init_hash_table(hash_table *hash_table, size_t size) {
  hash_table->size = size;
  // Allocate memory for *size* instances of *ack*.
  hash_table->table = (ack **)calloc(TABLE_SIZE, sizeof(ack *));
  if (hash_table->table == NULL) return NULL;
  hash_table->table[size - 1] = NULL;
  return hash_table;
}

bool hash_table_insert(ack *p) {
  if (p == NULL) return false;
  int index = hash(p->pair);
  if (hash_t[index] != NULL) {
    return false;
  }
  hash_t[index] = p;
  return true;
}

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

ack *hash_table_lookup(pair p) {
  int index = hash(p);
  if (hash_t[index] != NULL &&
    pair_cmp(hash_t[index]->pair, p) == 0) return hash_t[index];
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

void print_hash_table(hash_table hash_table) {
  printf("\tIndex\t---\tAck\t\n");
  for (int i=0; i < hash_table.size; i++) {
    if (hash_table.table[i] == NULL) {
      printf("\t%i\t---\n", i);
    } else {
      ack *a = hash_table.table[i];
      printf("\t%i\t---\t(%d, %d)=>%d\t\n", i, a->pair.m, a->pair.n, a->value);
    }
  }
  printf("\n");
}
