#ifndef __QUEUE_H_INCLUDED
#define __QUEUE_H_INCLUDED

#include <cstring>

template <typename T>
struct Node {
    T data;
    Node<T>* nxt;
};

template <typename T>
class Queue {
    private:
        Node<T>* head;
        Node<T>* tail;
        size_t length;

        void delWhole();
        void copyWhole(const Queue&);

    public:
        Queue();
        Queue(const Queue&);
        Queue& operator = (const Queue&);
        ~Queue();

        bool empty() const;
        size_t size() const;
        T front() const;
        void push(const T&);
        void pop();
};

#endif
