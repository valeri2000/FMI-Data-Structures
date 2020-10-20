#include <iostream>
#include <cassert>
#include <vector>
#include "../QueueLL/Queue.cpp"

template <typename T>
Queue<T>* mergeSorted(Queue<T> one, Queue<T> two) { // make copies
    Queue<T>* res = new Queue<T>;
    while(!one.empty() && !two.empty()) {
        int top1 = one.front(), top2 = two.front();
        if(top1 < top2) {
            res->push(top1);
            one.pop();
        } else {
            res->push(top2);
            two.pop();
        }
    }
    while(!one.empty()) {
        res->push(one.front());
        one.pop();
    }
    while(!two.empty()) {
        res->push(two.front());
        two.pop();
    }
    return res;
}

int main () {
    std::vector<int> v1 = {-5, 0, 1, 4, 5}; Queue<int> one;
    std::vector<int> v2 = {1, 2, 3, 4, 5, 6}; Queue<int> two;   
    for(const int& i : v1) one.push(i);
    for(const int& i : v2) two.push(i);

    Queue<int>* res = mergeSorted(one, two);

    assert(res->size() == one.size() + two.size());
    while(!res->empty()) {
        std::cout << res->front() << ' ';
        res->pop();
    }
    std::cout << '\n';
    
    delete res;
    return 0;
}
