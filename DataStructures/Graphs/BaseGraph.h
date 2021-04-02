//
// Created by kinfi4 on 4/2/21.
//

#ifndef GRAPHS_BASEGRAPH_H
#define GRAPHS_BASEGRAPH_H

#include "Node.h"
#include <vector>

using namespace std;

template <class T>
class BaseGraph{
public:
    void print(){
        for(auto& pair : this->_graph){
            cout << pair.first->name << " -- ";
            for(auto& node : pair.second)
                cout << node->name << " ";

            cout << endl;
        }

        cout << endl;
    }


protected:
    vector<pair<Node<T>*, vector<Node<T>*>>> _graph;
    Node<T>* _find_node_by_name(T node_name){
        for(auto& pair : this->_graph){
            if(pair.first->name == node_name)
                return pair.first;
        }

        throw invalid_argument("Can find the start node in the graph");
    }
    vector<Node<T>*> _get_node_neighbors(T node_name){
        for(auto& pair : this->_graph){
            if(pair.first->name == node_name)
                return pair.second;
        }

        throw invalid_argument("Can find the start node in the graph");
    }
    bool _is_visited(T node_name, vector<T>& visited){
        for(auto& name : visited){
            if(name == node_name)
                return true;
        }

        return false;
    }

};

#endif //GRAPHS_BASEGRAPH_H
