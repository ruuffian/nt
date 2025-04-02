# Computes and Benchmarks the Ackermann function:

#  A(m,n) -> {
#              n + 1               m=0
#              A(m-1, 1)           m>0 & n=0
#              A(m-1, A(m, n-1))   m>0 & n>0
#            }

import sys
import timeit
import argparse
import functools
import numpy as np

# ----- GLOBALS -----
M = 0
N = 0
ITERATIONS = 100


# ----- BENCHMARKING ------
def count_calls(fn):
    """Decorates a recursive function and counts each recursive call."""
    @functools.wraps(fn)
    def wrapper(*args, **kwargs):
        wrapper.calls += 1
        return fn(*args, **kwargs)
    wrapper.calls = 0
    return wrapper


def run_benchmark(fn, fn_str, descriptor, *args):
    """Run a function with recursive tracking, then benchmark it.
    Requres fn to be decorated with '@count_calls'
    """
    print(f'{fn_str}({M},{N}) => {{')
    val = fn(*args)
    calls = fn.calls
    print(f'\tFunction Return: {val}')
    print(f'\tTotal Recursive Calls: {calls}')
    print(f'\tBenchmarking {descriptor} alg...')
    marks = benchmark(fn_str)
    report_marks(fn_str, marks)


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
    print('}')


# ----- ALGORITHMS ----
@count_calls
def a(m, n):
    """Naive Ackermann function implementation."""
    if m == 0:
        return n + 1
    if n == 0:
        return a(m-1, 1)
    return a(m-1, a(m, n-1))


def memoized_a(m, n):
    """Utilizes a cache to skip branches after computing them once."""
    cache = {}

    @count_calls
    def _memoized_a(m, n):
        try:
            return cache[(m, n)]
        except KeyError:
            if m == 0:
                val = n + 1
                cache[(m, n)] = val
                return val
            if n == 0:
                val = _memoized_a(m-1, 1)
                cache[(m, n)] = val
                return val
            val = _memoized_a(m-1, _memoized_a(m, n-1))
            cache[(m, n)] = val
            return val
    val = _memoized_a(m, n)
    memoized_a.calls = _memoized_a.calls
    return val


@count_calls
def ackermann(i, n):
    """I read this in a paper and wanted to try implementing it with numpy"""
    next = np.arange(i+1) * 0
    goal = np.arange(i+1) * 0 + 1
    goal[i] = -1
    current = i
    while next[i] != n + 1:
        value = next[0] + 1
        transferring = True
        current = i
        while transferring:
            if next[i-current] == goal[i-current]:
                goal[i-current] = value
            else:
                transferring = False
            next[i-current] = next[i-current]+1
            current -= 1
    return value


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
    run_benchmark(ackermann, 'ackermann', 'Grossman-Zeitman', M, N)
    run_benchmark(memoized_a, 'memoized_a', 'cache-optimized', M, N)
    run_benchmark(a, 'a', 'naive', M, N)


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
        default=100

    )
    args = vars(parser.parse_args())
    M = args['m']
    N = args['n']
    ITERATIONS = args['loops']
    main()
