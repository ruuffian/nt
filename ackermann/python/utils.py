import functools


def count_calls(fn):
    """Decorates a recursive function and counts each recursive call."""

    @functools.wraps(fn)
    def wrapper(*args, **kwargs):
        wrapper.calls += 1
        return fn(*args, **kwargs)

    wrapper.calls = 0
    return wrapper
