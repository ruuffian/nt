#ifndef _ACKERMANN_H
#define _ACKERMANN_H

#include <stdbool.h>
#include <stdlib.h>

#include "libht.h"

typedef long (*ackermann_fn)(int, int);

long naive(int, int);
long memoized(int, int, hash_table *);
long iterative(int, int);

#endif
