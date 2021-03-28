//
// Created by kinfi4 on 3/28/21.
//

#ifndef FUCKING_ASD_LAB_LIST_ADJACENCY_H
#define FUCKING_ASD_LAB_LIST_ADJACENCY_H

#include <vector>

using namespace std;

template <class T>
class ListAdjacency{
public:
    ListAdjacency(vector<pair<T, vector<T>>> lists){
        this->lists = lists;
    }

    void print(){
        for(auto& pair : this->lists){
            cout << pair.first << " -- ";
            for(auto& node : pair.second)
                cout << node << " ";

            cout << endl;
        }
        cout << endl << endl << endl;
    }

private:
    vector<pair<T, vector<T>>> lists;
};


#endif //FUCKING_ASD_LAB_LIST_ADJACENCY_H
