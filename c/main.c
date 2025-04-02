#include <stdio.h>
#include <sys/time.h>
#include <sys/resource.h>
#include "ackermann.h"

#define M 4
#define N 1

double get_time();

int main(int argc, char *argv[]) {
  double start, end;
  start = get_time();
  const int ackermann = A(M, N);
  end = get_time();

  printf("A(%d, %d) = %d\n", M, N, ackermann);
  printf("%g (ms)\n", (end - start) / (double) 1000);
  return 0;
}

double get_time() {
  struct timeval t;
  struct timezone tzp;
  gettimeofday(&t, &tzp);
  return t.tv_sec*1e6 + t.tv_usec;
}
