//
// Created by kinfi4 on 3/22/21.
//

#ifndef GRAPH_NODE_H
#define GRAPH_NODE_H
#include "BaseGraph.h"

template <class T, class D>
class Node{
public:
    Node(T name, D data, BaseGraph<T>* graph);

private:
    BaseGraph<T>* graph;
    D data;
    T name;
};

template<class T, class D>
Node<T, D>::Node(T name, D data, BaseGraph<T>* graph) {
    this->graph = graph;
    this->data = data;
    this->name = name;
}

#endif //GRAPH_NODE_H
