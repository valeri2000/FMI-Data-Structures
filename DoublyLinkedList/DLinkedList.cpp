#include "DLinkedList.h"

#define DLL DLinkedList<T>
#define DLLI DLinkedListIterator

template <typename T>
DLL::DLLI::DLLI(Node* newPtr) {
    ptr = newPtr;
}

template <typename T>
DLL::DLLI::DLLI(const DLLI& other) {
    ptr = other.ptr;
}

template <typename T>
typename DLL::DLLI& DLL::DLLI::operator = (const DLLI& other) {
    if(this != &other) {
        ptr = other.ptr;
    }
    return *this;
}

template <typename T>
typename DLL::DLLI& DLL::DLLI::operator ++ () {
    ptr = ptr->nxt;
    return *this;
}

template <typename T>
typename DLL::DLLI DLL::DLLI::operator ++ (int a) {
    DLLI temp(ptr);
    ptr = ptr->nxt;
    return temp;
}

template <typename T>
typename DLL::DLLI& DLL::DLLI::operator -- () {
    ptr = ptr->prv;
    return *this;
}

template <typename T>
typename DLL::DLLI DLL::DLLI::operator -- (int a) {
    DLLI temp(ptr);
    ptr = ptr->prv;
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
    Node* temp = other.head;
    size_t curr = 0;
    while(curr != other.len) {
        push_back(temp->data);
        temp = temp->nxt;
        ++curr;
    }
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
    helpCopy(other);
}

template <typename T>
DLL& DLL::operator = (const DLL& other) {
    if(this != &other) {
        clear();
        copy(other);
    }
    return *this;
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
        head = new Node({value, nullptr, nullptr});
        len++;
        return;
    }
    Node* newHead = new Node({value, nullptr, head});
    if(len == 1) {
        newHead->prv = head;
        head->prv = newHead;
        head->nxt = newHead;
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
        head = new Node({value, nullptr, nullptr});
        len++;
        return;
    }
    if(len == 1) {
        Node* newNode = new Node({value, head, head});
        head->nxt = head->prv = newNode;
        len++;
        return;
    }
    Node* tail = head;
    size_t curr = 1;
    while(curr != len) {
        tail = tail->nxt;
        curr++;
    }
    Node* newTail = new Node({value, tail, head});
    tail->nxt = newTail;
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
    Node* newNode = new Node({value, temp->prv, temp});
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
