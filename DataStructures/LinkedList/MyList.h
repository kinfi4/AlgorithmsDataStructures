//
// Created by kinfi4 on 2/15/21.
//
#include <cmath>
#include <vector>
#include <functional>


#ifndef STUDENT_H
#define STUDENT_H

using namespace std;

template <class T>
class MyList{
public:
    MyList();
    ~MyList();

    void push_back(T data);
    void push_front(T data);
    T pop(int index = -1);
    T& operator[](int index);
    int size();
    void sort(bool reverse=false);
    void sort_by_key(function<bool(T, T)>);
    void clear();
    void extend(MyList<T>& list);

    bool contains(T value);
    int index(T value);
    void insert(int index, T value);
    void swap(int index1, int index2);

    MyList<T> filter(function<bool(T)>);

    int count(T value);
    int count_if(function<bool(T)>);

    int remove(T value);
    void remove_if(function<bool(T)>);

    MyList<T> copy();
    void set(int index, T value);
    T get(int index);

    static MyList<T> concat_lists(MyList<T> &list1, MyList<T> &list2);

private:
    template<class T1>
    class Node{
    public:
        T1 data;
        Node *pNext, *pPrev;

        Node(T1 data = T(), Node *pPrev=nullptr, Node *pNext=nullptr) {
            this->data = data;
            this->pNext = pNext;
            this->pPrev = pPrev;
        }

        bool operator > (const Node &another){
            return this->data > another.data;
        }

        Node<T>* copy(){
            return new Node<T>(this->data, this->pPrev, this->pNext);
        }
    };

    T delete_node(Node<T>* current);
    int validate_index(int index);

    int _size;
    Node<T> *head, *tail;
};

template<class T>
MyList<T>::MyList() {
    this->_size = 0;
    this->head = nullptr;
    this->tail = nullptr;
}

template<class T>
MyList<T>::~MyList() {
    this->clear();
}

template<class T>
void MyList<T>::push_back(T data) {
    if (this->head == nullptr){
        this->tail = this->head = new Node<T>(data);
    }
    else{
        this->tail->pNext = new Node<T>(data, this->tail);
        this->tail = this->tail->pNext;
    }

    this->_size++;
}

template<class T>
T MyList<T>::pop(int index) {
    index = this->validate_index(index);
    Node<T> *current;

    if(index > this->_size / 2){
        current = this->tail;
        for (int i = this->_size - 1; i != index; --i) {
            current = current->pPrev;
        }
    }else{
        current = this->head;
        for (int i = 0; i != index; ++i){
            current = current->pNext;
        }
    }

    return this->delete_node(current);
}

template<class T>
int MyList<T>::size() {
    return this->_size;
}

template<class T>
T &MyList<T>::operator[](int index) {
    index = this->validate_index(index);

    Node<T> * cur_node;
    if(index > this->_size / 2){
        cur_node = this->tail;
        int cur_index = this->_size - 1;

        while(cur_index != index){
            cur_node = cur_node->pPrev;
            cur_index--;
        }
    }else{
        cur_node = this->head;
        int cur_index = 0;

        while(cur_index != index){
            cur_node = cur_node->pNext;
            cur_index++;
        }
    }

    return cur_node->data;
}

template<class T>
void MyList<T>::sort(bool reverse) {

    for (int i = 0; i < this->size() - 1; ++i) {
        for (int j = 0; j < this->size() - i - 1; ++j) {
            if(((*this)[j] > (*this)[j+1] and not reverse) or ((*this)[j] < (*this)[j+1] and reverse)){
                T temp = (*this)[j];
                (*this)[j] = (*this)[j+1];
                (*this)[j+1] = temp;
            }
        }
    }

}

template<class T>
void MyList<T>::sort_by_key(function<bool(T, T)> compare) {
    for (int i = 0; i < this->size() - 1; ++i) {
        for (int j = 0; j < this->size() - i - 1; ++j) {
            if(not compare((*this)[j], (*this)[j + 1])){
                T temp = (*this)[j];
                (*this)[j] = (*this)[j+1];
                (*this)[j+1] = temp;
            }
        }
    }
}

template<class T>
void MyList<T>::clear() {
    while(this->size()){
        this->pop();
    }
}

template<class T>
void MyList<T>::extend(MyList<T> &list) {
    auto cur_node_of_another = list.head;
    while (cur_node_of_another != nullptr){
        this->push_back(cur_node_of_another->data);
        cur_node_of_another = cur_node_of_another->pNext;
    }
}

template<class T>
void MyList<T>::push_front(T data) {
    if(this->head == nullptr){
        this->tail = this->head = new Node<T>(data);
    }
    else{
        auto new_node = new Node<T>(data);
        this->head->pPrev = new_node;
        new_node->pNext = this->head;
        this->head = new_node;
    }

    this->_size++;
}

