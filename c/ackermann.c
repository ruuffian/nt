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

int iterative_a(int m, int n) {
  return -1;
}
