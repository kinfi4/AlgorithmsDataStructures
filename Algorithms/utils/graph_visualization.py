import matplotlib.pyplot as plt
import networkx as nx


def visualize_graph(graph_adj_matrix, graph: nx.Graph):
    for row_idx, row in enumerate(graph_adj_matrix, start=1):
        for node_idx, dist in enumerate(row, start=1):
            if dist != 0:
                graph.add_edge(row_idx, node_idx, weight=dist)

    pos = nx.spring_layout(graph, seed=21)  # 18 - 21 best

    # nodes
    nx.draw_networkx_nodes(graph, pos, node_size=200)

    # edges
    nx.draw_networkx_edges(graph, pos, width=3)
    nx.draw_networkx_edges(
        graph, pos, alpha=0.9, width=0.2
    )

    nx.draw_networkx_labels(graph, pos, font_size=12, font_family="sans-serif")

    edge_labels = nx.get_edge_attributes(graph, "weight")
    nx.draw_networkx_edge_labels(graph, pos, edge_labels)

    plt.show()
