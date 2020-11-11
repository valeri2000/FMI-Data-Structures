#include <cassert>
#include <cmath>
#include "SkipList.h"

template <typename T>
SkipList<T>::Node::Node(const T& _data, Node* _nxt, Node* _skip) :
    data(_data), nxt(_nxt), skip(_skip) {}

template <typename T>
void SkipList<T>::clearSkips() {
    if(!hasSkips) { return; }

    hasSkips = false;
    Node* curr = head;
    while(curr != nullptr) {
        curr->skip = nullptr;
        curr = curr->nxt;
    }
}

template <typename T>
void SkipList<T>::clear() {
    if(hasSkips) {
        clearSkips();
        hasSkips = false;
    }

    while(head != nullptr) {
        Node* newHead = head->nxt;
        delete head;
        head = newHead;
    }
    len = 0;
}

template <typename T>
void SkipList<T>::copy(const SkipList<T>& other) {
    Node* curr = other.head;
    Node* prv = nullptr;
    Node* currHead;
    while(curr != nullptr) {
        currHead = new Node(curr->data);
        len++;
        if(prv == nullptr) {
            head = currHead;
        } else {
            prv->nxt = currHead;
        }
        prv = currHead;
        curr = curr->nxt;
    }
    if(other.hasSkips) {
        buildSkips();
    }
}

template <typename T>
SkipList<T>::SkipList() :
    head(nullptr), len(0), hasSkips(false) {}

template <typename T>
SkipList<T>::SkipList(const SkipList<T>& other) {
    copy(other);
}

template <typename T>
SkipList<T>::~SkipList() {
    clear();
}

template <typename T>
SkipList<T>& SkipList<T>::operator = (const SkipList& other) {
    if(this != &other) {
        clear();
        copy(other);
    }
    return *this;
}

template <typename T>
void SkipList<T>::insert(const T& value) {
    Node* curr = head;
    Node* prv = nullptr;
    bool done = false;
    while(curr != nullptr) {
        if(curr->data <= value) {
            prv = curr;
            curr = curr->nxt;
        } else {
            if(prv == nullptr) {
                Node* newHead = new Node(value, head);
                head = newHead;
            } else {
                Node* newNode = new Node(value, curr);
                prv->nxt = newNode;
            }
            done = true;
            len++;
            break;
        }
    }
    if(!done) {
        if(len == 1) {
            Node* newNode = new Node(value);
            head->nxt = newNode;
        } else if(len == 0) {
            head = new Node(value);
        } else {
            Node* newNode = new Node(value);
            prv->nxt = newNode;
        }
        len++;
    }
}

template <typename T>
void SkipList<T>::buildSkips() {
    if(hasSkips) {
        clearSkips();
    }
    size_t bucketLen = sqrt(len);
    Node* tmp = head;
    Node* prv = nullptr;
    for(size_t curr = 1; curr <= len; ++curr) {
        if(curr % bucketLen == 0) {
            if(prv == nullptr) {
                prv = tmp;
            } else {
                prv->skip = tmp;
                prv = tmp;
            }
        }
        tmp = tmp->nxt;
    }
    hasSkips = true;
}

template <typename T>
std::pair<size_t, unsigned> SkipList<T>::findWithSkips(const T& value, bool& found) const {
    found = false;
    size_t index = 0, steps = 0, bucketLen = sqrt(len);
    Node* curr = head;
    while(curr != nullptr) {
        if(curr->data >= value) {
            found = (curr->data == value);
            break;
        } else {
            if(curr->skip == nullptr || (curr->skip)->data > value) {
                index++;
                steps++;
                curr = curr->nxt;
            } else {
                index += bucketLen;
                steps++;
                curr = curr->skip;
            }
        }
    }
    return std::make_pair(index, steps);
}

template <typename T>
size_t SkipList<T>::findWithNxt(const T& value, bool& found) const {
    found = false;
    size_t index = 0;
    Node* curr = head;
    while(curr != nullptr) {
        if(curr->data >= value) {
            found = (curr->data == value);
            break;
        } else {
            index++;
            curr = curr->nxt;
        }
    }
    return index;
}

template <typename T>
void SkipList<T>::getElements(std::vector<T>& res) const {
    res.clear();
    Node* curr = head;
    while(curr != nullptr) {
        res.push_back(curr->data);
        curr = curr->nxt;
    }
}

template <typename T>
size_t SkipList<T>::size() const {
    return len;
}

