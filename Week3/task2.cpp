#include <iostream>
#include <cassert>
#include "../Stack/Stack.cpp"

template <typename T>
class Queue {
    private:
        Stack<T> one, two;

    public:
        void push(const T&);
        void pop();
        T front() const;
        size_t size() const;
        bool empty() const;
};

int main() {
    Queue<int> q;

    assert(q.empty());
    q.push(1);
    q.push(2);
    assert(q.size() == 2 && !q.empty());
    q.push(3);
    assert(q.front() == 1);
    q.pop();
    assert(q.front() == 2);

    std::cout << "Success!\n";
    return 0;
}

template<typename T>
void Queue<T>::push(const T& value) {
    while(!this->one.empty()) {
        this->two.push(this->one.top());
        this->one.pop();
    }
    this->one.push(value);
    while(!this->two.empty()) {
        this->one.push(this->two.top());
        this->two.pop();
    }
}

template<typename T>
void Queue<T>::pop() {
    if(this->one.empty()) {
        throw "Popping from empty stack!";
    }
    this->one.pop();
}

template<typename T>
T Queue<T>::front() const {
    if(this->one.empty()) {
        throw "Front of empty stack!";
    }
    return this->one.top();
}

template<typename T>
size_t Queue<T>::size() const {
    return this->one.size();
}

template<typename T>
bool Queue<T>::empty() const {
    return this->one.empty();
}
