#include <iostream>
#include "BST.h"

template <typename Key, typename Value>
BST<Key, Value>::Node::Node( const Key& _key, const Value& _value, Node* _left, Node* _right) : key(_key), value(_value), left(_left), right(_right) {}

template <typename Key, typename Value>
typename BST<Key, Value>::Node* BST<Key, Value>::build(
        const std::vector<std::pair<Key, Value> >& v,
        unsigned l, unsigned r) {
    if(l + 1 == r) {
        return new Node(v[l].first, v[l].second);
    }
    if(l >= r) {
        return nullptr;
    }

    unsigned m = (l + r) / 2;
    Node* el = new Node(v[m].first, v[m].second);
    Node* leftEl = build(v, l, m);
    Node* rightEl = build(v, m + 1, r);

    el->left = leftEl, el->right = rightEl;
    return el;
}

template <typename Key, typename Value>
typename BST<Key, Value>::Node* BST<Key, Value>::copy(const Node* other) {
    if(other == nullptr) {
        return nullptr;
    }
    Node* curr = new Node(other->key, other->value);
    Node* leftEl = copy(other->left);
    Node* rightEl = copy(other->right);
    curr->left = leftEl;
    curr->right = rightEl;
    return curr;
}

template <typename Key, typename Value>
void BST<Key, Value>::clear(Node* curr) {
    if(curr == nullptr) {
        return;
    }
    clear(curr->left);
    clear(curr->right);
    delete curr;
}

template <typename Key, typename Value>
void BST<Key, Value>::inorder(Node* curr) const {
    if(curr == nullptr) {
        return;
    }
    inorder(curr->left);
    std::cout << "[" << curr->key << ", " << curr->value << "] ";
    inorder(curr->right);
}

template <typename Key, typename Value>
void BST<Key, Value>::helpPrint(Node* curr, unsigned chars) const {
    if(curr == nullptr) {
        return;
    }

    helpPrint(curr->right, chars + 10); std::cout << std::endl;
    for(unsigned i = 0; i < chars; ++i) { std::cout << ' '; }

    std::cout << curr->key << std::endl;

    helpPrint(curr->left, chars + 10);
}

template <typename Key, typename Value>
std::pair<Value, bool> BST<Key, Value>::helpSearch(
        Node* curr, const Key& key) const {
    if(curr == nullptr) {
        return std::make_pair(Value(), false);
    }
    if(curr->key == key) {
        return std::make_pair(curr->value, true);
    }
    if(curr->key > key) {
        return helpSearch(curr->left, key);
    }
    return helpSearch(curr->right, key);
}

template <typename Key, typename Value>
typename BST<Key, Value>::Node* BST<Key, Value>::insert(Node* curr, const std::pair<Key, Value>& p) {
    if(curr == nullptr) {
        return new Node(p.first, p.second);
    }
    if(curr->key < p.first) {
        curr->right = insert(curr->right, p);
    } else if(curr->key > p.first) {
        curr->left = insert(curr->left, p);
    }
    return curr;
}

template <typename Key, typename Value>
typename BST<Key, Value>::Node* BST<Key, Value>::remove(Node* curr, const Key& key) {
    if(curr == nullptr) {
        return nullptr;
    }

    if(key < curr->key) {
        curr->left = remove(curr->left, key);
    } else if(key > curr->key) {
        curr->right = remove(curr->right, key);
    } else {
        if(curr->left == nullptr && curr->right == nullptr) {
            delete curr;
            curr = nullptr;
        } else if(curr->left == nullptr) {
            Node* temp = curr;
            curr = curr->right;
            delete temp;
        } else if(curr->right == nullptr) {
            Node* temp = curr;
            curr = curr->left;
            delete temp;
        } else {
            Node* minNode = curr->right;
            while(minNode->left != nullptr) {
                minNode = minNode->left;
            }
            std::cout << "We found " << curr->key << " (deletion of " << key << ") to have 2 children and min from right has key " << minNode->key << std::endl;
            curr->key = minNode->key, curr->value = minNode->value;
            curr->right = remove(curr->right, minNode->key);
        }
    }
    return curr;
}

template <typename Key, typename Value>
std::pair<unsigned, unsigned> BST<Key, Value>::dfs(Node* curr) const {
    std::pair<unsigned, unsigned> res(0, 0);
    if(curr == nullptr) {
        return res;
    }
    if(curr->left == nullptr && curr->right == nullptr) {
        res.second++;
    }
    std::pair<unsigned, unsigned> resLeft = dfs(curr->left),
                                  resRight = dfs(curr->right);
    res.second += (resLeft.second + resRight.second);
    res.first = 1 + std::max(resLeft.first, resRight.first);
    return res;
}

template <typename Key, typename Value>
BST<Key, Value>::BST() : root(nullptr) {}

template <typename Key, typename Value>
BST<Key, Value>::BST(const std::vector<std::pair<Key, Value> >& v) {
    root = build(v, 0, v.size());
}

template <typename Key, typename Value>
BST<Key, Value>::BST(const BST& other) {
    root = copy(other.root);
}

template <typename Key, typename Value>
BST<Key, Value>& BST<Key, Value>::operator = (const BST& other) {
    if(this != &other) {
        clear(root);
        root = copy(other.root);
    }
    return *this;
}

template <typename Key, typename Value>
BST<Key, Value>::~BST() {
    clear(root);
}

template <typename Key, typename Value>
void BST<Key, Value>::print() const {
    helpPrint(root, 0);
}

template <typename Key, typename Value>
void BST<Key, Value>::inorderPrint() const {
    inorder(root);
    if(root != nullptr) {
        std::cout << std::endl;
    }
}

template <typename Key, typename Value>
std::pair<Value, bool> BST<Key, Value>::search(const Key& key) const {
    return helpSearch(root, key);
}

template <typename Key, typename Value>
void BST<Key, Value>::insert(const std::pair<Key, Value>& p) {
    root = insert(root, p);
}

template <typename Key, typename Value>
void BST<Key, Value>::remove(const Key& key) {
    root = remove(root, key);
}

template <typename Key, typename Value>
unsigned BST<Key, Value>::height() const {
    return dfs(root).first;
}

template <typename Key, typename Value>
unsigned BST<Key, Value>::countLeaves() const {
    return dfs(root).second;
}

