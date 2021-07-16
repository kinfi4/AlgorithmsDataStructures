//
// Created by kini4 on 2/28/21.
//
#include "../MyList.h"
#include <assert.h>


#ifndef LINKEDLIST_COUNT_TESTS_H
#define LINKEDLIST_COUNT_TESTS_H

void test_count(){
    auto list = MyList<int>();
    list.push_back(4);
    list.push_back(43);
    list.push_back(43);
    list.push_back(-2);
    list.push_back(14);
    list.push_back(14);
    list.push_back(14);


    assert(list.count(0) == 0);
    assert(list.count(43) == 2);
    assert(list.count(14) == 3);

    cout << "test_count passed well" << endl;
}

void test_count_if(){
    auto list = MyList<int>();
    list.push_back(4);
    list.push_back(43);
    list.push_back(-43);
    list.push_back(-2);
    list.push_back(14);
    list.push_back(-14);
    list.push_back(14);


    assert(list.count_if([](int a){
        return a > 0;
    }) == 4);

    assert(list.count_if([](int a){
        return a < 0;
    }) == 3);

    cout << "test_count_if passed well" << endl;
}


#endif //LINKEDLIST_COUNT_TESTS_H
