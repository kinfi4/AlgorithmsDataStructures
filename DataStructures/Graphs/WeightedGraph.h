//
// Created by kinfi4 on 4/3/21.
//

#ifndef GRAPHS_WEIGHTEDGRAPH_H
#define GRAPHS_WEIGHTEDGRAPH_H
#include "BaseWeightedGraph.h"
#include <vector>

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

        for (int i = 0; i < this->weights.size(); ++i) {
            dist.emplace_back(this->names[i], INTMAX_MAX);
            minListed.push_back(false);
        }


    }



};

#endif //GRAPHS_WEIGHTEDGRAPH_H
