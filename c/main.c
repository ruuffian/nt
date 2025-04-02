#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <stdarg.h>
#include "ackermann.h"

struct mark {
  double delta;
  long val;
};

double get_time();
void run_mark(struct mark *, a_t, int, int);
void benchmark(a_t, char*, int, int);
void usage();

int main(int argc, char *argv[]) {
  if (argc != 3) {
    usage();
    return 1;
  }
  int m = atoi(argv[1]);
  int n = atoi(argv[2]);
  if (m == 0 || n == 0) {
    usage();
    return 1;
  }
  a_t iterative;
  iterative = &iterative_a;
  benchmark(iterative, "Iterative", m, n);
  a_t naive;
  naive = &a;
  benchmark(naive, "Naive", m, n);
  struct mark mark2;
  return 0;
}

void usage() {
  printf("Usage: main <m> <n>");
}

void benchmark(a_t fn, char* descriptor, int m, int n) {
  struct mark mark;
  run_mark(&mark, fn, m, n);
  printf("%s: (%d, %d) = %ld\n", descriptor, m, n, mark.val);
  printf("%g (ms)\n", mark.delta);
}

void run_mark(struct mark *mark, a_t fn, int m, int n) {
  double start, end;
  start = get_time();
  long val = (*fn)(m, n);
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
