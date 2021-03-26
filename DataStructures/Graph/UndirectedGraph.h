//
// Created by kinfi4 on 3/22/21.
//

#ifndef GRAPH_UNDIRECTEDGRAPH_H
#define GRAPH_UNDIRECTEDGRAPH_H
#include "BaseGraph.h"
#include "Node.h"

template <class T, class D>
class UndirectedGraph: BaseGraph<T, D>{
public:
    void add_node(T name, D data) override;
};

template<class T, class D>
void UndirectedGraph<T, D>::add_node(T name, D data) {

}

#endif //GRAPH_UNDIRECTEDGRAPH_H
