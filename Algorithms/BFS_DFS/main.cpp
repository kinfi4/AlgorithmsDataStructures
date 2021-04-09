#include <iostream>

#include "UnweightedGraph.h"

using namespace std;

void undirected(){
    auto matrix = vector<vector<int>>{
            {  1,  1,  1,  0,  0,  1 },
            {  1,  1,  0,  1,  0,  1 },
            {  1,  0,  0,  1,  1,  0 },
            {  0,  1,  1,  0,  1,  0 },
            {  0,  0,  1,  1,  0,  0 },
            {  1,  1,  0,  0,  0,  0 },
    };
    auto names = vector<string>{"a", "b", "c", "d", "e", "f"};

    auto graph = UnweightedGraph<string>(matrix, names);
    graph.print();

    cout << "BFS:: ";
    graph.bfs("a");

    cout << endl << "DFS:: ";
    graph.dfs("a");
}

void directed(){
    auto matrix = vector<vector<int>>{
            {  0,  1,  1,  0,  1  },
            {  0,  0,  0,  1,  1  },
            {  0,  0,  0,  0,  1  },
            {  0,  0,  1,  0,  0  },
            {  0,  0,  0,  1,  0  },
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
    directed();
    cout << endl << "==============================================" << endl;
    undirected();


    return 0;
}
