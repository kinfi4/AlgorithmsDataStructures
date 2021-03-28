#include <iostream>
#include <vector>

#include "matrix.h"
#include "list_edges.h"
#include "list_adjacency.h"


void first_task(){
    auto matrix = vector<vector<int>>{
            {1, 1, 1, 0, 0, 1},
            {1, 1, 0, 1, 0, 1},
            {1, 0, 0, 1, 1, 0},
            {0, 1, 1, 0, 1, 0},
            {0, 0, 1, 1, 0, 0},
            {1, 1, 0, 0, 0, 0}
    };

    auto graph = MatrixAdjacencyUndirected<string>(matrix);
    graph.add_names(vector<string>{"a", "b", "c", "d", "e", "f"});
    graph.print();

    auto graph2 = graph.create_incidence_matrix();
    auto graph3 = graph2.get_list_adjacency();
    auto graph4 = graph2.get_list_edges();

    graph2.print();
    graph3.print();
    graph4.print();
}

int main() {

    first_task();

    return 0;
}
