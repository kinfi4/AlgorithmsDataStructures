//
// Created by kini4 on 2/28/21.
//
#include "../MyList.h"
#include <assert.h>

#ifndef LINKEDLIST_FILTER_TEST_H
#define LINKEDLIST_FILTER_TEST_H

void test_filtering(){
    auto list = MyList<int>();
    for (int i = 0; i < 100; ++i) {
        list.push_back(rand() % 200 - 100);
    }

    auto new_list = list.filter([](int a){
        return a > 0;
    });

    for (int i = 0; i < new_list.size(); ++i) {
        assert(new_list[i] > 0);
    }


    cout << "test_filtering passed well" << endl;
}


#endif //LINKEDLIST_FILTER_TEST_H
