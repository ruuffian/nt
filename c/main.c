#include <stdio.h>
#include <sys/time.h>
#include <sys/resource.h>
#include "ackermann.h"

#define M 3
#define N 20

struct mark {
  double delta;
  int val;
};

double get_time();
void run_mark(struct mark *mark, a_t fn);
void benchmark(a_t fn);

int main(int argc, char *argv[]) {
  a_t iterative;
  iterative = &iterative_a;
  benchmark(iterative);
  a_t naive;
  naive = &a;
  benchmark(naive);
  struct mark mark2;
  return 0;
}

void benchmark(a_t fn) {
  struct mark mark;
  run_mark(&mark, fn);
  printf("a(%d, %d) = %d\n", M, N, mark.val);
  printf("%g (ms)\n", mark.delta);
}

void run_mark(struct mark *mark, a_t fn) {
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
