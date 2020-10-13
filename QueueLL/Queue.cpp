#include <iostream>
#include "Queue.h"

template <typename T>
void Queue<T>::delWhole() {
    if(this->length == 0) {
        this->tail = nullptr;
        return;
    }

    this->length = 0;
    Node<T>* temp;
    while(this->head != this->tail) {
        temp = this->head;
        this->head = (this->head)->nxt;
        delete temp;
    }
    delete this->head;
    this->head = this->tail = nullptr;
}

template <typename T>
void Queue<T>::copyWhole(const Queue<T>& other) {
    this->length = other.length;

    if(this->length == 1) {
        this->head = new Node<T>;
        (this->head)->data = (other.head)->data;
        (this->head)->nxt = nullptr;
        this->tail = this->head;
        return;
    }

    this->head = new Node<T>;
    (this->head)->data = (other.head)->data;

    Node<T>* currThis = this->head;
    Node<T>* newThis;
    Node<T>* currOther = other.head;
    while(currOther != other.tail) {
        currOther = currOther->nxt;

        newThis = new Node<T>;
        newThis->data = currOther->data;

        currThis->nxt = newThis;
        currThis = newThis;
    }

    currThis->nxt = nullptr;
    this->tail = currThis;
}

template <typename T>
Queue<T>::Queue() {
    this->head = this->tail = nullptr;
    this->length = 0;
}

template <typename T>
Queue<T>::Queue(const Queue<T>& other) {
    this->copyWhole(other);
}

template <typename T>
Queue<T>& Queue<T>::operator = (const Queue<T>& other) {
    if(this != &other) {
        this->delWhole();
        this->copyWhole(other);
    }
    return *this;
}

template <typename T>
Queue<T>::~Queue() {
    this->delWhole();
}

template <typename T>
bool Queue<T>::empty() const {
    return this->length == 0;
}

template <typename T>
size_t Queue<T>::size() const {
    return this->length;
}

template <typename T>
T Queue<T>::front() const {
    if(this->length == 0) {
        throw "No element at front";
        return T();
    }
    return (this->head)->data;
}

template <typename T>
void Queue<T>::push(const T& value) {
    if(this->length == 0) {
        this->head = new Node<T>;
        (this->head)->data = value;
        (this->head)->nxt = nullptr;
        this->tail = this->head;
        this->length = 1;
        return;
    }

    this->length++;

    Node<T>* newTail = new Node<T>;
    newTail->data = value;
    newTail->nxt = nullptr;
    (this->tail)->nxt = newTail;
    this->tail = newTail;
}

template <typename T>
void Queue<T>::pop() {
    if(this->length == 0) {
        throw "No element to pop";
        return;
    }

    this->length--;
    Node<T>* newHead = (this->head)->nxt;
    delete this->head;
    this->head = newHead;
}

