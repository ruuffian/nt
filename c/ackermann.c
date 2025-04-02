#include <stdbool.h>
#include <stdlib.h>
#include "ackermann.h"

long a(int m, int n) {
  if (m == 0) 
    return (long) n + 1;
  else if (n == 0) 
    return a(m-1, 1);
  else
    return a(m-1, a(m, n-1));
}

long memoized_a(int m, int n) {
  return  -1;
}

long iterative_a(int i, int n) {
  long *next = calloc((long) i+1, sizeof(long));
  long *next_c = next;
  long *goal = calloc((long) i+1, sizeof(long));
  int idx = 0;
  while (idx < i+1){
    goal[idx++] = 1;
  }
  goal[i] = -1;
  long *goal_c = goal;
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
  free(next_c);
  free(goal_c);
  return value;
}
