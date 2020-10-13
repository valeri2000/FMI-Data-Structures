#include "Stack.h"

template<typename T>
void Stack<T>::delData() {
    delete[] this->data;
    this->data = nullptr;
}

template<typename T>
T* Stack<T>::copyData() const {
    T* cData = new T[this->capacity];
    for(size_t i = 0; i < this->len; ++i) {
        cData[i] = this->data[i];
    }
    return cData;
}

template<typename T>
void Stack<T>::modifyCap(const float factor) {
    size_t newCap = static_cast<size_t>(this->capacity * factor);
    T* newData = new T[newCap];

    for(size_t i = 0; i < this->len; ++i) {
        newData[i] = this->data[i];
    }

    this->delData();
    this->data = newData;
    this->capacity = newCap;
}

template<typename T>
Stack<T>::Stack() {
    this->capacity = 2;
    this->len = 0;
    this->data = new T[this->capacity];
}

template<typename T>
Stack<T>::Stack(const Stack<T>& other) {
    this->data = other.copyData();
    this->capacity = other.capacity;
    this->len = other.len;
}

template<typename T>
Stack<T>& Stack<T>::operator = (const Stack<T>& other) {
    if(&other != this) {
        this->delData();
        this->data = other.copyData();
        this->capacity = other.capacity;
        this->len = other.len;
    }
    return *this;
}

template<typename T>
Stack<T>::~Stack() {
    this->delData();
    this->len = this->capacity = 0;
}

template<typename T>
T Stack<T>::top() const {
    if(this->len == 0) {
        throw "No top element";
        return T();
    }
    return this->data[len - 1];
}

template<typename T>
void Stack<T>::pop() {
    if(this->len == 0) {
        throw "Cannot pop empty stack";
        return;
    }
    this->len--;
    if(this->len == this->capacity / 4) {
        this->modifyCap(0.5f);
    }
}

template<typename T>
bool Stack<T>::empty() const {
    return this->len == 0;
}

template<typename T>
size_t Stack<T>::size() const {
    return this->len;
}

template<typename T>
void Stack<T>::push(const T& value) {
   if(this->len == this->capacity) {
       this->modifyCap(2.0f);
   }
   this->data[this->len++] = value;
}

