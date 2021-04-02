//
// Created by kinfi4 on 3/22/21.
//

#ifndef GRAPH_UNDIRECTEDGRAPH_H
#define GRAPH_UNDIRECTEDGRAPH_H
#include "Node.h"
#include "BaseGraph.h"
#include <vector>
#include <queue>
#include <stack>

using namespace std;

template <class T>
class UnWeightedGraph: public BaseGraph<T>{
public:
    UnWeightedGraph(vector<vector<int>> matrix, vector<T> names){
        if(matrix.size() != names.size())
            throw invalid_argument("Matrix size must be equal to names size");

        auto new_nodes = vector<Node<T>*>();
        for (int i = 0; i < matrix.size(); ++i) {
            new_nodes.push_back(new Node<T>(names[i]));
        }

        for (int i = 0; i < matrix.size(); ++i) {
            auto neighbors = vector<Node<T>*>();
            for (int j = 0; j < matrix[i].size(); ++j) {
                if(matrix[i][j] > 0){
                    neighbors.push_back(new_nodes[j]);
                }
            }

            this->_graph.push_back(pair<Node<T>*, vector<Node<T>*>>(new_nodes[i], neighbors));
        }
    }

    void bfs(T start_node){
        queue<Node<T>*> queue;
        auto visited = vector<T>();

        queue.push(this->_find_node_by_name(start_node));
        visited.push_back(start_node);

        while (not queue.empty()){
            auto cur_node_name = queue.front()->name;
            cout << cur_node_name << " -> ";

            queue.pop();

            for(auto& node : this->_get_node_neighbors(cur_node_name)){
                if(not this->_is_visited(node->name, visited)){
                    visited.push_back(node->name);
                    queue.push(node);
                }
            }
        }
    }

    void dfs(T start_node){
        stack<Node<T>*> stack;
        auto visited = vector<T>();

        stack.push(this->_find_node_by_name(start_node));

        while(not stack.empty()){
            auto cur_node_name = stack.top()->name;
            stack.pop();

            if(not this->_is_visited(cur_node_name, visited)){
                cout << cur_node_name << " -> ";
                visited.push_back(cur_node_name);
            }

            for(auto& node : this->_get_node_neighbors(cur_node_name)){
                if(not this->_is_visited(node->name, visited)){
                    stack.push(node);
                }
            }
        }
    }

};



#endif //GRAPH_UNDIRECTEDGRAPH_H
