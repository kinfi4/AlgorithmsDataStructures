//
// Created by kini4 on 2/28/21.
//
#include "../MyList.h"
#include <assert.h>


#ifndef LINKEDLIST_INDEXING_TEST_H
#define LINKEDLIST_INDEXING_TEST_H

void test_indexing(){
    auto list = MyList<string>();
    list.push_back("First");
    list.push_back("Second");
    list.push_back("Finally");
    list.push_back("The");
    list.push_back("Last");

    assert(list.index("First") == 0);
    assert(list.index("Forth") == -1);
    assert(list.index("The") == 3);

    cout << "test_indexing passed well" << endl;
}

void test_swapping(){
    auto list = MyList<string>();
    list.push_back("First");
    list.push_back("Second");
    list.push_back("Finally");
    list.push_back("The");
    list.push_back("Last");

    list.swap(0, -1);

    assert(list.index("First") == list.size() - 1);
    assert(list.index("Last") == 0);

    cout << "test_swapping passed well" << endl;
}

void test_contains(){
    auto list = MyList<string>();
    list.push_back("First");
    list.push_back("Second");
    list.push_back("Finally");
    list.push_back("The");
    list.push_back("Last");

    assert(list.contains("First"));
    assert(not list.contains("Forth"));

    cout << "test_contains passed well" << endl;
}





#endif //LINKEDLIST_INDEXING_TEST_H
