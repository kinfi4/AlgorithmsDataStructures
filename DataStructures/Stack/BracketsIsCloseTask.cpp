#include <iostream>
#include <vector>
#include "Queue.h"
#include "Stack.h"

using namespace std;

bool brackets_are_close(string line){
    auto stack = Stack<char>();

    try{
        for (auto c : line) {
            if(c == '[' or c == '{' or c == '(') {
                stack.push(c);
            }else {
                if(stack.is_empty())
                    return false;

                switch (c) {
                    case '}':
                        if(stack.pop() != '{')
                            return false;
                        break;
                    case ']':
                        if(stack.pop() != '[')
                            return false;
                        break;
                    case ')':
                        if(stack.pop() != '(')
                            return false;
                        break;
                    default:
                        return false;
                }
            }
        }

    }catch(exception) {
        return false;
    }

    return stack.size() == 0;
}


int main() {
    auto test = vector<string>();
    test.push_back("[]");
    test.push_back("[");
    test.push_back("[[[]]]");
    test.push_back("[{}([]){}]");
    test.push_back("[]{}");
    test.push_back("[{]}");
    test.push_back("[)");

    for(auto value : test){
        cout << value << " -- " << bool(brackets_are_close(value)) << endl;
    }

// HOW STACK WORKS
//    auto stack = Stack<int>();
//    for (int i = 0; i < 10; ++i) {
//        stack.push(i);
//    }
//
//    while(not stack.is_empty()){
//        cout << stack.pop() << endl;
//    }


    return 0;
}
