#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <ctype.h>
#include <sys/time.h>
#include <sys/resource.h>
#include "ackermann.h"

struct mark {
  double delta;
  long val;
};

void usage(char*);
double get_time();
void run_mark(struct mark *, a_t, int, int);

int main(int argc, char *argv[]) {
  // cmdline parsing
  int iterations =  100;
  int c;
  while ((c = getopt (argc, argv, "hl:")) != -1) {
    switch(c) {
      case 'h':
        usage(argv[0]);
        return 0;
      case 'l':
        iterations = atoi(optarg);
        if (iterations == 0) {
          fprintf(stderr, "'-l' must be followed by a non-zero number.");
          return 1;
        }
        break;
      case '?':
        if (optopt == 'l') 
          fprintf(stderr, "Option -%c requires an argument.\n", optopt);
        else if (isprint(optopt)) 
          fprintf(stderr, "Unknown option character '-%c'.\n", optopt);
        else 
          fprintf(stderr, "Unknown option character '\\x%x'.\n", optopt);
        return 1;
      default:
        abort();
    }
  }
  if (argc != 3) {
    usage(argv[0]);
    return 1;
  }
  int m = atoi(argv[1]);
  int n = atoi(argv[2]);
  struct mark mark;
  run_mark(&mark, &iterative_a, m, n);
  printf("Iterative: (%d, %d) = %ld\n", m, n, mark.val);
  printf("%g (ms)\n", mark.delta);
  struct mark mark2;
  run_mark(&mark2, &a, m, n);
  printf("Naive: (%d, %d) = %ld\n", m, n, mark2.val);
  printf("%g (ms)\n", mark2.delta);
  return 0;
}

void usage(char *name) {
  printf("Usage: %s m n\n", name);
  printf("\tm and n are arguments to various implementations of the Ackermann function.\n");
  printf("\tNote that M values greater than 4 are ill-advised- ack(4,2) will likely never compute.\n");
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
