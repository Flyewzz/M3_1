//
//  main.cpp
//  M3_1
//
//  Created by Alpha on 24.11.2018.
//  Copyright © 2018 Alpha. All rights reserved.
//

#include <iostream>
#include <tuple>
template <class T, class U>
struct Node {
    T key;
    U priority;
    Node<T, U> *left;
    Node<T, U> *right;
};

template <class T, class U>
class Treap {
    static Node<T,U> *root;
    uint16_t size;
    void split(Node<T, U> *currentNode, U key, Node<T,U> *&, Node<T,U> *&);
    Node<T,U>* merge(Node<T,U> *left, Node<T,U> *right);
    Node<T, U>* found_in_treap(Node<T, U> *node, U priority);
public:
    Treap(){root = nullptr; size = 0;}
    uint16_t getSize() {return size;}
    ~Treap(){removetree();}
    Treap(const Treap &) = delete;
    Treap& operator = (const Treap &) = delete;
    void removetree();
    void add(T key, U priority, Node<T, U>*node = root);
    void print(Node<T, U> *node = root);
};

template <class T, class U>
void Treap<T, U>::split(Node<T, U> *currentNode, U key, Node<T,U> *&left, Node<T,U> *&right) {
    if (currentNode == nullptr) {
//        if (left) {
//            delete left;
//        }
//        if (right) {
//            delete right;
//        }
        left = nullptr;
        right = nullptr;
    }
    else if (currentNode->key < key) {
        split(currentNode->right, key, currentNode->right, right);
        left = currentNode;
    }
    else {
        split(currentNode->left, key, left, currentNode->left);
        right = currentNode;
    }
}

template <class T, class U>
Node<T,U>* merge(Node<T,U> *left, Node<T,U> *right) {
    if (left == nullptr || right == nullptr) {
        return left == nullptr? right : left;
    }
    if (left->priority > right->priority) {
        left->right = merge(left->right, right);
        return left;
    }
    else {
        right->left = merge(left, right->left);
        return right;
    }
}

template <class T, class U>
Node<T, U>* Treap<T, U>::found_in_treap(Node<T, U> *node, U priority) {
    if (node == nullptr) return node; // Возвращаем "не найдено"
    if (node->priority >= priority) {
        Node<T, U> *left = found_in_treap(node->left, priority);
        Node<T, U> *right = found_in_treap(node->right, priority);
        return left == nullptr ? right : left;
    }
    return node;
}
template<class T, class U>
void Treap<T, U>::add(T key, U priority, Node<T, U>* node) {
//    std::function<std::tuple<Node<T, U>*, Node<T, U>*>*(Node<T, U>*)> found_in_treap = [&found_in_treap, priority, node](Node<T, U>* node){
//        if (node->priority >= priority) {
////            found_in_treap(node->left);
////            found_in_treap(node->right);
//            return std::make_tuple(found_in_treap(node->left), found_in_treap(node->right));
//        }
//return node;
//};
    Node<T, U>* found_node;
    found_node = found_in_treap(node, priority);
//    Теперь добавляем элемент
    Node<T, U> *left;
    Node<T, U> *right;
    split(found_node, key, left, right);
    Node<T, U> *creating_element = new Node<T, U>;
    creating_element->key = key;
    creating_element->priority = priority;
    creating_element->left = left;
    creating_element->right = right;
//    delete found_node;
    if (size == 0) {
        root = creating_element;
    }
    ++size;
}
template<class T, class U>
void Treap<T, U>::removetree() {
    
}

template<class T, class U>
void Treap<T, U>::print(Node<T, U> *node) {
    if (node == nullptr) return;
    print(node->left);
    print(node->right);
    std::cout << node->key << " ";
}
template<class T, class U>
Node<T, U>* Treap<T, U>::root = nullptr;

int main(int argc, const char * argv[]) {
    int N;
    std::cin >> N;
    Treap<int, int> treap;
    for (int i = 0; i < N; ++i) {
        int key;
        int priority;
        std::cin >> key >> priority;
        treap.add(key, priority);
    }
    treap.print();
    std::cout << std::endl;
    return 0;
}
