from functools import cache


# ----- ALGORITHMS ----
def naive(m, n):
    """Naive Ackermann function implementation."""
    if m == 0:
        return n + 1
    if n == 0:
        return naive(m - 1, 1)
    return naive(m - 1, naive(m, n - 1))


@cache
def lru(m, n):
    """Despite being about a millisecond faster than the home-grown
    memoization, this function absolutely explodes as soon as you give it more
    more than a(3, 10) unless you CRANK the max recursion limit.
    """
    if m == 0:
        return n + 1
    if n == 0:
        return lru(m - 1, 1)
    return lru(m - 1, lru(m, n - 1))


def memoized(m, n):
    """I cheated by reading the functools source code to learn some small
    optimizations like calculating a key rather than useing a large object
    and giving a default return to cache.get() to check if the key exists
    instead of using a KeyError. I should have noticed the KeyError 'smell'
    immediately but I was busy fighting other battles. I hope I take this as a
    lesson that writing extremely performant code should ALMOST NEVER interact
    with Exceptions EXCEPT WHEN NECESSARY!

    I have basically re-implemented the @lru_cache decorator, but with a much
    faster make_key() function because I KNOW my key type ahead of time. Neat!

    I was convinced that pair enumeration would be the fastest way to compute a
    cache key, but after several rounds of testing it seems that hashing a
    tuple is just by far the fastest operation. I even tried implementing the
    enumeration in C and importing it at runtime, but even that was slower than
    tuple hashing. Sadge! lru_cache still beats my alg by about a millisecond,
    which is driving me crazy. HOWEVER, lru_cache encounters stack overflows
    WAY before my implementation because each recursive call is actually 2
    function calls, vs my implementation only having 1. Decorators carry hidden
    costs, always remember that!
    """
    sentinel = object()
    cache = {}
    cache_get = cache.get

    def _(m, n):
        key = (m, n)
        result = cache_get(key, sentinel)
        if result is not sentinel:
            return result
        else:
            val = n + 1
            if m == 0:
                cache[key] = val
                return val
            if n == 0:
                val = _(m - 1, 1)
                cache[key] = val
                return val
            val = _(m - 1, _(m, n - 1))
            cache[key] = val
            return val

    return _(m, n)


def iterative(i, n):
    """I read this in a paper and wanted to try implementing it with numpy.
    I'm **pretty** sure the extra load time is worth using numpy for vector
    operations, but now that I'm thinking about it the entire algorithm is
    iterative anyways...hmm.
    """
    import numpy as np

    next = np.arange(i + 1) * 0
    goal = np.arange(i + 1) * 0 + 1
    goal[i] = -1
    current = i
    while next[i] != n + 1:
        value = next[0] + 1
        transferring = True
        current = i
        while transferring:
            if next[i - current] == goal[i - current]:
                goal[i - current] = value
            else:
                transferring = False
            next[i - current] = next[i - current] + 1
            current -= 1
    return value
