#include <iostream>
#include <vector>

#include "matrix.h"
#include "list_edges.h"
#include "list_adjacency.h"


void undirected_task(){
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
    graph2.print();

    auto graph3 = graph2.create_adjacency_matrix();
    graph3.print();

    graph.get_list_edges().print();
    graph2.get_list_adjacency().print();

}

void directed_task(){
    auto matrix = vector<vector<int>>{
            {  0,  1,  1,  0,  1},
            {  0,  0,  0,  1,  1},
            {  0,  0,  0,  0,  1},
            {  0,  0,  1,  0,  0},
            {  0,  0,  0,  1,  0},
    };

    auto undir_graph = MatrixAdjacencyDirected<string>(matrix);
    undir_graph.add_names(vector<string>{"a", "b", "c", "d", "f"});
    undir_graph.print();

    auto dir_graph = undir_graph.create_incidence_matrix();
    dir_graph.print();

    dir_graph.get_list_adjacency().print();
    dir_graph.get_list_edges().print();

    dir_graph.create_adjacency_matrix().print();

}


int main() {

    directed_task();

    return 0;
}
