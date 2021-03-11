//
// Created by kini4 on 3/11/21.
//

#ifndef STACK_STACK_H
#define STACK_STACK_H

template <class T>
class Stack{
public:
    Stack(){
        this->cur_tail = nullptr;
        this->_size = 0;
    }

    bool is_empty();
    int size();
    void push(T data);
    T pop();


private:
    template<class T1>
    class Node{
    public:
        Node(T1 data){
            this->data = data;
            this->prev_node = nullptr;
        }

        T1 data;
        Node<T1>* prev_node;
    };

    Node<T>* cur_tail;
    int _size;

};

template<class T>
bool Stack<T>::is_empty() {
    return this->_size <= 0;
}

template<class T>
int Stack<T>::size() {
    return this->_size;
}

template<class T>
void Stack<T>::push(T data) {
    auto* new_node = new Node<T>(data);
    new_node->prev_node = this->cur_tail;
    this->cur_tail = new_node;

    this->_size++;
}

template<class T>
T Stack<T>::pop() {
    if(this->is_empty()){
        throw "stack is empty!";
    }
    auto temp = this->cur_tail;
    this->cur_tail = this->cur_tail->prev_node;

    auto data = temp->data;
    delete temp;
    this->_size--;

    return data;
}

#endif //STACK_STACK_H
