//
// Created by kini4 on 3/15/21.
//

#ifndef STACK_QUEUE_H
#define STACK_QUEUE_H
template <class T>
class Queue{
public:
    Queue(){
        this->cur_head = nullptr;
        this->_size = 0;
    }

    bool is_empty();
    int size();
    void push(T data);
    T look();
    T pop();


private:
    template<class T1>
    class Node{
    public:
        Node(T1 data){
            this->data = data;
            this->next_node = nullptr;
        }

        T1 data;
        Node<T1>* next_node;
    };

    Node<T>* cur_head;
    int _size;

};

template<class T>
bool Queue<T>::is_empty() {
    return this->_size == 0;
}

template<class T>
int Queue<T>::size() {
    return this->_size;
}

template<class T>
void Queue<T>::push(T data) {
    auto* new_node = new Node<T>(data);
    new_node->next_node = this->cur_head;
    this->cur_head = new_node;

    this->_size++;
}

template<class T>
T Queue<T>::look() {
    return this->cur_head->data;
}

template<class T>
T Queue<T>::pop() {
    if(this->is_empty()){
        throw "stack is empty!";
    }

    auto temp = this->cur_head;
    this->cur_head = this->cur_head->next_node;

    auto data = temp->data;
    delete temp;
    this->_size--;

    return data;
}

#endif //STACK_QUEUE_H
