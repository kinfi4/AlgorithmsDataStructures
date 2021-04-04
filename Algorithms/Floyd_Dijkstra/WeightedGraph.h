//
// Created by kinfi4 on 4/3/21.
//

#ifndef GRAPHS_WEIGHTEDGRAPH_H
#define GRAPHS_WEIGHTEDGRAPH_H
#include "BaseWeightedGraph.h"
#include <vector>
#include <climits>
#include <cmath>

using namespace std;

template <class T>
class WeightedGraph: public BaseWeightedGraph<T>{
public:
    WeightedGraph(vector<vector<int>> weights, vector<T> names){
        if(weights.size() != names.size())
            throw invalid_argument("Weights matrix size must be equal to names vector size");

        this->weights = weights;
        this->names = names;
    }

    vector<pair<T, int>> dijkstra(T start_node){
        vector<pair<T, int>> dist;
        vector<bool> minListed;
        int start_index;

        for (int i = 0; i < this->weights.size(); ++i) {
            if(start_node == this->names[i])
                start_index = i;

            dist.emplace_back(this->names[i], INT_MAX);
            minListed.push_back(false);
        }

        dist[start_index] = pair<T, int>(start_node, 0);

        for (int count = 0; count < this->names.size() - 1; ++count) {
            int cur = this->_min_distance(dist, minListed);
            minListed[cur] = true;

            for (int i = 0; i < this->names.size(); ++i) {
                if(not minListed[i] and this->weights[cur][i] and dist[cur].second != INT_MAX
                   and dist[cur].second + this->weights[cur][i] < dist[i].second)
                    dist[i].second = dist[cur].second + this->weights[cur][i];
            }
        }

        return dist;
    }
    vector<vector<int>> floyd(){
        vector<vector<int>> weights_matrix;
        for (int i = 0; i < this->weights.size(); ++i) {
            vector<int> row;
            for (int j = 0; j < this->weights[i].size(); ++j) {
                if(i == j)
                    row.push_back(0);
                else if(this->weights[i][j] == 0)
                    row.push_back(INT_MAX);
                else
                    row.push_back(this->weights[i][j]);
            }
            weights_matrix.push_back(row);
        }
        
        int size = weights_matrix.size();
        for (int k = 0; k < size; ++k) {
            for (int i = 0; i < size; ++i) {
                for (int j = 0; j < size; ++j) {
                    auto val = weights_matrix[i][k] + weights_matrix[k][j];
                    if(val > 0)
                        weights_matrix[i][j] = min(weights_matrix[i][j], val);
                }
            }
        }

        return weights_matrix;
    }

private:
    int _min_distance(vector<pair<T, int>> dist, vector<bool> minListed){
        int min = INT_MAX, min_index;
        for (int i = 0; i < dist.size(); ++i) {
            if(not minListed[i] and dist[i].second < min){
                min = dist[i].second;
                min_index = i;
            }
        }

        return min_index;
    }
};

#endif //GRAPHS_WEIGHTEDGRAPH_H
