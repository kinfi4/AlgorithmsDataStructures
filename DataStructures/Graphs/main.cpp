#include <iostream>
#include "UnweightedGraph.h"
#include "WeightedGraph.h"

using namespace std;

void _print_matrix(vector<vector<int>> matrix){
    for(auto& row : matrix){
        for(auto& el : row)
            cout << el << " ";

        cout << endl;
    }
}

void unweighted_graph(){
    auto matrix = vector<vector<int>>{
            {  0,  1,  1,  0,  1 },
            {  0,  0,  0,  1,  1 },
            {  0,  0,  0,  0,  1 },
            {  0,  0,  1,  0,  0 },
            {  0,  0,  0,  1,  0 },
    };
    auto names = vector<string>{"a", "b", "c", "d", "f"};

    auto graph = UnweightedGraph<string>(matrix, names);
    graph.print();

    cout << "BFS:: ";
    graph.bfs("a");

    cout << endl << "DFS:: ";
    graph.dfs("a");
}

void weighted_graph(){
    vector<vector<int>> weights = {
            {0, 3, 0, 0,  0, 9},
            {0, 0, 0, 2,  0, 5},
            {4, 0, 0, 12, 9, 0},
            {0, 0, 0, 0,  4, 0},
            {0, 0, 0, 0,  0, 0},
            {0, 0, 0, 0,  0, 0},
    };

    vector<string> names = {"a", "b", "c", "d", "e", "f"};

    auto graph = WeightedGraph<string>(weights, names);
    graph.print();
}

int main() {
//    unweighted_graph();
    weighted_graph();


    return 0;
}
