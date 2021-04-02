//
// Created by kinfi4 on 3/28/21.
//
#ifndef FUCKING_ASD_LAB_MATRIX_H
#define FUCKING_ASD_LAB_MATRIX_H

#include <vector>

#include "list_adjacency.h"
#include "list_edges.h"

using namespace std;

template <class T>
class MatrixAdjacencyDirected;

template <class T>
class MatrixAdjacencyUndirected;

template <class T>
class MatrixIncidenceDirected;

template <class T>
class MatrixIncidenceUndirected;


// =====================================================================================================================
// Incidence matrix

template <class T>
class BaseMatrixIncidence{
public:
    void print(){
        cout << "   ";
        for (int i = 0; i < this->edges_names.size(); ++i)
            cout << this->edges_names[i] << ' ';

        cout << endl;

        for (int i = 0; i < this->matrix.size(); ++i) {
            cout << this->names[i] << "  ";

            for(auto value : this->matrix[i]){
                if(value >= 0)
                    cout << " " << value << "  ";
                else
                    cout << "" << value << "  ";
            }

            cout << endl;
        }

        cout << "\n\n\n";
    }
    void add_names(vector<T>& names) {
        this->names = names;
    }
    void add_edges_names(vector<string>& names){
        this->edges_names = names;
    }

    ListEdges<T> get_list_edges(){
        auto list = vector<pair<T, T>>();
        for(auto& edge_name : this->edges_names){
            string first;
            first += edge_name[0];

            string second;
            second += edge_name[2];

            list.emplace_back(second, first);
        }

        auto list_edges = ListEdges<T>(list);
        return list_edges;
    }

protected:
    vector<T> names;
    vector<string> edges_names;
    vector<vector<int>> matrix;
};

template <class T>
class MatrixIncidenceDirected: public BaseMatrixIncidence<T>{
public:
    MatrixIncidenceDirected(vector<vector<int>>& matrix){
        this->matrix = matrix;
    }

    MatrixAdjacencyUndirected<T> create_adjacency_matrix() {
        auto matrix = vector<vector<int>>();

        auto node_edges = vector<pair<int, int>>();
        for (int i = 0; i < this->matrix.size(); ++i) {
            for (int j = 0; j < this->matrix[i].size(); ++j) {
                if (this->matrix[i][j] > 0) {
                    auto edge = _find_indexes_of_edge(this->edges_names[j]);
                    node_edges.push_back(edge);
                }
            }
        }

        for (int i = 0; i < this->matrix.size(); ++i) {
            auto values = vector<int>();
            for (int j = 0; j < this->matrix.size(); ++j) {
                bool found = false;
                for(auto pair : node_edges){
                    if(i == pair.first and j == pair.second){
                        values.push_back(1);
                        found = true;
                        break;
                    }
                }

                if(not found)
                    values.push_back(0);
            }
            matrix.push_back(values);
        }

        auto graph = MatrixAdjacencyUndirected<T>(matrix);
        graph.add_names(this->names);
        return graph;
    }
    ListAdjacency<T> get_list_adjacency(){
        auto pairs = vector<pair<T, vector<T>>>();
        for (int i = 0; i < this->matrix.size(); ++i) {
            auto neighbors = vector<T>();
            for (int j = 0; j < this->matrix[i].size(); ++j) {
                if(this->matrix[i][j] > 0){
                    string neighbor;
                    neighbor += this->edges_names[j][2];

                    neighbors.push_back(neighbor);
                }
            }

            pairs.emplace_back(this->names[i], neighbors);
        }

        auto list_adjacency = ListAdjacency<T>(pairs);
        return list_adjacency;
    }

private:
    pair<int, int> _find_indexes_of_edge(string edge){
        string edge1, edge2;
        edge1 += edge[0];
        edge2 += edge[2];

        int index1 = 0, index2 = 0;
        for (int i = 0; i < this->names.size(); ++i) {
            if(this->names[i] == edge1)
                index1 = i;
            if(this->names[i] == edge2)
                index2 = i;
        }

        return pair<int, int>(index1, index2);
    }
};
template <class T>
class MatrixIncidenceUndirected: public BaseMatrixIncidence<T>{
public:
    MatrixIncidenceUndirected(vector<vector<int>>& matrix){
        this->matrix = matrix;
    }
    MatrixAdjacencyUndirected<T> create_adjacency_matrix() {
        auto matrix = vector<vector<int>>();

        auto node_edges = vector<pair<int, int>>();
        for (int i = 0; i < this->matrix.size(); ++i) {
            for (int j = 0; j < this->matrix[i].size(); ++j) {
                if (this->matrix[i][j] > 0) {
                    auto edge = _find_indexes_of_edge(this->edges_names[j]);
                    node_edges.push_back(edge);
                }
            }
        }

//        cout << "DEBUG" << endl;
//        for(auto v : node_edges){
//            cout << v.first << v.second << " ";
//        }
//        cout << endl;

        for (int i = 0; i < this->matrix.size(); ++i) {
            auto values = vector<int>();
            for (int j = 0; j < this->matrix.size(); ++j) {
                bool found = false;
                for(auto pair : node_edges){
                    if(i == pair.first and j == pair.second or i == pair.second and j == pair.first){
//                        cout << "Found " << i << " " << j << " ---- ";
                        values.push_back(1);
                        found = true;
                        break;
                    }
                }

                if(not found)
                    values.push_back(0);
            }
            matrix.push_back(values);
        }

        auto graph = MatrixAdjacencyUndirected<T>(matrix);
        graph.add_names(this->names);
        return graph;
    }
    ListAdjacency<T> get_list_adjacency(){
        auto pairs = vector<pair<T, vector<T>>>();
        for (int i = 0; i < this->matrix.size(); ++i) {
            auto neighbors = vector<T>();
            for (int j = 0; j < this->matrix[i].size(); ++j) {
                if(this->matrix[i][j] > 0){
                    string neighbor1, neighbor2;
                    neighbor1 += this->edges_names[j][2];
                    neighbor2 += this->edges_names[j][0];

                    string neighbor = neighbor1 == this->names[i] ? neighbor2: neighbor1;

                    neighbors.push_back(neighbor);
                }
            }

            pairs.emplace_back(this->names[i], neighbors);
        }

        auto list_adjacency = ListAdjacency<T>(pairs);
        return list_adjacency;
    }

private:
    pair<int, int> _find_indexes_of_edge(string edge){
        string edge1, edge2;
        edge1 += edge[0];
        edge2 += edge[2];

        int index1 = 0, index2 = 0;
        for (int i = 0; i < this->names.size(); ++i) {
            if(this->names[i] == edge1)
                index1 = i;
            if(this->names[i] == edge2)
                index2 = i;
        }

        return pair<int, int>(index1, index2);
    }
};



