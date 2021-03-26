//
// Created by kinfi4 on 3/22/21.
//

#ifndef GRAPH_BASEGRAPH_H
#define GRAPH_BASEGRAPH_H
#include <vector>

template <class T, class D>
class BaseGraph{
public:
    virtual void add_node(T name, D data);
    virtual void add_edge(T name1, T name2);

    virtual void add_nodes_from_vector();
};

#endif //GRAPH_BASEGRAPH_H
