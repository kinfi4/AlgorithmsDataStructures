//
// Created by kini4 on 3/20/21.
//

#ifndef BITREE_NODE_H
#define BITREE_NODE_H
template<class T1, class T2>
class Node{
public:
    Node(T1 index, T2 data, Node<T1, T2> *parent, Node<T1, T2>* left_child= nullptr, Node<T1, T2>* right_child= nullptr){
        this->index = index;
        this->data = data;
        this->parent = parent;

        this->left_child = left_child;
        this->right_child = right_child;
    }

    T1 index;
    T2 data;
    Node<T1, T2> *left_child, *right_child;
    Node<T1, T2> *parent;
};


#endif //BITREE_NODE_H
