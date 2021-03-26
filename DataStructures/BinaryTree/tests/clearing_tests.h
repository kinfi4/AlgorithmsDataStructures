//
// Created by kini4 on 3/20/21.
//

#ifndef BITREE_CLEARING_TESTS_H
#define BITREE_CLEARING_TESTS_H
#include "../BinaryTree.h"
#include <assert.h>

void test_clearing(){
    auto tree = BinaryTree<int, int>();

    tree.add(1, 3);
    tree.add(2, 3);
    tree.add(3, 3);

    assert(tree.size() == 3);

    tree.clear();

    assert(tree.size() == 0);

    cout << "test_clearing passed well" << endl;
}


#endif //BITREE_CLEARING_TESTS_H
