//
// Created by kinfi4 on 3/28/21.
//

#ifndef FUCKING_ASD_LAB_LIST_EDGES_H
#define FUCKING_ASD_LAB_LIST_EDGES_H
#include <vector>

using namespace std;

template <class T>
class ListEdges{
public:
    ListEdges(vector<pair<T, T>> pairs){
        this->edges = pairs;
    }

    void print(){
        for(auto & pair : this->edges){
            cout << pair.first << " -- " << pair.second << endl;
        }

        cout << endl << endl << endl;
    }

private:
    vector<pair<T, T>> edges;
};

#endif //FUCKING_ASD_LAB_LIST_EDGES_H
