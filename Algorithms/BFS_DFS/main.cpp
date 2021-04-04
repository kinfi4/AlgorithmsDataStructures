#include <iostream>

#include "UnweightedGraph.h"

using namespace std;

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


int main() {
    unweighted_graph();

    return 0;
}
