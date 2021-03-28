//
// Created by kinfi4 on 3/22/21.
//

#ifndef GRAPH_UNDIRECTEDGRAPH_H
#define GRAPH_UNDIRECTEDGRAPH_H
#include "Node.h"
#include <vector>
#include <string>

using namespace std;

template <class T, class D>
class UndirectedGraph{
public:

    int size();
    bool is_empty();

    UndirectedGraph(){
        this->_size = 0;
    }

    UndirectedGraph(vector<pair<Node<T, D>*, vector<Node<T, D>*>>> graph){
        this->_graph = graph;
    }

    void add_node(T name, D data);
    void add_nodes_from_vector(vector<pair<T, D>> nodes);

    void add_edge(T name1, T name2);
    void add_edges_from_vector(vector<pair<T, T>> nodes);

    vector<vector<bool>> get_matrix_adjacency();

    static UndirectedGraph<int, D> graph_from_matrix_adjacency(vector<vector<bool>> matrix);
    static UndirectedGraph<T, D> graph_from_list(vector<pair<Node<T, D>*, vector<Node<T, D>*>>> graph);
private:
    vector<pair<Node<T, D>*, vector<Node<T, D>*>>> _graph;
    int _size;

    Node<T, D>* _find_node(T name);
};

template<class T, class D>
void UndirectedGraph<T, D>::add_node(T name, D data) {
    this->_graph.push_back(pair<Node<T, D>*, vector<Node<T, D>*>>(new Node<T, D>(name, data), vector<Node<T, D>*>()));
}

template<class T, class D>
void UndirectedGraph<T, D>::add_nodes_from_vector(vector<pair<T, D>> nodes) {
    for(auto pair : nodes){
        this->add_node(pair.first, pair.second);
    }
}

template<class T, class D>
void UndirectedGraph<T, D>::add_edge(T name1, T name2) {
    Node<T, D>* node1;
    try{
        node1 = this->_find_node(name2);
    }catch (...){
        throw invalid_argument("Cant find the node or nodes with this name/names");
    }

    for(auto block : this->_graph){
        if(block.first->name == name1){
            block.second.push_back(node1);
            return;
        }
    }

    throw invalid_argument("Cant find the node or nodes with this name/names");
}

template<class T, class D>
Node<T, D> *UndirectedGraph<T, D>::_find_node(T name) {
    for(auto block : this->_graph){
        if(block.first->name == name){
            return block.first;
        }
    }

    throw invalid_argument("Cant find the node with this name");
}

template<class T, class D>
void UndirectedGraph<T, D>::add_edges_from_vector(vector<pair<T, T>> nodes) {
    for(auto pair : nodes){
        this->add_edge(pair.first, pair.second);
    }
}

template<class T, class D>
UndirectedGraph<T, D> UndirectedGraph<T, D>::graph_from_list(vector<pair<Node<T, D> *, vector<Node<T, D> *>>> graph) {
    return UndirectedGraph<T, D>(graph);
}

template<class T, class D>
UndirectedGraph<int, D> UndirectedGraph<T, D>::graph_from_matrix_adjacency(vector<vector<bool>> matrix) {
    auto graph = UndirectedGraph<int, D>();

    for(int i = 0; i < matrix.size(); i++)
        graph.add_node(i, D());

    for(int k = 0; k < matrix.size(); k++){
        for(int i = 0; i < matrix[k].size(); i++){
            if(matrix[k][i])
                graph.add_edge(k, i);
        }
    }

    return graph;
}

template<class T, class D>
int UndirectedGraph<T, D>::size() {
    return this->_size;
}

template<class T, class D>
bool UndirectedGraph<T, D>::is_empty() {
    return this->_size == 0;
}

template<class T, class D>
vector<vector<bool>> UndirectedGraph<T, D>::get_matrix_adjacency() {
    auto matrix = vector<vector<bool>>();


}


#endif //GRAPH_UNDIRECTEDGRAPH_H
