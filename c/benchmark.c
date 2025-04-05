
double get_time();
void run_mark(struct mark *, a_t, int, int);
int main() {
  printf("Algorithm: %s\n", algorithm);
  struct mark mark;
  run_mark(&mark, &iterative_a, m, n);
  printf("Iterative: (%d, %d) = %ld\n", m, n, mark.val);
  printf("%g (ms)\n", mark.delta);
  struct mark mark2;
  run_mark(&mark2, &a, m, n);
  printf("Naive: (%d, %d) = %ld\n", m, n, mark2.val);
  printf("%g (ms)\n", mark2.delta);
  return EXIT_SUCCESS;
}

struct mark {
  double delta;
  long val;
};

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
