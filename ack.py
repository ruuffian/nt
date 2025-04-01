# Computes and Benchmarks the Ackermann function:

#  A(m,n) -> {
#              n + 1               m=0
#              A(m-1, 1)           m>0 & n=0
#              A(m-1, A(m, n-1))   m>0 & n>0
#            }

import sys
import timeit
import argparse

# Bounds on Ackermann inputs
M = 0
N = 0
ITERATIONS = 100


def a(m, n):
    """Naive Ackermann function implementation."""
    a.count += 1
    if m == 0:
        return n + 1
    if n == 0:
        return a(m-1, 1)
    return a(m-1, a(m, n-1))


def memoized_a(m, n):
    """Utilizes a cache to skip branches after computing them once."""

    cache = {}

    def _memoized_a(m, n):
        memoized_a.count += 1
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
    return _memoized_a(m, n)


def track_recursive_calls(fn, *args):
    """Wrap a recursive function to track total recursive calls.
        Returns:
            val - fn() return value
            count - Total recursive calls
    """
    fn.count = 0
    val = fn(*args)
    return val, fn.count


def avg(vals):
    return sum(vals) / len(vals)


def variance(vals):
    average = avg(vals)
    return sum([(x - average)**2 for x in vals]) / len(vals)


def std_dev(vals):
    return variance(vals)**0.5


def analyze_marks(raw_marks):
    marks = [x * 1000 for x in raw_marks]
    return marks, avg(marks), min(marks), max(marks), variance(marks), std_dev(marks)


def benchmark(fn_str, enable_gc=False):
    """Coordinate benchmark() calls on a function."""
    marks = timeit.repeat(stmt=f'{fn_str}(M, N)',
                          globals=globals(),
                          repeat=ITERATIONS,
                          number=1)
    return marks


def report_marks(fn_str, marks):
    times, avg, min, max, variance, std_dev = analyze_marks(marks)
    print(f'\tRuntime Metrics [{len(times)} loops] => {{')
    print(f'\t\tPeek (top 3): {sorted(times, reverse=True)[0:5]}')
    print(f'\t\tAverage: {avg} ms')
    print(f'\t\tMin time:  {min} ms')
    print(f'\t\tMax time:  {max} ms')
    print(f'\t\tVariance:  {variance}')
    print(f'\t\tStandard Deviation:  {std_dev}')
    print('\t}')
    print('}')


def run_benchmark(fn, fn_str, descriptor, enable_gc=False):
    """Run and print a benchmark for a fn."""
    print(f'{fn_str}({M},{N}) => {{')
    ackermann, calls = track_recursive_calls(fn, M, N)
    print(f'\tAckermann Number: {ackermann}')
    print(f'\tTotal Recursive Calls: {calls}')
    print(f'\tBenchmarking {descriptor} Ackermann function...')
    marks = benchmark(fn_str, enable_gc)
    report_marks(fn_str, marks)


def main():
    sys.setrecursionlimit(10**6)
    run_benchmark(memoized_a, 'memoized_a', 'cache-optimized', True)
    run_benchmark(a, 'a', 'naive')


if __name__ == "__main__":
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
