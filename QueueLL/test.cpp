#include <iostream>
#include <cassert>
#include "Queue.cpp"

int main() {
    Queue<int> q;
    int x;

    try {
        x = q.front();
    } catch(const char* e) {
        std::cout << e << std::endl;
    }

    try {
        q.pop(); 
    } catch(const char* e) {
        std::cout << e << std::endl;
    }

    assert(q.size() == 0 && q.empty());
    for(int i = 1; i <= 10; ++i) {
        q.push(i);
    }

    assert(q.size() == 10 && !q.empty());
    assert(q.front() == 1);
    q.push(11);
    assert(q.front() == 1);
    q.pop();
    assert(q.front() == 2);

    while(!q.empty()) {
        q.pop();
    }
    assert(q.size() == 0 && q.empty());

    for(int i = 1; i <= 20; ++i) {
        q.push(i);
    }

    Queue<int> copy1 = q, copy2;
    copy2 = q;
    assert(copy1.size() == q.size() && copy2.size() == q.size());

    while(q.size()) {
        std::cout << q.front() << " = "
                  << copy1.front() << " = "
                  << copy2.front() << std::endl;
        q.pop();
        copy1.pop();
        copy2.pop();
    }

    std::cout << "\nSuccess\n";
    return 0;
}
