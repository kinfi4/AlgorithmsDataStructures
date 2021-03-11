//
// Created by kini4 on 3/2/21.
//

#include <vector>

using namespace std;

#ifndef GRAPH_GRAPH_H
#define GRAPH_GRAPH_H

template <class T>
class MyGraph{
public:
    static MyGraph<T> GraphFromMatrix(vector<vector<T
    >>);

private:
    template <class T1>
    class Node{
    public:
        Node(T1 name, MyGraph<T1> &graph){
            this->name = name;
            this->graph = graph;
        }

    private:
        T1 name;
        MyGraph<T1> graph;
    };

    vector<vector<T>> graph_matrix;
    vector<Node<T>> nodes;
};

template<class T>
MyGraph<T> MyGraph<T>::GraphFromMatrix(vector<vector<T>> matrix) {
    auto new_graph = MyGraph();
    new_graph.graph_matrix = matrix;

    for(auto list : matrix){
        for(auto element : list){

        }
    }

    return new_graph;
}


#endif //GRAPH_GRAPH_H
