//
// Created by kini4 on 3/15/21.
//

using namespace std;

#ifndef BITREE_BINARYTREE_H
#define BITREE_BINARYTREE_H

#include "Node.h"
#include <vector>
#include <stdexcept>


template <class T, class D>
class BinaryTree {
public:
    BinaryTree();

    int size();
    bool is_empty();

    void add(T index, D value);
    void remove(T index);
    D find_element(T index);
    void clear();
    static BinaryTree<T, D> tree_from_vector(vector<pair<T, D>> nodes);
    static BinaryTree<T, D> tree_from_vector(vector<Node<T, D>> nodes);
    bool index_exists(T index);
    vector<T> keys();
    vector<D> values();

    D operator[](T index);

private:
    int _size;
    Node<T, D> *root;
    void _add_node(Node<T, D>* root, T index, D data);
    Node<T, D>* _find_the_node(Node<T, D>* root, T index);
    void _replace_node_with_terminal_node(Node<T, D>* root);
    void _replace_node_with_node(Node<T, D>* node1, Node<T, D>* node2);
    bool _index_exists(Node<T, D>* root, T index);

    void _delete_subtree(Node<T, D>* root);

    void _check_the_comparability();
    void _find_keys(Node<T, D>* root, vector<T>& keys);
    void _find_values(Node<T, D>* root, vector<D>& values);
};

template<class T, class D>
BinaryTree<T, D>::BinaryTree() {
    this->_check_the_comparability();

    this->root = nullptr;
    this->_size = 0;
}

template<class T, class D>
void BinaryTree<T, D>::_check_the_comparability() {
    auto first = T();
    auto second = T();
    bool possibility_of_comparability = false;

    try{
        auto compare_res = first > second;
        possibility_of_comparability = true;
    }catch(...) {
        possibility_of_comparability = false;
    }

    if(not possibility_of_comparability)
        throw invalid_argument("Impossible to compare this types");
}

template<class T, class D>
int BinaryTree<T, D>::size() {
    return this->_size;
}

template<class T, class D>
void BinaryTree<T, D>::add(T index, D data) {
    if(this->is_empty())
        this->root = new Node<T, D>(index, data, nullptr);
    else
        this->_add_node(this->root, index, data);

    this->_size++;
}

template<class T, class D>
void BinaryTree<T, D>::_add_node(Node<T, D> *root, T index, D data) {
    if(root->index < index and root->right_child == nullptr)
        root->right_child = new Node<T, D>(index, data, root);
    else if (root->index > index and root->left_child == nullptr)
        root->left_child = new Node<T, D>(index, data, root);
    else if (root->index == index)
        throw invalid_argument("Can add index, cause it already exist in the tree");
    else
        root->index > index ? _add_node(root->left_child, index, data) : _add_node(root->right_child, index, data);
}

template<class T, class D>
bool BinaryTree<T, D>::is_empty() {
    return this->_size == 0;
}

template<class T, class D>
void BinaryTree<T, D>::remove(T index) {
    auto node_to_remove = _find_the_node(this->root, index);
    if(node_to_remove == nullptr)
        return;

    _replace_node_with_terminal_node(node_to_remove);
    this->_size--;
}

template<class T, class D>
void BinaryTree<T, D>::_replace_node_with_terminal_node(Node<T, D> *root) {
    if(root->right_child != nullptr){
        auto term_node = root->right_child;
        while (term_node->left_child != nullptr)
            term_node = term_node->left_child;

        term_node->parent->left_child = nullptr;

        _replace_node_with_node(root, term_node);
    }else if(root->left_child != nullptr){
        auto term_node = root->left_child;
        while (term_node->right_child != nullptr)
            term_node = term_node->right_child;

        term_node->parent->right_child = nullptr;

        _replace_node_with_node(root, term_node);
    }else
        _replace_node_with_node(root, nullptr);
}

template<class T, class D>
void BinaryTree<T, D>::_replace_node_with_node(Node<T, D> *node1, Node<T, D>* node2) {
    if(node2 != nullptr){
        node2->right_child = node1->right_child;
        node2->left_child = node1->left_child;
    }

    if(node1->index > node1->parent->index)
        node1->parent->right_child = node2;
    else
        node1->parent->left_child = node2;

    delete node1;
}


template<class T, class D>
Node<T, D> *BinaryTree<T, D>::_find_the_node(Node<T, D> *root, T index) {
    if(root == nullptr)
        return nullptr;
    else if(root->index == index)
        return root;
    else
        return root->index > index ? _find_the_node(root->left_child, index) : _find_the_node(root->right_child, index);
}

template<class T, class D>
D BinaryTree<T, D>::find_element(T index) {
    if (this->is_empty())
        throw invalid_argument("The tree is empty");

    auto found_node = _find_the_node(this->root, index);
    if(found_node == nullptr)
        throw invalid_argument("There is such index in the tree");

    return found_node->data;
}

template<class T, class D>
void BinaryTree<T, D>::clear() {
    _delete_subtree(this->root);
}

template<class T, class D>
void BinaryTree<T, D>::_delete_subtree(Node<T, D> *root) {
    if(root->left_child != nullptr)
        _delete_subtree(root->left_child);
    if(root->right_child != nullptr)
        _delete_subtree(root->right_child);

    delete root;
    this->_size--;
}

template<class T, class D>
BinaryTree<T, D> BinaryTree<T, D>::tree_from_vector(vector<pair<T, D>> nodes) {
    auto tree = new BinaryTree<T, D>();
    for(auto node : nodes){
        tree->add(node.first, node.second);
    }

    return *tree;
}

template<class T, class D>
BinaryTree<T, D> BinaryTree<T, D>::tree_from_vector(vector<Node<T, D>> nodes) {
    auto tree = BinaryTree<T, D>();
    for(auto node : nodes){
        tree.add(node.index, node.data);
    }

    return tree;
}

template<class T, class D>
bool BinaryTree<T, D>::index_exists(T index) {
    return _index_exists(this->root, index);
}

template<class T, class D>
bool BinaryTree<T, D>::_index_exists(Node<T, D>* root, T index) {
    if(root == nullptr)
        return false;

    return root->index == index or _index_exists(root->left_child, index) or _index_exists(root->right_child, index);
}

template<class T, class D>
D BinaryTree<T, D>::operator[](T index) {
    return find_element(index);
}

template<class T, class D>
vector<T> BinaryTree<T, D>::keys() {
    auto _keys = vector<T>();
    _find_keys(this->root, _keys);

    return _keys;
}

template<class T, class D>
void BinaryTree<T, D>::_find_keys(Node<T, D> *root, vector<T>& _keys) {
    if(root == nullptr)
        return;

    _find_keys(root->left_child, _keys);
    _find_keys(root->right_child, _keys);

    _keys.push_back(root->index);
}

template<class T, class D>
vector<D> BinaryTree<T, D>::values() {
    auto _values = vector<D>();
    _find_values(this->root, _values);

    return _values;
}

template<class T, class D>
void BinaryTree<T, D>::_find_values(Node<T, D>* root, vector<D>& values) {
    if(root == nullptr)
        return;

    _find_values(root->left_child, values);
    _find_values(root->right_child, values);

    values.push_back(root->data);
}


#endif //BITREE_BINARYTREE_H
