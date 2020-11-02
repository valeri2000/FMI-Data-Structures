#include <iostream>
#include <vector>
#include "LinkedList.cpp"

int main() {
    /*
     * NOT TESTED COMPLETELY !!!
     */
    LinkedList<int> l;
    std::vector<int> v = {1, 2, 3, 4, 5};
    for(const int& i : v) {
        l.push_back(i);
    }
    for(const int& i : v) {
        l.push_front(i);
    }

    for(LinkedList<int>::LinkedListIterator it = l.begin(); it != l.end(); ++it) {
        std::cout << *it << ' ';
    }
    std::cout << std::endl;

    while(!l.empty()) {
        std::cout << l.front() << ' ';
        l.pop_front();
    }
    std::cout << std::endl;

    return 0;
}
