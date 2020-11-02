#include "LinkedList.h"
#define LLC LinkedList<T>
#define LLI LinkedListIterator

template <typename T>
LLC::Node::Node(const T& newData, Node* newNxt) {
    data = newData;
    nxt = newNxt;
}

template <typename T>
LLC::LLI::LLI(Node* newPtr) {
    ptr = newPtr;
}

template <typename T>
LLC::LLI::LLI(const LLI& other) {
    ptr = other.ptr;
}

template <typename T>
typename LLC::LLI& LLC::LLI::operator = (const LLI& other) {
    if(this != &other) {
        ptr = other.ptr;
    }
    return *this;
}

template <typename T>
typename LLC::LLI& LLC::LLI::operator ++ () {
    ptr = ptr->nxt;
    return *this;
}

template <typename T>
typename LLC::LLI LLC::LLI::operator ++ (int a) {
    LLI temp(ptr);
    ptr = ptr->nxt;
    return temp;
}

template <typename T>
T& LLC::LLI::operator * () const {
    return ptr->data;
}

template <typename T>
bool LLC::LLI::operator == (const LLI& other) const {
    return ptr == other.ptr;
}

template <typename T>
bool LLC::LLI::operator != (const LLI& other) const {
    return ptr != other.ptr;
}

template <typename T>
void LLC::clear() {
    while(!empty()) {
        pop_back();
    }
    head = nullptr;
}

template <typename T>
void LLC::copy(const LLC& other) {
    if(other.head == nullptr) {
        head = nullptr;
        return;
    }
    Node* temp = new Node((other.head)->data);
    const Node* curr = other.head;
    head = temp;
    while(curr->nxt != nullptr) {
        curr = curr->nxt;
        Node* newTemp = new Node(curr->data);
        temp->nxt = newTemp;
        temp = newTemp;
    }
}

template <typename T>
LLC::LinkedList() {
    head = nullptr;
}

template <typename T>
LLC::~LinkedList() {
    clear();
}

template <typename T>
LLC::LinkedList(const LLC& other) {
    copy(other);
}

template <typename T>
LLC& LLC::operator = (const LLC& other) {
    if(this != &other) {
        clear();
        copy(other);
    }
    return *this;
}

template <typename T>
T& LLC::front() {
    return *begin();
}

template <typename T>
void LLC::push_front(const T& data) {
    Node* temp = new Node(data, head);
    head = temp;
}

template <typename T>
void LLC::pop_front() {
    if(head == nullptr) { 
        throw "No elements to pop";
    }
    Node* newHead = head->nxt;
    delete head;
    head = newHead;
}

template <typename T>
void LLC::push_back(const T& data) {
    Node* temp = head;
    if(temp == nullptr) {
        push_front(data);
        return;
    }
    while(temp->nxt != nullptr) {
        temp = temp->nxt;
    }
    Node* newNode = new Node(data);
    temp->nxt = newNode;
}

template <typename T>
void LLC::pop_back() {
    if(head == nullptr) {
        throw "No elements to pop";
    }
    Node* temp = head;
    Node* prev = nullptr;
    while(temp->nxt != nullptr) {
        prev = temp;
        temp = temp->nxt;
    }
    if(prev == nullptr) {
        delete head;
        head = nullptr;
        return;
    }
    delete temp;
    prev->nxt = nullptr;
}

template <typename T>
bool LLC::empty() const {
    return (head == nullptr);
}

template <typename T>
typename LLC::LLI LLC::begin() {
    return LLI(head);
}

template <typename T>
typename LLC::LLI LLC::end() {
    return LLI();
}
