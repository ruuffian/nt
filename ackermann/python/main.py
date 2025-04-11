#!/usr/bin/env python
# Computes and Benchmarks the Ackermann function:
import sys
import timeit
import time
import argparse
from typing import Callable
import numpy as np
from ackermann import naive, cached, memoized, iterative

# ----- GLOBALS -----
m = 0
n = 0
iterations = 0
algorithm = "naive"


# ----- BENCHMARKING ------
def benchmark(fn_str: str):
    """Coordinate calls on a function."""
    SETUP = f"""
if ALGORITHM == 'lru':
    {fn_str}.cache_clear()
"""
    marks = timeit.repeat(
        stmt=f"{fn_str}(M, N)",
        globals=globals(),
        setup=SETUP,
        repeat=iterations,
        number=1,
    )
    return marks


def report_marks(marks: list[float]):
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
def analyze_marks(raw_marks: list[float]):
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
    fns: dict[str, Callable[[int, int], int]] = {
        "naive": naive,
        "memoized": memoized,
        "cached": cached,
        "iterative": iterative,
    }
    print(f"{algorithm}({m},{n})=", end=" ")
    fn = fns[algorithm]
    start = time.perf_counter_ns()
    val = fn(m, n)
    end = time.perf_counter_ns()
    # calls = fn.calls
    print(val)
    # print(f'\tTotal Recursive Calls: {calls}')
    print(f"Runtime: {(end - start) / 1e6} (ms)")
    if iterations > 0:
        print(f"Benchmarking {algorithm} alg...")
        marks = benchmark(algorithm)
        report_marks(marks)


if __name__ == "__main__":
    # Can't access M, N, or ITERATIONS from main() function
    parser = argparse.ArgumentParser(
        description="Benchmarks varius Ackermann's function implementations against each other."
    )
    _ = parser.add_argument(
        "m", type=int, help="First argument to Ackermann's function."
    )
    _ = parser.add_argument(
        "n", type=int, help="Second argument to Ackermann's function."
    )
    _ = parser.add_argument(
        "--loops",
        "-l",
        type=int,
        help="The number of iterations to use for benchmarking.",
        default=0,
    )
    _ = parser.add_argument(
        "--algorithm",
        "-a",
        help="Choosing the algorithm to calculate with.",
        choices=["naive", "memoized", "iterative", "cached"],
        default="naive",
    )
    args = vars(parser.parse_args())
    m: int = args["m"]
    n: int = args["n"]
    iterations: int = args["loops"]
    algorithm: str = args["algorithm"]
    main()
