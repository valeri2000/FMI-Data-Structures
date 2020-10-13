#include <iostream>
#include <cassert>
#include "Stack.cpp"

int main() {
    Stack<int> a;
    int num = -1;

    try {
        a.pop();
    } catch(const char* e) {
        std::cout << e << std::endl;
    }

    try {
        num = a.top();
    } catch(const char* e) {
        std::cout << e << std::endl;
    }

    a.push(10);
    assert(!a.empty());
    a.push(12);
    assert(a.size() == 2);
    assert(a.top() == 12);
    a.pop();
    assert(a.size() == 1);
    assert(a.top() == 10);
    a.pop();
    assert(a.empty());

    for(int i = 0; i < 1e5; ++i) {
        a.push(i);
    }
    Stack<int> b = a, c;
    c = a;
    assert(b.size() == 1e5 && c.size() == 1e5);

    int last = (int)(1e5) - 1;
    while(!a.empty()) {
        num = a.top();
        a.pop();
        assert(num == last);
        assert(a.size() == last);
        last--;
    }
    assert(a.size() == 0);

    for(int i = 0; i < 5; ++i) {
        a.push(i);
    }
    while(!a.empty()) {
        std::cout << a.top() << std::endl;
        a.pop();
    }

    std::cout << "\nSuccess!\n";
    return 0;
}
