//
// Created by kinfi4 on 3/22/21.
//

#ifndef GRAPH_NODE_H
#define GRAPH_NODE_H

template <class T>
class Node{
public:
    Node(T name){
        this->name = name;
    }

    T name;
};


#endif //GRAPH_NODE_H
