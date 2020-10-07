#include <iostream>
#include <cassert>
#include "Stack.cpp"

int main() {
    Stack<int> a;
    int numb;
    bool fl;

    assert(a.size() == 0);
    assert(a.empty() == 1);
    a.pop(fl);
    assert(fl == 0);
    numb = a.top(fl);
    assert(fl == 0); 

    for(int i = 0; i < 10001; ++i) {
        a.push(i);
    }
    Stack<int> b, c = a;
    b = a;
    assert(a.empty() == 0);
    assert(a.size() == 10001);
    assert(b.size() == 10001);
    assert(c.size() == 10001);
    assert(a.top(fl) == 10000);
    assert(fl == 1);
    a.pop(fl);
    assert(fl == 1);
    assert(a.top(fl) == 9999);
    assert(fl == 1);

    while(!a.empty()) {
        numb = a.top(fl);
        assert(fl == 1);
        a.pop(fl);
        assert(fl == 1);
    }
    assert(a.size() == 0);
    assert(a.empty() == 1);
    assert(numb == 0);
    
    std::cout << "Success!\n";
    return 0;
}
