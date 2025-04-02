#include <stdbool.h>
#include <stdlib.h>
#include "ackermann.h"

int a(int m, int n) {
  if (m == 0) 
    return n + 1;
  else if (n == 0) 
    return a(m-1, 1);
  else
    return a(m-1, a(m, n-1));
}

int memoized_a(int m, int n) {
  return  -1;
}

int iterative_a(int i, int n) {
  int *next = calloc(i+1, sizeof(int));
  int *next_c = next;
  int *goal = calloc(i+1, sizeof(int));
  int idx = 0;
  while (idx < i+1){
    goal[idx++] = 1;
  }
  goal[i] = -1;
  int *goal_c = goal;
  int value = -1;
  do  {
    value = next[0] + 1;
    bool transferring = true;
    int current = i;
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
  while (next[i] != n + 1);
  free(next_c);
  free(goal_c);
  return value;
}
