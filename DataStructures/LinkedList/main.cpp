#include <iostream>
#include "MyList.h"
#include <functional>
#include <algorithm>

using namespace std;

int main() {
    auto list = MyList<string>();
    auto list2 = MyList<string>();

    list.push_back("Hello1");
    list.push_back("Hell2");
    list2.push_back("Hell3");
    list2.push_back("Hello4");

    list.extend(list2);


    auto new_list = list.copy();
    new_list.push_back("Some data in new list");
    new_list.set(0, "new Value");

    for (int i = 0; i < new_list.size(); ++i) {
        cout << new_list[i] << " ";
    }
    cout << endl;

    for (int i = 0; i < list.size(); ++i) {
        cout << list[i] << " ";
    }

    return 0;
}
