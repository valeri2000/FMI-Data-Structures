#include "AVL.h"
#include <iostream>
#define TAVL AVL<Key, Value>

template<typename Key, typename Value>
TAVL::Node::Node(
    const Key& _key, const Value& _value, 
    Node* _left, Node* _right, const int& _height
    ) : key(_key), value(_value), left(_left), right(_right), height(_height) {}

template<typename Key, typename Value>
int TAVL::getBalance(Node* curr) const {
    return getHeight(curr->left) - getHeight(curr->right);
}

template<typename Key, typename Value>
int TAVL::getHeight(Node*& curr) const {
    return !curr ? 0 : curr->height;
}

template<typename Key, typename Value>
typename TAVL::Node* TAVL::rotateLeft(Node* curr) {
    Node* newCurr = curr->right;
    Node* currRightNew = newCurr->left;
    newCurr->left = curr;
    curr->right = currRightNew;

    curr->height = 1 + std::max(getHeight(curr->left), getHeight(curr->right));
    newCurr->height = 1 + std::max(getHeight(newCurr->left), getHeight(newCurr->right));
    ++curr->height; ++newCurr->height;
    return newCurr;
}

template<typename Key, typename Value>
typename TAVL::Node* TAVL::rotateRight(Node* curr) {
    Node* newCurr = curr->left;
    Node* currLeftNew = newCurr->right;
    newCurr->right = curr;
    curr->left = currLeftNew;

    curr->height = 1 + std::max(getHeight(curr->left), getHeight(curr->right));
    newCurr->height = 1 + std::max(getHeight(newCurr->left), getHeight(newCurr->right));
    ++curr->height; ++newCurr->height;
    return newCurr;
}

template<typename Key, typename Value>
typename TAVL::Node* TAVL::copy(const Node* other) {
    if(other == nullptr) {
        return nullptr;
    }
    Node* res = new Node(other->key, other->value);
    res->left = copy(other->left);
    res->right = copy(other->right);
    res->height = 1 + std::max(getHeight(res->left), getHeight(res->right));
    return res;
}

template<typename Key, typename Value>
void TAVL::del(Node*& curr) {
    if(curr == nullptr) {
        return;
    }
    del(curr->left);
    del(curr->right);
    delete curr;
    curr = nullptr;
}

template<typename Key, typename Value>
typename TAVL::Node* TAVL::insert(Node* curr, const Key& key, const Value& value) {
    if(curr == nullptr) {
        return new Node(key, value);
    }
    if(curr->key < key) {
        curr->right = insert(curr->right, key, value);
    } else if(curr->key > key) {
        curr->left = insert(curr->left, key, value);
    } else { // duplicate
        return curr;
    }
    curr->height = 1 + std::max(getHeight(curr->left), getHeight(curr->right));
    int currBalance = getBalance(curr);
    if(currBalance > 1) {// 2, left is bigger
        if(key > (curr->left)->key) { // it is left, right
            curr->left = rotateLeft(curr->left);
        }
        return rotateRight(curr);
    } else if(currBalance < -1) { // -2, right is bigger
        if(key < (curr->right)->key) {
            curr->right = rotateRight(curr->right);
        }
        return rotateLeft(curr);
    }
    return curr; // ok
}

template<typename Key, typename Value>
std::pair<Value, bool> TAVL::find(Node* curr, const Key& key) const {
    if(curr == nullptr) {
        return std::make_pair(Value(), false);
    }
    if(curr->key > key) {
        return find(curr->left, key);
    }
    if(curr->key < key) {
        return find(curr->right, key);
    }
    return std::make_pair(curr->value, true);
}

template<typename Key, typename Value>
std::pair<Value, bool> TAVL::find(const Key& key) const {
    return find(root, key);
}

template<typename Key, typename Value>
void TAVL::printKeys(Node* curr, unsigned offs) const {
    if(curr == nullptr) {
        return;
    }
    offs += 10; // lvls

    printKeys(curr->right, offs); // right sub is first
    std::cout << std::endl;

    for(unsigned i = 10; i < offs; ++i) {
        std::cout << ' ';
    }
    std::cout << curr->key << std::endl;

    printKeys(curr->left, offs);
}

template<typename Key, typename Value>
TAVL::AVL() : root(nullptr) {}

template<typename Key, typename Value>
TAVL::AVL(const AVL& other) {
    root = copy(other.root);
}

template<typename Key, typename Value>
TAVL::~AVL() {
    del(root);
}

template<typename Key, typename Value>
TAVL& TAVL::operator = (const AVL& other) {
    if(this != &other) {
        del(root);
        root = copy(other.root);
    }
    return *this;
}

template<typename Key, typename Value>
void TAVL::insert(const Key& key, const Value& value) {
    root = insert(root, key, value);
}

template<typename Key, typename Value>
void TAVL::printKeys() const {
    printKeys(root, 0);
    std::cout << std::endl;
}

