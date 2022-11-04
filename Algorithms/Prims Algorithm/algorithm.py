from typing import List, Set

import networkx as nx
import numpy as np

from utils.graph_visualization import visualize_graph


def search_closest_node(graph_matrix, visited):
    min_weight = max(row[i] for row in graph_matrix for i in range(len(row)))
    min_index = -1

    for visited_index in visited:
        for index, weight in enumerate(graph_matrix[visited_index]):
            if 0 < weight < min_weight and index not in visited:
                min_weight = weight
                min_index = index

    return [min_weight, min_index]


def prims_algorithm(graph_matrix: List[List[int]], starting_node: int):
    nodes = [(starting_node + 1, 0)]
    visited = {starting_node}
    to_visit = [i for i in range(len(graph_matrix)) if i != starting_node]

    for node in to_visit:
        weight, index = search_closest_node(graph_matrix, visited)
        nodes.append((index + 1, weight))
        visited.add(index)

    return nodes


D = [
    [0, 0, 1, 0, 0, 0, 0, 0],  # 1
    [0, 0, 3, 1, 0, 1, 0, 0],  # 2
    [1, 3, 0, 0, 2, 2, 0, 2],  # 3
    [0, 1, 0, 0, 0, 0, 3, 2],  # 4
    [0, 0, 2, 0, 0, 5, 2, 5],  # 5
    [0, 1, 2, 0, 5, 0, 1, 3],  # 6
    [0, 0, 0, 3, 2, 1, 0, 2],  # 7
    [0, 0, 2, 2, 5, 3, 2, 0],  # 8
]


if __name__ == '__main__':
    result = prims_algorithm(D, 0)

    print(result)


visualize_graph(np.array(D), nx.Graph())
