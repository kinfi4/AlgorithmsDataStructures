//
// Created by kini4 on 3/20/21.
//

#ifndef BITREE_INDEX_EXISTING_TESTS_H
#define BITREE_INDEX_EXISTING_TESTS_H

#include "../BinaryTree.h"
#include <assert.h>

void test_index_existing(){
    auto tree = BinaryTree<int, string>();

    tree.add(1, "Hello");
    tree.add(2, "World");

    assert(tree.index_exists(1));
    assert(tree.index_exists(2));
    assert(not tree.index_exists(3));

    cout << "test_index_existing passed well" << endl;
}

#endif //BITREE_INDEX_EXISTING_TESTS_H
