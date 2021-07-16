//
// Created by kini4 on 2/28/21.
//
#include "../MyList.h"
#include <assert.h>


#ifndef LINKEDLIST_EXTENDING_TESTS_H
#define LINKEDLIST_EXTENDING_TESTS_H

void test_extending(){
    auto list1 = MyList<int>();
    auto list2 = MyList<int>();

    for (int i = 0; i < 10; ++i) {
        list1.push_back(i);
        list2.push_back(i);
    }

    list1.extend(list2);

    assert(list1.size() == 20);

    cout << "test_extending passed well" << endl;
}

void test_concatenating(){
    auto list1 = MyList<int>();
    auto list2 = MyList<int>();

    for (int i = 0; i < 10; ++i) {
        list1.push_back(i);
        list2.push_back(i);
    }

    auto new_list = MyList<int>::concat_lists(list1, list2);

    assert(new_list.size() == 20);

    cout << "test_concatenating passed well" << endl;
}



#endif //LINKEDLIST_EXTENDING_TESTS_H
