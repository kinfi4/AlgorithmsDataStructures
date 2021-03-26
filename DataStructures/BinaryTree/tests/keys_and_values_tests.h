//
// Created by kinfi4 on 3/21/21.
//

#ifndef BITREE_KEYS_AND_VALUES_TESTS_H
#define BITREE_KEYS_AND_VALUES_TESTS_H
#include <algorithm>
#include <vector>
#include <assert.h>
#include "../BinaryTree.h"

void test_values(){
    auto tree = BinaryTree<int, int>();
    auto values = vector<int> {3, 5, -12, 0, 33};

    for(auto value : values)
        tree.add(value, value);

    auto tree_values = tree.values();
    for(auto value : tree_values){
        if(std::find(tree_values.begin(), tree_values.end(), value) != tree_values.end())
            assert(true);
        else
            assert(false);
    }


    cout << "test_values passed well" << endl;
}


void test_keys(){
    auto tree = BinaryTree<int, int>();
    auto keys = vector<int> {3, 5, -12, 0, 33};
    for(auto key : keys)
        tree.add(key, key);

    auto tree_keys = tree.keys();
    for(auto key : tree_keys){
        if(std::find(tree_keys.begin(), tree_keys.end(), key) != tree_keys.end())
            assert(true);
        else
            assert(false);
    }

    cout << "test_keys passed well" << endl;
}



#endif //BITREE_KEYS_AND_VALUES_TESTS_H
