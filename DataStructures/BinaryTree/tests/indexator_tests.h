//
// Created by kini4 on 3/20/21.
//

#ifndef BITREE_INDEXATOR_TESTS_H
#define BITREE_INDEXATOR_TESTS_H

#include <assert.h>
#include "../BinaryTree.h"

void test_operator_indexator(){
    auto tree = BinaryTree<int, int>();
    tree.add(1, 1);
    tree.add(2, 2);
    tree.add(3, 3);
    tree.add(4, 4);

    assert(tree[1] == 1);
    assert(tree[2] == 2);
    assert(tree[3] == 3);
    assert(tree[4] == 4);

    cout << "test_operator_indexator passed well" << endl;
}


#endif //BITREE_INDEXATOR_TESTS_H
