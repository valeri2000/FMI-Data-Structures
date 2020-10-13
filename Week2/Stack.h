#ifndef __STACK_H_INCLUDED
#define __STACK_H_INCLUDED

#include <cstring>

template<typename T>
class Stack {
    private:
        T* data;
        size_t len, capacity;

        void delData();
        T* copyData() const;
        void modifyCap(const float); // factor * (capac)
    public:
        Stack();
        Stack(const Stack&);
        Stack& operator = (const Stack&);
        ~Stack();

        T top(bool&) const;
        void pop(bool&);
        bool empty() const;
        size_t size() const;
        void push(const T&);
};

#endif