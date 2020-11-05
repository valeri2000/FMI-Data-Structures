#include "DLinkedList.h"
#include <iostream>

#define DLL DLinkedList<T>
#define DLLI DLinkedListIterator

template <typename T>
DLL::Node::Node(const T& _data, Node* _prv, Node* _nxt, const bool _isEnd) {
    data = _data, prv = _prv, nxt = _nxt, isEnd = _isEnd;
}

template <typename T>
void DLL::DLLI::copyIt(const DLLI& other) {
    ptr = other.ptr;
    lastElemPtr = other.lastElemPtr;
    passedLast = other.passedLast;
}

template <typename T>
DLL::DLLI::DLLI(Node* _ptr, Node* _lastElemPtr, const bool _passedLast) {
    ptr = _ptr;
    lastElemPtr = _lastElemPtr;
    passedLast = _passedLast;
}

template <typename T>
DLL::DLLI::DLLI(const DLLI& other) {
    copyIt(other);
}

template <typename T>
typename DLL::DLLI& DLL::DLLI::operator = (const DLLI& other) {
    if(this != &other) {
        copyIt(other);
    }
    return *this;
}

template <typename T>
typename DLL::DLLI& DLL::DLLI::operator ++ () {
    if(passedLast == false) {
        if(ptr->isEnd == true) {
            lastElemPtr = ptr;
            ptr = nullptr;
            passedLast = true;
        }
        else {
            ptr = ptr->nxt;
        }
    }
    return *this;
}

template <typename T>
typename DLL::DLLI DLL::DLLI::operator ++ (int a) {
    DLLI temp(ptr, lastElemPtr, passedLast);
    if(passedLast == false) {
        if(ptr->isEnd == true) {
            lastElemPtr = ptr;
            ptr = nullptr;
            passedLast = true;
        }
        else {
            ptr = ptr->nxt;
        }
    }
    return temp;
}

template <typename T>
typename DLL::DLLI& DLL::DLLI::operator -- () {
    if(passedLast == true) {
        passedLast = false;
        ptr = lastElemPtr;
    }
    else {
        ptr = ptr->prv;
    }
    return *this;
}

template <typename T>
typename DLL::DLLI DLL::DLLI::operator -- (int a) {
    DLLI temp(ptr, lastElemPtr, passedLast);
    if(passedLast == true) {
        passedLast = false;
        ptr = lastElemPtr;
    }
    else {
        ptr = ptr->prv;
    }
    return temp;
}

template <typename T>
T& DLL::DLLI::operator * () const {
    return ptr->data;
}

template <typename T>
bool DLL::DLLI::operator == (const DLLI& other) const {
    return ptr == other.ptr;
}

template <typename T>
bool DLL::DLLI::operator != (const DLLI& other) const {
    return ptr != other.ptr;
}

template <typename T>
void DLL::helpClear() {
    while(!empty()) {
        pop_back();
    }
}

template <typename T>
void DLL::helpCopy(const DLL& other) {
    if(other.len == 0) {
        return;
    }
    if(other.len == 1) {
        push_back((other.head)->data);
        return;
    }
    Node* temp = other.head;
    while(temp->nxt != other.head) {
        push_back(temp->data);
        temp = temp->nxt;
    }
    push_back(temp->data);
}

template <typename T>
DLL::DLinkedList() {
    head = nullptr;
    len = 0;
}

template <typename T>
DLL::~DLinkedList() {
    clear();
}

template <typename T>
DLL::DLinkedList(const DLL& other) {
    head = nullptr;
    len = 0;
    helpCopy(other);
}

template <typename T>
DLL& DLL::operator = (const DLL& other) {
    if(this != &other) {
        clear();
        helpCopy(other);
    }
    return *this;
}

template <typename T>
typename DLL::DLLI DLL::begin() {
    return DLLI(head);
}

template <typename T>
typename DLL::DLLI DLL::end() {
    return DLLI(nullptr, head->prv, true);
}

template <typename T>
bool DLL::empty() const {
    return len == 0;
}

template <typename T>
size_t DLL::size() const {
    return len;
}

template <typename T>
T& DLL::front() {
    if(len == 0) {
        throw "No elements";
    }
    return head->data;
}

