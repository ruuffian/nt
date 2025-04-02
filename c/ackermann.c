#include "ackermann.h"

int A(int m, int n) {
  if (m == 0) 
    return n + 1;
  else if (n == 0) 
    return A(m-1, 1);
  else
    return A(m-1, A(m, n-1));
}

int memoized_A(int m, int n) {
  return  -1;
}

int iterative_A(int m, int n) {
  return -1;
}
