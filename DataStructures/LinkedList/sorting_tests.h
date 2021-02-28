//
// Created by kini4 on 2/28/21.
//
#include <assert.h>
#include "MyList.h"


void test_sorting_without_key(){
    auto list = MyList<int>();
    list.push_back(4);
    list.push_back(43);
    list.push_back(-2);
    list.push_back(14);

    list.sort();

    for (int i = 0; i < list.size() - 1; ++i) {
        assert(list[i] <= list[i + 1]);
    }

    cout << "test_sorting_without_key passed well" << endl;

}

void test_sorting_with_key(){
    auto list = MyList<string>();
    list.push_back("some");
    list.push_back("string");
    list.push_back("here");
    list.push_back("to");
    list.push_back("check");
    list.push_back("sorting");


    list.sort_by_key([](string s1, string s2){
        return s1.size() < s2.size();
    });

    for (int i = 0; i < list.size() - 1; ++i) {
        assert(list[i].size() <= list[i + 1].size());
    }

    cout << "test_sorting_with_key passed well" << endl;
}
