#include <iostream>
#include <vector>
#include "WeightedGraph.h"

using namespace std;


void _print_matrix(vector<vector<int>> matrix, vector<string> names){
    for(auto& name : names)
        cout << "    " << name << "";

    cout << endl << endl;

    for(int i = 0; i < matrix.size(); ++i){
        cout << names[i] << "   ";
        for(auto& el : matrix[i]){
            if(el == INT_MAX)
                cout << "inf" << "  ";
            else
                cout << el << "    ";
        }

        cout << endl;
    }
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

    cout << "========================================" << endl;

    auto distances = graph.dijkstra("a");
    cout << "Distances from a:  ";
    for(auto& dist : distances){
       if(dist.second == INT_MAX)
            cout << dist.first << ":" << "inf" << "   ";
       else
           cout << dist.first << ":" << dist.second << "   ";
    }

    cout << endl;
    cout << "========================================" << endl;
    _print_matrix(graph.floyd(), {"a", "b", "c", "d", "e", "f"});
}


int main() {
    weighted_graph();

    return 0;
}
