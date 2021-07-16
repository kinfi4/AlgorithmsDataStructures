#include <iostream>

#include "tests/sorting_tests.h"
#include "tests/filter_test.h"
#include "tests/pushing_seting_geting_tests.h"
#include "tests/extending_tests.h"
#include "tests/count_tests.h"
#include "tests/indexing_test.h"
#include "tests/remove_tests.h"

#include "./MyList.h"

using namespace std;

int main() {
    test_pushing_back_and_front();
    test_get_set_operator();
    test_index_operator();
    test_inserting();

    test_extending();
    test_concatenating();

    test_sorting_with_key();
    test_sorting_without_key();

    test_filtering();

    test_count();
    test_count_if();

    test_swapping();
    test_contains();
    test_indexing();

    test_remove();
    test_remove_if();

    return 0;
}