template <typename T>
T& DLL::back() {
    if(len == 0) {
        throw "No elements";
    }
    if(len == 1) {
        return head->data;
    }
    return (head->prv)->data;
}

template <typename T>
void DLL::assign(const size_t n, const T& value) {
    clear();
    size_t _n = n;
    while(_n--) {
        push_back(value);
    }
}

template <typename T>
void DLL::push_front(const T& value) {
    if(len == 0) {
        head = new Node(value, nullptr, nullptr, true);
        len++;
        return;
    }
    Node* newHead = new Node(value, nullptr, head);
    if(len == 1) {
        newHead->prv = head;
        head->prv = newHead;
        head->nxt = newHead;
        head->isEnd = true;
        head = newHead;
        len++;
        return;
    }
    Node* tail = head->prv;
    head->prv = newHead;
    newHead->prv = tail;
    tail->nxt = newHead;
    head = newHead;
    len++;
}

template <typename T>
void DLL::push_back(const T& value) {
    if(len == 0) {
        head = new Node(value, nullptr, nullptr, true);
        len++;
        return;
    }
    if(len == 1) {
        Node* newNode = new Node(value, head, head, true);
        head->nxt = head->prv = newNode;
        head->isEnd = false;
        len++;
        return;
    }
    Node* tail = head;
    while(tail->nxt != head) {
        tail = tail->nxt;
    }
    Node* newTail = new Node(value, tail, head, true);
    tail->nxt = newTail;
    tail->isEnd = false;
    head->prv = newTail;
    len++;
}

template <typename T>
void DLL::pop_front() {
    if(len == 0) {
        throw "No elements to pop";
    }
    if(len == 1) {
        delete head;
        head = nullptr;
        len--;
        return;
    }
    if(len == 2) {
        Node* newHead = head->nxt;
        newHead->prv = newHead->nxt = nullptr;
        delete head;
        head = newHead;
        len--;
        return;
    }
    Node* tail = head->prv;
    Node* newHead = head->nxt;
    tail->nxt = newHead;
    newHead->prv = tail;
    delete head;
    head = newHead;
    len--;
}

template <typename T>
void DLL::pop_back() {
    if(len == 0) {
        throw "No elements to pop";
    }
    if(len == 1) {
        delete head;
        head = nullptr;
        len--;
        return;
    }
    Node* tail = head->prv;
    Node* newTail = tail->prv;
    newTail->nxt = head;
    newTail->isEnd = true;
    head->prv = newTail;
    delete tail;
    len--;
}

template <typename T>
void DLL::insertBefore(const size_t index, const T& value) {
    if(index > len) {
        throw "Index out of range";
    }
    if(index == 0) {
        push_front(value);
        return;
    }
    if(index == len) {
        push_back(value);
        return;
    }
    size_t curr = 0;
    Node* temp = head;
    while(curr != index) {
        temp = temp->nxt;
        curr++;
    }
    Node* newNode = new Node(value, temp->prv, temp);
    (temp->prv)->nxt = newNode;
    temp->prv = newNode;
    len++;
}

template <typename T>
void DLL::erase(const size_t index) {
    if(index >= len) {
        throw "Invalid index";
    }
    if(index == 0) {
        pop_front();
        return;
    }
    if(index == len - 1) {
        pop_back();
        return;
    }
    size_t curr = 0;
    Node* temp = head;
    while(curr != index) {
        temp = temp->nxt;
        curr++;
    }
    Node* prevTemp = temp->prv;
    Node* nextTemp = temp->nxt;
    prevTemp->nxt = nextTemp;
    nextTemp->prv = prevTemp;
    delete temp;
    len--;
}

template <typename T>
void DLL::clear() {
    helpClear();
}

template <typename T>
void DLL::filter(bool (*pred)(const T& value)) {
    size_t index = 0;
    DLL newList;
    for(DLLI it = begin(); it != end(); ++it) {
        if(pred(*it)) {
            newList.push_back(*it);
        }
        ++index;
    }
    helpClear();
    helpCopy(newList);
}


template <typename T>
void DLL::map(T (*func)(const T& value)) {
    for(DLLI it = begin(); it != end(); ++it) {
        *it = func(*it);
    }
}

