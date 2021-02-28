//
// Created by kini4 on 2/28/21.
//

#include "MyList.h"
#include <assert.h>

#ifndef LINKEDLIST_REMOVE_TESTS_H
#define LINKEDLIST_REMOVE_TESTS_H

void test_remove_if(){
    auto list = MyList<int>();
    for (int i = 0; i < 100; ++i) {
        list.push_back(rand() % 200 - 100);
    }

    list.remove_if([](int a){
        return a < 0;
    });

    for (int i = 0; i < list.size(); ++i) {
        assert(list[i] >= 0);
    }

    cout << "test_remove_if passed well" << endl;
}

void test_remove(){
    auto list = MyList<int>();
    list.push_back(3);
    list.push_back(5);
    list.push_back(5);

    list.remove(3);
    list.remove(5);
    assert(not list.contains(3));
    assert(list.count(5) == 1);

    cout << "test_remove_if passed well" << endl;
}


#endif //LINKEDLIST_REMOVE_TESTS_H
