//
// Created by kini4 on 3/20/21.
//

#ifndef BITREE_REMOVING_TESTS_H
#define BITREE_REMOVING_TESTS_H

#include "../BinaryTree.h"
#include <assert.h>

void test_removing(){
    auto tree = BinaryTree<int, string>();
    tree.add(1, "First");
    tree.add(2, "Second");
    tree.add(3, "Third");

    tree.remove(2);

    assert(tree.size() == 2);

    try{
        tree[2];
    }catch (...){
        cout << "test_removing passed well" << endl;
        return;
    }

    assert(false);
}


#endif //BITREE_REMOVING_TESTS_H
