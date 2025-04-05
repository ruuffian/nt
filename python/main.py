#!/usr/bin/env python
# Computes and Benchmarks the Ackermann function:
import sys
import timeit
import time
import argparse
import numpy as np
from ackermann import naive, memoized, iterative

# ----- GLOBALS -----
M = 0
N = 0
ITERATIONS = 0


# ----- BENCHMARKING ------
def benchmark(fn_str):
    """Coordinate calls on a function."""
    marks = timeit.repeat(stmt=f'{fn_str}(M, N)',
                          globals=globals(),
                          repeat=ITERATIONS,
                          number=1)
    return marks


def report_marks(fn_str, marks):
    times, avg, min, max, median, variance, std_dev = analyze_marks(marks)
    print(f'\tRuntime Metrics [{len(times)} loops] => {{')
    print(f'\t\tPeek (top 5): {sorted(times, reverse=True)[0:5]}')
    print(f'\t\tAverage: {avg} ms')
    print(f'\t\tMedian: {median} ms')
    print(f'\t\tMin time:  {min} ms')
    print(f'\t\tMax time:  {max} ms')
    print(f'\t\tVariance:  {variance}')
    print(f'\t\tStandard Deviation:  {std_dev}')
    print('\t}')


# ----- DATA ANALYSIS ------
def analyze_marks(raw_marks):
    """Recieves a list of marks and calculates basic summary statistics.
    This area had a bit more before adding NumPy.
    """
    # Seconds -> Milliseconds
    marks = np.array(raw_marks, dtype=float)
    marks = marks * 1000
    return marks, np.mean(marks), np.min(marks), np.max(marks), np.median(marks), np.var(marks), np.std(marks)


# ----- SCRIPT -----
def main():
    # Default recursion limit too low for the Ackermann function
    sys.setrecursionlimit(10**6)
    print(f'{ALGORITHM}({M},{N}) => {{')
    fn = naive
    match ALGORITHM:
        case 'naive':
            fn = naive
        case 'memoized':
            fn = memoized
        case 'iterative':
            fn = iterative

    start = time.perf_counter_ns()
    val = fn(M, N)
    end = time.perf_counter_ns()
    calls = fn.calls
    print(f'\tFunction Return: {val}')
    print(f'\tTotal Recursive Calls: {calls}')
    print(f'\tRuntime: {(end - start) / 1e6} (ms)')
    if ITERATIONS > 0:
        print(f'\tBenchmarking {ALGORITHM} alg...')
        marks = benchmark(ALGORITHM)
        report_marks(ALGORITHM, marks)
    print('}')


if __name__ == "__main__":
    # Can't access M, N, or ITERATIONS from main() function
    parser = argparse.ArgumentParser(
        description='Benchmarks varius Ackermann\'s function implementations against each other.'
    )
    parser.add_argument(
        'm',
        type=int,
        help='First argument to Ackermann\'s function.'
    )
    parser.add_argument(
        'n',
        type=int,
        help='Second argument to Ackermann\'s function.'
    )
    parser.add_argument(
        '--loops',
        '-l',
        type=int,
        help='The number of iterations to use for benchmarking.',
        default=0
    )
    parser.add_argument(
        '--algorithm',
        '-a',
        help='Choosing the algorithm to calculate with.',
        choices=['naive', 'memoized', 'iterative'],
        default='naive',
    )
    args = vars(parser.parse_args())
    M = args['m']
    N = args['n']
    ITERATIONS = args['loops']
    ALGORITHM = args['algorithm']
    main()
