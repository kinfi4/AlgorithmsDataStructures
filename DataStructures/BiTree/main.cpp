#include <iostream>
#include "BinaryTree.h"
#include <map>

#include "tests/adding_nodes_tests.h"
#include "tests/factory_method_tests.h"
#include "tests/indexator_tests.h"
#include "tests/clearing_tests.h"
#include "tests/removing_tests.h"
#include "tests/index_existing_tests.h"

using namespace std;


int main() {
    test_adding_nodes();
    test_tree_from_vector();
    test_several_identical_indexes();
    test_operator_indexator();
    test_clearing();
    test_tree_from_vector();
    test_index_existing();
    test_removing();


    auto tree = map<int, int>();


    return 0;
}
