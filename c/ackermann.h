#ifndef _ACKERMANN_H
#define _ACKERMANN_H

#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

#include "libht.h"

/* Contract for ackermann algorithms */
typedef uint64_t (*ackermann_fn)(uint64_t, uint64_t);

/* Pure recursive solution */
uint64_t naive(uint64_t, uint64_t);
/* Memoized solution */
uint64_t memoized(uint64_t, uint64_t);
/* Iterative solution */
uint64_t iterative(uint64_t, uint64_t);

#endif
