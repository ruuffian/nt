#!/usr/bin/env python
# Computes and Benchmarks the Ackermann function:
import sys
import timeit
import time
import argparse
import numpy as np
from ackermann import naive, lru, memoized, iterative

# ----- GLOBALS -----
M = 0
N = 0
ITERATIONS = 0


# ----- BENCHMARKING ------
def benchmark(fn_str):
    """Coordinate calls on a function."""
    SETUP = f"""
if ALGORITHM == 'lru':
    {fn_str}.cache_clear()
"""
    marks = timeit.repeat(
        stmt=f"{fn_str}(M, N)",
        globals=globals(),
        setup=SETUP,
        repeat=ITERATIONS,
        number=1,
    )
    return marks


def report_marks(fn_str, marks):
    times, avg, min, max, median, variance, std_dev = analyze_marks(marks)
    print(f"Runtime Metrics [{len(times)} loops] => {{")
    print(f"\tPeek (top 5): {sorted(times, reverse=True)[0:5]}")
    print(f"\tAverage: {avg} (ms)")
    print(f"\tMedian: {median} (ms)")
    print(f"\tMin time:  {min} (ms)")
    print(f"\tMax time:  {max} (ms)")
    print(f"\tVariance:  {variance}")
    print(f"\tStandard Deviation:  {std_dev}")
    print("}")


# ----- DATA ANALYSIS ------
def analyze_marks(raw_marks):
    """Recieves a list of marks and calculates basic summary statistics.
    This area had a bit more before adding NumPy.
    """
    # Seconds -> Milliseconds
    marks = np.array(raw_marks, dtype=float)
    marks = marks * 1000
    return (
        marks,
        np.mean(marks),
        np.min(marks),
        np.max(marks),
        np.median(marks),
        np.var(marks),
        np.std(marks),
    )


# ----- SCRIPT -----
def main():
    # Default recursion limit too low for the Ackermann function
    sys.setrecursionlimit(10**6)
    fns = {"naive": naive, "memoized": memoized, "lru": lru, "iterative": iterative}
    print(f"{ALGORITHM}({M},{N})=", end=" ")
    fn = fns[ALGORITHM]
    m = M
    n = N
    start = time.perf_counter_ns()
    val = fn(m, n)
    end = time.perf_counter_ns()
    # calls = fn.calls
    print(val)
    # print(f'\tTotal Recursive Calls: {calls}')
    print(f"Runtime: {(end - start) / 1e6} (ms)")
    if ITERATIONS > 0:
        print(f"Benchmarking {ALGORITHM} alg...")
        marks = benchmark(ALGORITHM)
        report_marks(ALGORITHM, marks)


if __name__ == "__main__":
    # Can't access M, N, or ITERATIONS from main() function
    parser = argparse.ArgumentParser(
        description="Benchmarks varius Ackermann's function implementations against each other."
    )
    parser.add_argument("m", type=int, help="First argument to Ackermann's function.")
    parser.add_argument("n", type=int, help="Second argument to Ackermann's function.")
    parser.add_argument(
        "--loops",
        "-l",
        type=int,
        help="The number of iterations to use for benchmarking.",
        default=0,
    )
    parser.add_argument(
        "--algorithm",
        "-a",
        help="Choosing the algorithm to calculate with.",
        choices=["naive", "memoized", "iterative", "lru"],
        default="naive",
    )
    args = vars(parser.parse_args())
    M = args["m"]
    N = args["n"]
    ITERATIONS = args["loops"]
    ALGORITHM = args["algorithm"]
    main()
