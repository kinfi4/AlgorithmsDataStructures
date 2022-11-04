import math

import networkx as nx
import numpy as np

from utils.graph_visualization import visualize_graph


def get_linked_nodes(start_node_index, graph_matrix):
    """ Finds all the nodes that are linked to the start_node_index """
    for node_i, weight in enumerate(graph_matrix[start_node_index]):
        if weight > 0:
            yield node_i


def arg_min(weights, seen):
    """ Finds the lowest value of weight for node which is not in seen """
    min_index = -1
    min_value = max(weights)

    for index, weight in enumerate(weights):
        if weight < min_value and index not in seen:
            min_value = weight
            min_index = index

    return min_index


def dijkstra(graph_matrix, start_node):
    """ Gets the graph matrix and index of start node, and returns the list of weights """
    weights = [math.inf] * len(graph_matrix)
    weights[start_node] = 0
    seen = {start_node}

    while start_node != -1:
        for neighbor in get_linked_nodes(start_node, graph_matrix):
            if neighbor not in seen:
                neighbor_weight = weights[start_node] + graph_matrix[start_node][neighbor]
                if neighbor_weight < weights[neighbor]:
                    weights[neighbor] = neighbor_weight

        start_node = arg_min(weights, seen)
        if start_node > 0:
            seen.add(start_node)

    return weights


#        1  2  3  4  5  6  7  8
D = (
        (0, 0, 3, 0, 0, 3, 0, 0),  # 1
        (0, 0, 0, 3, 0, 1, 0, 2),  # 2
        (0, 0, 0, 0, 0, 0, 0, 0),  # 3
        (0, 1, 0, 0, 0, 0, 0, 2),  # 4
        (0, 0, 2, 0, 0, 2, 0, 0),  # 5
        (0, 0, 2, 0, 5, 0, 1, 0),  # 6
        (0, 3, 0, 3, 2, 1, 0, 4),  # 7
        (0, 0, 0, 0, 5, 3, 2, 0),  # 8
)


distances = dijkstra(D, 1)

for idx, distance in enumerate(distances, start=1):
    print(f'Index: {idx} - distance: {distance}')


visualize_graph(np.array(D), nx.OrderedDiGraph())
