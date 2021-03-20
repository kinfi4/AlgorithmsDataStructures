//
// Created by kini4 on 3/20/21.
//

#ifndef BITREE_FACTORY_METHOD_TESTS_H
#define BITREE_FACTORY_METHOD_TESTS_H
#include <vector>
#include <assert.h>
#include <string>
#include "../BinaryTree.h"

using namespace std;

void test_tree_from_vector(){
    auto pairs = vector<pair<int, string>>();
    pairs.push_back(pair<int, string>(23, "First"));
    pairs.push_back(pair<int, string>(12, "Second"));
    pairs.push_back(pair<int, string>(-3, "Third"));
    pairs.push_back(pair<int, string>(4, "Forth"));
    pairs.push_back(pair<int, string>(2, "Fifth"));

    auto tree = BinaryTree<int, string>::tree_from_vector(pairs);

    assert(tree.size() == 5);
    assert(tree.find_element(23) == "First");
    assert(tree.find_element(12) == "Second");
    assert(tree.find_element(-3) == "Third");

    cout << "test_tree_from_vector passed well" << endl;
}

#endif //BITREE_FACTORY_METHOD_TESTS_H