// =====================================================================================================================
// Adjacency matrix

template <class T>
class BaseMatrixAdjacency{
public:
    void print(){
        cout << "   ";
        for(auto name : this->names)
            cout << " " << name << " ";

        cout << endl;

        for (int i = 0; i < this->matrix.size(); ++i) {
            cout << this->names[i] << "  ";

            for(auto value : this->matrix[i]){
                if(value >= 0)
                    cout << " " << value << " ";
                else
                    cout << value << " ";
            }


            cout << endl;
        }

        cout << "\n\n\n";
    }
    void add_names(vector<T> names) {
        this->names = names;
    }

    ListEdges<T> get_list_edges(){
        auto list = vector<pair<T, T>>();
        for (int i = 0; i < this->matrix.size(); ++i) {
            for (int j = 0; j < this->matrix[i].size(); ++j) {
                if(matrix[i][j] == 1)
                    list.emplace_back(this->names[i], this->names[j]);
            }
        }

        auto list_edges = ListEdges<T>(list);
        return list_edges;
    }
    ListAdjacency<T> get_list_adjacency(){
        auto pairs = vector<pair<T, vector<T>>>();
        for (int i = 0; i < this->matrix.size(); ++i) {
            auto neighbors = vector<T>();
            for (int j = 0; j < this->matrix[i].size(); ++j) {
                if(this->matrix[i][j] > 0){
                    neighbors.push_back(this->names[j]);
                }
            }

            pairs.emplace_back(this->names[i], neighbors);
        }

        auto list_adjacency = ListAdjacency<T>(pairs);
        return list_adjacency;
    }
protected:
    vector<T> names;
    vector<vector<int>> matrix;
};

template <class T>
class MatrixAdjacencyDirected: public BaseMatrixAdjacency<T>{
public:
    MatrixAdjacencyDirected(vector<vector<int>> matrix){
        this->matrix = matrix;
    }
    MatrixIncidenceDirected<T> create_incidence_matrix(){
        auto edges = vector<pair<int, int>>();
        for (int i = 0; i < this->matrix.size(); ++i) {
            for (int j = 0; j < this->matrix[i].size(); ++j) {
                if(this->matrix[i][j] == 1){
                    edges.emplace_back(i, j);
                }
            }
        }


        auto matrix = vector<vector<int>>();
        for (int i = 0; i < this->matrix.size(); ++i) {
            auto temp = vector<int>();

            for (auto & edge : edges) {
                if (i == edge.first and i == edge.second)
                    temp.push_back(2);
                else if(i == edge.first)
                    temp.push_back(1);
                else if (i == edge.second)
                    temp.push_back(-1);
                else
                    temp.push_back(0);
            }

            matrix.push_back(temp);
        }

        auto edge_names = vector<string>();
        for(auto & edge : edges){
            edge_names.push_back(this->names[edge.first] + "-" + this->names[edge.second]);
        }

        auto new_graph = MatrixIncidenceDirected<T>(matrix);
        new_graph.add_names(this->names);
        new_graph.add_edges_names(edge_names);

        return new_graph;
    }
};
template <class T>
class MatrixAdjacencyUndirected: public BaseMatrixAdjacency<T>{
public:
    MatrixAdjacencyUndirected(vector<vector<int>> matrix){
        this->matrix = matrix;
    }
    MatrixIncidenceUndirected<T> create_incidence_matrix(){
        auto edges = vector<pair<int, int>>();
        for (int i = 0; i < this->matrix.size(); ++i) {
            for (int j = 0; j <= i; ++j) {
                if(this->matrix[i][j] == 1){
                    edges.emplace_back(i, j);
                }
            }
        }


        auto matrix = vector<vector<int>>();
        for (int i = 0; i < this->matrix.size(); ++i) {
            auto temp = vector<int>();

            for (auto & edge : edges) {
                if (i == edge.second or i == edge.first)
                    temp.push_back(1);
                else
                    temp.push_back(0);
            }

            matrix.push_back(temp);
        }

        auto edge_names = vector<string>();
        for(auto & edge : edges){
            edge_names.push_back(this->names[edge.second] + "-" + this->names[edge.first]);
        }

        auto new_graph = MatrixIncidenceUndirected<T>(matrix);
        new_graph.add_names(this->names);
        new_graph.add_edges_names(edge_names);

        return new_graph;
    }
};


#endif //FUCKING_ASD_LAB_MATRIX_H
