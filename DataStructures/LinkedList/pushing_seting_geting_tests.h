//
// Created by kini4 on 2/28/21.
//
#include "MyList.h"
#include <assert.h>

#ifndef LINKEDLIST_PUSHING_SETING_GETING_TESTS_H
#define LINKEDLIST_PUSHING_SETING_GETING_TESTS_H

void test_pushing_back_and_front(){
    auto list = MyList<int>();
    list.push_front(4);
    list.push_front(43);
    list.push_back(-2);
    list.push_back(14);

    assert(list.size() == 4);

    cout << "test_pushing_back_and_front passed well" << endl;
}

void test_index_operator(){
    auto list = MyList<int>();
    list.push_back(4);
    list.push_back(43);
    list.push_back(-2);
    list.push_back(14);

    assert(list[0] == 4);
    assert(list[-1] == 14);
    assert(list[1] == list[-3]);

    cout << "test_index_operator passed well" << endl;

}

void test_get_set_operator(){
    auto list = MyList<int>();
    list.push_back(4);
    list.push_back(43);
    list.push_back(-2);
    list.push_back(14);

    list.set(0, 5);
    list.set(-1, 100);

    assert(list.get(0) == 5);
    assert(list.get(-1) == 100);

    cout << "test_get_set_operator passed well" << endl;
}

void test_inserting(){
    auto list = MyList<int>();
    list.push_back(4);
    list.push_back(43);
    list.push_back(-2);
    list.push_back(14);

    list.insert(0, 5);
    list.insert(-1, 100);

    assert(list.get(0) == 5);
    assert(list.get(-1) == 100);
    assert(list.size() == 6);

    cout << "test_inserting passed well" << endl;
}


#endif //LINKEDLIST_PUSHING_SETING_GETING_TESTS_H
