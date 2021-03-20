//
// Created by kini4 on 3/20/21.
//

#ifndef BITREE_ADDING_NODES_TESTS_H
#define BITREE_ADDING_NODES_TESTS_H
#include "../BinaryTree.h"
#include <assert.h>

void test_adding_nodes(){
    auto tree = BinaryTree<int, int>();
    tree.add(1, 2);
    tree.add(2, 5);
    tree.add(3, 3);
    tree.add(4, 4);

    assert(tree.size() == 4);
    assert(tree.find_element(1) == 2);
    assert(tree.find_element(2) == 5);
    assert(tree.find_element(3) == 3);
    assert(tree.find_element(4) == 4);

    cout << "test_adding_nodes passed well" << endl;
}

void test_several_identical_indexes(){
    auto tree = BinaryTree<int, int>();
    tree.add(1, 3);

    try{
        tree.add(1, 1);
    }catch (...){
        cout << "test_several_identical_indexes passed well" << endl;
        return;
    }

    assert(false);
}


#endif //BITREE_ADDING_NODES_TESTS_H
