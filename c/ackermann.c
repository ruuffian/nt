#include "ackermann.h"

void _cache_ack(hash_table *table, long value, pair key);

long naive(int m, int n) {
  if (m == 0) 
    return (long) n + 1;
  else if (n == 0) 
    return naive(m-1, 1);
  else
    return naive(m-1, naive(m, n-1));
}

long memoized(int m, int n, hash_table *table) {
  pair key = {.m=m, .n=n};
  ack *cached = hash_table_lookup(table, key);
  if (cached != NULL) 
    return cached->value;
  if (m == 0) {
    long value = (long) n + 1;
    _cache_ack(table, value, key);
    return value;
  } else if (n == 0) {
    long value = memoized(m-1, 1, table);
    _cache_ack(table, value, key);
    return value;
  }
  else {
    long value = memoized(m-1, memoized(m, n-1, table), table);
    _cache_ack(table, value, key);
    return value;
  }
}

void _cache_ack(hash_table *table, long value, pair key) {
    ack *ack = malloc(sizeof(ack));
    if (ack == NULL) {
      fprintf(stderr, "Memory allocation failed.\n");
      abort();
      /* NOT REACHED */
    }
    ack->value = value;
    ack->pair = key;
    if(hash_table_insert(table, key, ack) == false) {
      fprintf(stderr, "Failed to insert into cache.\n");
      abort();
      /* NOT REACHED */
    }
}

long iterative(int i, int n) {
  long *next = calloc((long) i+1, sizeof(long));
  long *goal = calloc((long) i+1, sizeof(long));
  int idx = 0;
  while (idx < i+1){
    goal[idx++] = 1;
  }
  goal[i] = -1;
  long value = -1;
  do  {
    value = next[0] + 1;
    bool transferring = true;
    long current = i;
    while (transferring) {
      if (next[i-current] == goal[i-current]) {
        goal[i-current] = value;
      } else {
        transferring = false;
      }
      next[i-current] = next[i-current]+1;
      current -= 1;
    }
  } 
  while (next[i] != (long) n + 1);
  free(next);
  free(goal);
  return value;
}
