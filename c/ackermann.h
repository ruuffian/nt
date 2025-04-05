#ifndef _ACKERMANN_H
#define _ACKERMANN_H

#include <stdbool.h>
#include <stdlib.h>

typedef long (*ackermann_fn)(int, int);

long naive(int, int);
long memoized(int, int);
long iterative(int, int);

#endif
