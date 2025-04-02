#include <stdio.h>
#include <sys/time.h>
#include <sys/resource.h>
#include "ackermann.h"

#define M 3
#define N 10

struct mark {
  double delta;
  int val;
};

double get_time();
void benchmark(struct mark *mark, a_t fn);

int main(int argc, char *argv[]) {
  struct mark mark;
  a_t naive;
  naive = &a;
  benchmark(&mark, naive);
  printf("A(%d, %d) = %d\n", M, N, mark.val);
  printf("%g (ms)\n", mark.delta);
  return 0;
}

void benchmark(struct mark *mark, a_t fn) {
  double start, end;
  start = get_time();
  int val = (*fn)(M, N);
  end = get_time();
  double delta = (end - start) / (double) 1000;
  mark->delta = delta;
  mark->val = val;
}

double get_time() {
  struct timeval t;
  struct timezone tzp;
  gettimeofday(&t, &tzp);
  return t.tv_sec*1e6 + t.tv_usec;
}