template<class T>
int MyList<T>::remove(T value) {
    if(this->head == nullptr){
        return -1;
    }

    auto cur_node = this->head;
    while(cur_node != nullptr){
        if(cur_node->data == value){
            this->delete_node(cur_node);
            return 1;
        }

        cur_node = cur_node->pNext;
    }

    return 0;
}

template<class T>
T MyList<T>::delete_node(MyList::Node<T> *current) {
    if(current != this->head){
        current->pPrev->pNext = current->pNext;
    }else{
        this->head = current->pNext;
    }

    if(current != this->tail){
        current->pNext->pPrev = current->pPrev;
    }else{
        this->tail = current->pPrev;
    }

    T data = current->data;
    this->_size--;
    delete current;

    return data;
}

template<class T>
bool MyList<T>::contains(T value) {
    if(this->head == nullptr){
        return false;
    }

    auto cur_node = this->head;
    while(cur_node != nullptr){
        if(cur_node->data == value)
            return true;

        cur_node = cur_node->pNext;
    }

    return false;
}

template<class T>
int MyList<T>::index(T value) {
    if(this->head == nullptr){
        return -1;
    }
    int cur_index = 0;
    auto cur_node = this->head;

    while(cur_node != nullptr){
        if(cur_node->data == value)
            return cur_index;

        cur_index++;
        cur_node = cur_node->pNext;
    }

    return -1;
}

template<class T>
MyList<T> MyList<T>::concat_lists(MyList<T> &list1, MyList<T> &list2) {
    auto new_list = new MyList<T>();
    new_list->extend(list1);
    new_list->extend(list2);

    return *new_list;
}

template<class T>
void MyList<T>::insert(int index, T value) {
    index = this->validate_index(index);

    if(index == 0)
        return this->push_front(value);
    if(index == this->size() - 1)
        return this->push_back(value);

    auto cur_node = this->head;
    for (int i = 0; i < index; ++i) {
        cur_node = cur_node->pNext;
    }

    auto new_node = new Node<T>(value, cur_node->pPrev, cur_node);
    cur_node->pPrev->pNext = new_node;
    cur_node->pPrev = new_node;

    this->_size++;
}

template<class T>
void MyList<T>::swap(int index1, int index2) {
    index1 = this->validate_index(index1);
    index2 = this->validate_index(index2);

    auto cur_node = this->head;
    Node<T>* node1, *node2;
    for (int i = 0; i <= max(index2, index1); ++i) {
        if(i == index1)
            node1 = cur_node;
        if(i == index2)
            node2 = cur_node;

        cur_node = cur_node->pNext;
    }

    std::swap(node1->data, node2->data);
}

template<class T>
int MyList<T>::count(T value) {
    int counter = 0;
    auto cur_node = this->head;
    while (cur_node != nullptr){
        if(cur_node->data == value)
            counter++;

        cur_node = cur_node->pNext;
    }

    return counter;
}

template<class T>
int MyList<T>::validate_index(int index) {
    index = index < 0 ? index + this->size() : index;

    if(index < 0 or index >= this->size())
        throw invalid_argument("index out of range");

    return index;
}

template<class T>
MyList<T> MyList<T>::filter(function<bool(const T)> predicate) {
    if(this->head == nullptr)
        return MyList<T>();

    auto new_list = new MyList<T>();
    auto cur_node = this->head;
    while(cur_node != nullptr){
        if(predicate(cur_node->data))
            new_list->push_back(cur_node->data);

        cur_node = cur_node->pNext;
    }

    return *new_list;
}

template<class T>
int MyList<T>::count_if(function<bool(T)> predicate) {
    if(this->head == nullptr)
        return 0;

    int counter = 0;
    auto cur_node = this->head;
    while(cur_node != nullptr){
        if(predicate(cur_node->data))
            counter++;

        cur_node = cur_node->pNext;
    }

    return counter;
}

template<class T>
MyList<T> MyList<T>::copy() {
    if(this->head == nullptr)
        return MyList<T>();

    auto cur_node = this->head;
    auto new_list = new MyList<T>();
    while(cur_node != nullptr){
        new_list->push_back(cur_node->data);
        cur_node = cur_node->pNext;
    }
    return *new_list;
}

template<class T>
T MyList<T>::get(int index) {
    return (*this)[index];
}

template<class T>
void MyList<T>::set(int index, T value) {
    index = this->validate_index(index);

    Node<T> *current;
    if(index > this->_size / 2){
        current = this->tail;
        for (int i = this->_size - 1; i != index; --i) {
            current = current->pPrev;
        }
    }else{
        current = this->head;
        for (int i = 0; i != index; ++i){
            current = current->pNext;
        }
    }

    current->data = value;

}

template<class T>
void MyList<T>::remove_if(function<bool(T)> predicate) {
    auto cur_node = this->head;
    while(cur_node != nullptr){
        auto next_node = cur_node->pNext;
        if(predicate(cur_node->data))
            this->delete_node(cur_node);

        cur_node = next_node;
    }
}

#endif

