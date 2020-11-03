#include <iostream>
#include <cassert>
#include "DLinkedList.cpp"

int main() {
    DLinkedList<int> l; 
    assert(l.empty() == true);
    l.assign(3, 3);
    l.push_front(2);
    l.push_front(1);
    l.push_back(4);
    l.push_back(5);
    std::cout << "size: " << l.size() << std::endl;
    assert(l.size() == 4 + 3);
    assert(l.back() == 5);
    assert(l.front() == 1);
    l.pop_back();
    assert(l.size() == 4 + 2);
    assert(l.back() == 4);
    l.pop_front();
    assert(l.size() == 4 + 1);
    assert(l.front() == 2);

    DLinkedList<int> l1(l);
    assert(l1.size() == 5);
    while(!l1.empty()) {
        std::cout << l1.front() << ' ';
        l1.pop_front();
    }
    std::cout << std::endl;

    while(!l.empty()) {
        std::cout << l.back() << ' ';
        l.pop_back();
    }
    std::cout << std::endl;

    std::cout << "Success\n";

    return 0;
}