from typing import override

"""
Take in a list of facts (str, float, str)
Process a list of queries (float, str, str)
"""

"""
Much harder than I thought- needs to be represented as a graph to allow
conversions from m -> ft -> in when only given m -> ft and ft -> in (one
example).
"""
"""
Two data structures:
    Dictionary storing string (unit) and nodes (child units, float value)
"""


class Edge:
    def __init__(self, weight: float, parent: str, child: str):
        self.weight: float = weight
        self.parent: str = parent
        self.child: str = child

    @override
    def __repr__(self):
        return f"{self.parent} --{self.weight}--> {self.child}"


def parse_facts(facts: list[tuple[str, float, str]]) -> dict[str, list[Edge]]:
    unit_edges: dict[str, list[Edge]] = {}
    for fact in facts:
        unit, weight, target = fact
        edge = Edge(weight, unit, target)
        if unit not in unit_edges:
            unit_edges[unit] = [edge]
        else:
            unit_edges[unit].append(edge)
    return unit_edges


facts = [
    ("m", 3.28, "ft"),
    ("m", 100, "cm"),
    ("ft", 12, "in"),
    ("hr", 60, "min"),
    ("min", 60, "sec"),
]

conversions = parse_facts(facts)


def process_query(val: float, unit: str, target: str) -> float | None:
    pass


def bfs(current: str, target: str, path: list[str]):
    """Needs to return a path to a target node, or None if one does not exist"""
    path.append(current)
    if current == target:
        # return the path to get here
        return path
    valid_edges = conversions[current]
    for edge in valid_edges:
        if edge in path:
            # Avoid circular paths
            continue
        else:
            new_path = 
        











