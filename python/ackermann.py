import numpy as np
from utils import count_calls


# ----- ALGORITHMS ----
@count_calls
def A(m, n):
    """Naive Ackermann function implementation."""
    if m == 0:
        return n + 1
    if n == 0:
        return A(m-1, 1)
    return A(m-1, A(m, n-1))


def memoized_A(m, n, count=False):
    """Utilizes a cache to skip branches after computing them once."""
    cache = {}

    @count_calls
    def _(m, n):
        try:
            return cache[(m, n)]
        except KeyError:
            if m == 0:
                val = n + 1
                cache[(m, n)] = val
                return val
            if n == 0:
                val = _(m-1, 1)
                cache[(m, n)] = val
                return val
            val = _(m-1, _(m, n-1))
            cache[(m, n)] = val
            return val
    val = _(m, n)
    memoized_A.calls = _.calls
    return val


@count_calls
def iterative_A(i, n):
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
