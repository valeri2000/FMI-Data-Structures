#include <iostream>
#include <cassert>
#include "../QueueLL/Queue.cpp"

template <typename T>
class PQueue {
    private:
        Queue<T> low, normal, high;

    public:
        void push(const T&, const std::string = {"NORMAL"});
        void pop();
        T front() const;
        bool empty() const;
        size_t size() const;
        void print();
};

int main() {
    PQueue<std::string> q;

    assert(q.empty() && q.size() == 0);
    q.push("low1", "LOW");
    assert(!q.empty() && q.size() == 1);
    q.push("high1", "HIGH");
    assert(q.front() == "high1");
    q.push("normal1", "NORMAL");
    q.pop();
    assert(q.front() == "normal1");

    q.push("low11", "LOW");
    q.push("low22", "LOW");
    q.push("low33", "LOW");
    q.push("high11", "HIGH");
    q.push("high22", "HIGH");
    q.push("high33", "HIGH");
    q.push("normal11");
    q.push("normal22", "NORMAL");
    q.push("normal33");

    q.print();

    std::cout << "Success!\n";
    return 0;
}

template <typename T>
void PQueue<T>::push(const T& value, const std::string pr) {
    if(pr == "LOW") low.push(value);
    else if(pr == "NORMAL") normal.push(value);
    else if(pr == "HIGH") high.push(value);
    else throw "Invalid priority";
}

template <typename T>
void PQueue<T>::pop() {
    if(!high.empty()) high.pop();
    else if(!normal.empty()) normal.pop();
    else if(!low.empty()) low.pop();
    else throw "No elements to pop";
}

template <typename T>
T PQueue<T>::front() const {
    if(!high.empty()) return high.front();
    if(!normal.empty()) return normal.front();
    if(!low.empty()) return low.front();
    throw "No elements to peek";
    return T();
}

template <typename T>
bool PQueue<T>::empty() const {
    return high.empty() && normal.empty() && low.empty();
}

template <typename T>
size_t PQueue<T>::size() const {
    return high.size() + normal.size() + low.size();
}

template <typename T>
void PQueue<T>::print() {
    std::cout << "PQueue:\n";
    while(!empty()) {
        std::cout << "\t" << front() << std::endl;
        pop();
    }
    std::cout << std::endl;
}

