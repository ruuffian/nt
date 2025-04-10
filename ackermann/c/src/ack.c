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
#include <float.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "ackermann.h"

#define STACK_SIZE 16

/* Print application usage statement and terminate. */
void usage(void);
/* Call fn(m, n) 'loops'-many times and print some basic analytics. */
void _benchmark(ackermann_fn, uint64_t, uint64_t, int);
/* Get the current time in nanoseconds */
double _get_time();

/* Available ackermann_fn algorithms */
typedef enum {
  NAIVE,
  ITERATIVE,
  MEMOIZED 
} algorithm_t;

/* Global program name for usage() */
char *_progname;

int main(int argc, char *argv[]) {
  _progname = argv[0];
  int c;
  algorithm_t algorithm = NAIVE;
  int loops = 0;
  rlim_t stack_size = STACK_SIZE;
  char *tmp;
  while ((c = getopt (argc, argv, ":himl:s:")) != -1) {
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
      case 'l':
        int l = strtol(optarg, &tmp, 10);
        if (tmp == optarg || *tmp != '\0') {
          fprintf(stderr, "Invalid argument passed for 'l'.\n");
          return EXIT_FAILURE;
        } else if (loops < 0) {
          fprintf(stderr, "'l' value must be greater than 0.\n");
          return EXIT_FAILURE;
        }
        loops = l;
        break;
      case 's':
        int s = strtol(optarg, &tmp, 10);
        if (tmp == optarg || *tmp != '\0') {
          fprintf(stderr, "Invalid argument passed for 's'.\n");
          return EXIT_FAILURE;
        } else if (s < 0) {
          fprintf(stderr, "'s' value must be greater than 0.\n");
          return EXIT_FAILURE;
        }
        if (s > 1024) {
          fprintf(stderr, "'s' value must be less than 1024.\n");
          return EXIT_FAILURE;
        }
        stack_size = s;
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
  /* We need to account for arguments parsed by getopt */
  argc -= optind;
  argv += optind;
  /* M and N are required arguments */
  if (argc != 2) {
    usage();
    /* NOT REACHED */
  }
  /* Input validation */
  uint64_t m = strtol(argv[0], &tmp, 10);
  if (tmp == argv[0] || *tmp != '\0') {
    fprintf(stderr, "Invalid argument passed for 'm'.");
    usage();
    /* NOT REACHED */
  }
  uint64_t n = strtol(argv[1], &tmp, 10);
  if (tmp == argv[1] || *tmp != '\0') {
    fprintf(stderr, "Invalid argument passed for 'n'.");
    usage();
    /* NOT REACHED */
  }
  /* Select algorithm- I'm almost positive there's an easier way. */
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
      struct rlimit rl;
      rl.rlim_cur = stack_size * 1024 * 1024;
      rl.rlim_max = stack_size * 1024 * 1024;
      setrlimit(RLIMIT_STACK, &rl);
      getrlimit(RLIMIT_STACK, &rl);
      printf("Stack size: %ld (MB), max stack: %ld (MB)\n", rl.rlim_cur / 1024 / 1024, rl.rlim_max / 1024 / 1024);
      a = "memoized";
      fn = &memoized;
      break;
    default:
      abort();
      /* NOT REACHED */
  }
  /* Run the function once for quick feedback, then check for benchmarking */
  double start, end, delta;
  start = _get_time();
  uint64_t val = (*fn)(m, n);
  end = _get_time();
  delta = (end - start) / (double) 1000;
  fprintf(stdout, "%s(%ld, %ld) = %ld\n", a, m, n, val);
  fprintf(stdout, "Runtime: %f (ms)\n", delta);
  /* If user doesn't give  a loop value, don't benchmark. */
  if (loops != 0) {
    _benchmark(fn, m, n, loops);
  }
  return EXIT_SUCCESS;
}

void _benchmark(ackermann_fn fn, uint64_t m, uint64_t n, int loops) {
  int counter = 0;
  double *times = calloc(loops, sizeof(double));
  if (times == NULL) {
    fprintf(stderr, "Memory allocation failed.");
    abort();
  }
  double min = DBL_MAX, max = 0, sum = 0;
  /* int peek;
  if (loops < PEEK_SIZE) peek = loops;
  else peek = PEEK_SIZE;
  */
  while(counter < loops) {
    double start, end, delta;
    start = _get_time();
    (*fn)(m, n);
    end = _get_time();
    delta = (end - start) / (double) 1000;
    times[counter] = delta;
    if (delta > max) max = delta;
    if (delta < min) min = delta;
    sum += delta;
    counter++;
  }
  double median = times[(loops / 2) - 1];
  double avg = sum / (double) loops;
  printf("Runtime metrics [%d loops] => {\n", loops);
  /* I need to implement a sorting algorithm :D
  printf("Peek (top %d): [", peek);
  int i;
  for(i=0; i < peek; i++){
    printf("%lf, ", times[i]);
  }
  printf("]\n");
  */
  printf("\tAverage: %lf (ms)\n", avg);
  printf("\tMedian: %lf (ms)\n", median);
  printf("\tMin: %lf (ms)\n", min);
  printf("\tMax: %lf (ms)\n", max);
  printf("}\n");
  free(times);
}

void usage(void) {
  fprintf(stderr, "Usage: %s [-m | -i] [-l LOOPS] M N\n", _progname);
  fprintf(stderr, "Calculates the Ackermann function given M and N.\n\n");
  fprintf(stderr, "  -m | -i\tChooses the Ackermann implementation to use. -m is memoized and -i is iterative. Specifying multiple options will use the last specified.\n");
  fprintf(stderr, "  -l LOOPS\tRuns the algorithm with the given inputs LOOPS times and analyzes the results.\n\n");
  fprintf(stderr, "  -s STACK_SIZE\tSets the max stack size in MB to STACK_SIZE. Must be greater than 0.\n\n");
  fprintf(stderr, "Note that 'm' values greater than 4 are ill-advised- ack(4,2) has 19 thousand digits.\n");
  exit(EXIT_FAILURE);
}

double _get_time() {
  struct timeval t;
  struct timezone tzp;
  gettimeofday(&t, &tzp);
  return t.tv_sec*1e6 + t.tv_usec;
}
