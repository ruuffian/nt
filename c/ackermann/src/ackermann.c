#include <stdbool.h>
#include <stdlib.h>

#include "ackermann.h"
#include "hash_table.h"

/* Allocates an 'ack' on the heap and associates it with a given key */
void _cache(hash_table *table, uint64_t value, tuple key);
/* Internal memoized ackermann calculation */
uint64_t _memoized(uint64_t m, uint64_t n, hash_table *table);

uint64_t naive(uint64_t m, uint64_t n) {
  if (m == 0)
    return n + 1;
  else if (n == 0)
    return naive(m - 1, 1);
  else
    return naive(m - 1, naive(m, n - 1));
}

uint64_t memoized(uint64_t m, uint64_t n) {
  hash_table *t = ht_create(64);
  if (t == NULL) {
    fprintf(stderr, "Failed to create hash table.");
    abort();
    /* NOT REACHED. */
  }
  uint64_t val = _memoized(m, n, t);
  ht_destroy(t);
  return val;
}

uint64_t _memoized(uint64_t m, uint64_t n, hash_table *table) {
  tuple key = {m, n};
  record *r = ht_lookup(table, key);
  if (r != NULL)
    return r->value;
  if (m == 0) {
    uint64_t value = n + 1;
    _cache(table, value, key);
    return value;
  } else if (n == 0) {
    uint64_t value = _memoized(m - 1, 1, table);
    _cache(table, value, key);
    return value;
  } else {
    uint64_t value = _memoized(m - 1, _memoized(m, n - 1, table), table);
    _cache(table, value, key);
    return value;
  }
}

void _cache(hash_table *table, uint64_t value, tuple key) {
  record *e = malloc(sizeof(record));
  if (e == NULL) {
    fprintf(stderr, "Memory allocation failed.\n");
    abort();
    /* NOT REACHED */
  }
  e->key = key;
  e->value = value;
  record *tmp;
  if ((tmp = ht_insert(table, key, e)) == NULL) {
    fprintf(stderr, "Failed to insert into cache.\n");
    abort();
    /* NOT REACHED */
  }
  if (tmp != e)
    free(tmp);
}

uint64_t iterative(uint64_t i, uint64_t n) {
  uint64_t *next = calloc((uint64_t)i + 1, sizeof(uint64_t));
  uint64_t *goal = calloc((uint64_t)i + 1, sizeof(uint64_t));
  uint64_t idx = 0;
  while (idx < i + 1) {
    goal[idx++] = 1;
  }
  goal[i] = -1;
  uint64_t value = -1;
  do {
    value = next[0] + 1;
    bool transferring = true;
    uint64_t current = i;
    while (transferring) {
      if (next[i - current] == goal[i - current]) {
        goal[i - current] = value;
      } else {
        transferring = false;
      }
      next[i - current] = next[i - current] + 1;
      current -= 1;
    }
  } while (next[i] != (uint64_t)n + 1);
  free(next);
  free(goal);
  return value;
}
