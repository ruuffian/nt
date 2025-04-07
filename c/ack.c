/* 
* Author: Liam Mackay
* Date: April 4th, 2025
* Description: This is a C-implementation of the Ackermann function, considered
* to be the first discovered non-primitive recursive function. There are 
* several implementations of this algorithm contained within, with various 
* levels of optimizations applied to them. It is ill-advised to attempt to 
* calucate beyond A(4,1) as A(4,2) has 19729 digits. Perhaps there is a 
* concurrent algorithm that can compute this efficiently- it is unknown to me.
*/

#include <sys/time.h>
#include <sys/resource.h>

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "ackermann.h"

void usage(void);
double _get_time();

typedef enum {
  NAIVE,
  ITERATIVE,
  MEMOIZED 
} algorithm_t;

char *_progname;

int main(int argc, char *argv[]) {
  _progname = argv[0];
  int c;
  algorithm_t algorithm = NAIVE;
  while ((c = getopt (argc, argv, ":him")) != -1) {
    switch(c) {
      case 'h':
        usage();
        break;
        /* NOT REACHED */
      case 'i':
        algorithm = ITERATIVE;
        break;
      case 'm':
        algorithm = MEMOIZED;
        break;
      case '?':
        if (isprint(optopt)) 
          fprintf(stderr, "Unknown option character '-%c'.\n", optopt);
        else 
          fprintf(stderr, "Unknown option character '\\x%x'.\n", optopt);
        return EXIT_FAILURE;
      default:
        usage();
        /* NOT REACHED */
    }
  }
  argc -= optind;
  argv += optind;
  if (argc != 2) {
    usage();
    /* NOT REACHED */
  }
  /* Input validation */
  char *tmp;
  int m = strtol(argv[0], &tmp, 10);
  if (tmp == argv[0] || *tmp != '\0') {
    fprintf(stderr, "Invalid argument passed for 'm'.");
  }
  int n = strtol(argv[1], &tmp, 10);
  if (tmp == argv[1] || *tmp != '\0') {
    fprintf(stderr, "Invalid argument passed for 'n'.");
  }
  long val;
  ackermann_fn fn;
  char *a;
  switch (algorithm) {
    case NAIVE:
      a = "naive";
      fn = &naive;
      break;
    case ITERATIVE:
      a = "iterative";
      fn = &iterative;
      break;
    case MEMOIZED:
      a = "memoized";
      fn = &memoized;
      break;
    default:
      abort();
      /* NOT REACHED */
  }
  double start, end, delta;
  start = _get_time();
  val = (*fn)(m, n);
  end = _get_time();
  delta = (end - start) / (double) 1000;
  fprintf(stdout, "%s(%i, %i) = %ld\n", a, m, n, val);
  fprintf(stdout, "Runtime: %f (ms)\n", delta);
  return EXIT_SUCCESS;
}

void usage(void) {
  fprintf(stderr, "Usage: %s [-m | -i] M N\n", _progname);
  fprintf(stderr, "Calculates the Ackermann function given M and N.\n\n");
  fprintf(stderr, "  -m | -i\tChooses the Ackermann implementation to use. -m is memoized and -i is iterative. Specifying multiple options will use the last specified.\n\n");
  fprintf(stderr, "Note that 'm' values greater than 4 are ill-advised- ack(4,2) has 19 thousand digits.\n");
  exit(EXIT_FAILURE);
}

double _get_time() {
  struct timeval t;
  struct timezone tzp;
  gettimeofday(&t, &tzp);
  return t.tv_sec*1e6 + t.tv_usec;
}
