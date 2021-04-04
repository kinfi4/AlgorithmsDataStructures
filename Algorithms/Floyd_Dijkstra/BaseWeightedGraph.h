//
// Created by kinfi4 on 4/3/21.
//

#ifndef GRAPHS_BASEWEIGHTEDGRAPH_H
#define GRAPHS_BASEWEIGHTEDGRAPH_H
#include <vector>

using namespace std;


template <class T>
class BaseWeightedGraph{
public:
    void print(){
        for (int i = 0; i < this->weights.size(); ++i) {
            cout << this->names[i] << ": ";
            cout << "\t";

            for (int j = 0; j < this->weights.size(); ++j) {
                if(this->weights[i][j] != 0){
                    cout << "("  << weights[i][j] << " - " << this->names[j] << ")  ";
                }
            }
            cout << endl;
        }
    }

protected:
    vector<vector<int>> weights;
    vector<T> names;
};


#endif //GRAPHS_BASEWEIGHTEDGRAPH_H
