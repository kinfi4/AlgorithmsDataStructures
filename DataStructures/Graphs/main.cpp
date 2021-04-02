#include <iostream>
#include "UndirectedGraph.h"

using namespace std;

int main() {
    auto matrix = vector<vector<int>>{
            {  0,  1,  1,  0,  1 },
            {  0,  0,  0,  1,  1 },
            {  0,  0,  0,  0,  1 },
            {  0,  0,  1,  0,  0 },
            {  0,  0,  0,  1,  0 },
    }; 
    auto names = vector<string>{"a", "b", "c", "d", "f"};

    auto graph = UnWeightedGraph<string>(matrix, names);
    graph.print();

    cout << "BFS:: ";
    graph.bfs("a");

    cout << endl << "DFS:: ";
    graph.dfs("a");

    return 0;
}
