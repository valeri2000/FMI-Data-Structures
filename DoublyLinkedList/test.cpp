#include <iostream>
#include <cassert>
#include "DLinkedList.cpp"

void testListFunctionality() {
    DLinkedList<int> l; 
    assert(l.empty() == true);
    l.assign(3, 3);
    l.push_front(2);
    l.push_front(1);
    l.push_back(4);
    l.push_back(5);
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
    std::cout << "List functionality ok!\n";
}

void testIteratorFunctionality() {
    DLinkedList<int> l;
    for(size_t i = 0; i < 5; ++i) {
        l.push_back(i);
    }
    for(auto it = l.begin(); it != l.end(); ++it) {
        std::cout << *it << ' ';
    }
    std::cout << std::endl;
    std::cout << "Begin: " << *l.begin() << std::endl;
    std::cout << "Last elem: " << *(--l.end()) << std::endl;
    auto it = l.begin(); ++it;
    std::cout << "Second elem: " << *it << std::endl;
    it++;
    std::cout << "Third elem: " << *it << std::endl;
    it--;
    std::cout << "Second again: " << *it << std::endl;
    --it;
    std::cout << "First elem: " << *it << std::endl;
    it = --l.end(); it--; it++;
    std::cout << "Last elem: " << *it << std::endl;
}

int main() {
    testListFunctionality();
    testIteratorFunctionality();
    return 0;
}
