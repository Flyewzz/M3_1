//
//  main.cpp
//  M3_1
//
//  Created by Alpha on 24.11.2018.
//  Copyright © 2018 Alpha. All rights reserved.
//

#include <iostream>

template <class T, class U>
struct Node {
    T key;
    U priority;
    Node *left;
    Node *right;
};

template <class T, class U>
class Treap {
    static Node<T,U> *root;
    void split(Node<T, U> *currentNode, U key, Node<T,U> *&, Node<T,U> *&);
    Node<T,U>* merge(Node<T,U> *left, Node<T,U> *right);
public:
    Treap(){root = nullptr;}
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
        if (left) {
            delete left;
        }
        if (right) {
            delete right;
        }
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
template<class T, class U>
void Treap<T, U>::add(T key, U priority, Node<T, U>* node) {
    Node<T, U> *found_node = [&](){//    Алгоритм должен работать и в случае отсутствия приоритета (пересмотреть)!
        if (node->priority >= priority) {
        add(key, priority, node->left);
        add(key, priority, node->right);
    }
return node;
}();
//    Теперь добавляем элемент
    Node<T, U> *left = new Node<T, U>;
    Node<T, U> *right = new Node<T, U>;
    split(found_node, key, left, right);
    Node<T, U> *creating_element = new Node<T, U>;
    creating_element->key = key;
    creating_element->priority = priority;
    creating_element->left = left;
    creating_element->right = right;
    delete found_node;
    found_node = creating_element;
}
template<class T, class U>
void Treap<T, U>::removetree() {
    
}

template<class T, class U>
void Treap<T, U>::print(Node<T, U> *node) {
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
