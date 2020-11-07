#ifndef __DLINKED_LIST_H_INCLUDED
#define __DLINKED_LIST_H_INCLUDED

#include <cstring> // size_t

template <typename T>
class DLinkedList {
    private:
        struct Node {
            T data;
            Node* prv;
            Node* nxt;
            bool isEnd; // for iterator

            Node(const T&, Node*, Node*, const bool = false);
        };

        Node* head;
        size_t len;

        void helpClear();
        void helpCopy(const DLinkedList&);
    public:
        class DLinkedListIterator {
            private:
                Node* ptr;
                Node* lastElemPtr; // back of the list
                bool passedLast; // have we passed it

                void copyIt(const DLinkedListIterator&);
            public:
                DLinkedListIterator(Node* = nullptr, Node* = nullptr, const bool = false);
                DLinkedListIterator(const DLinkedListIterator&);

                DLinkedListIterator& operator = (const DLinkedListIterator&);
                DLinkedListIterator& operator ++ ();
                DLinkedListIterator operator ++ (int);
                DLinkedListIterator& operator -- ();
                DLinkedListIterator operator -- (int);
                operator bool () const;
                bool operator ! () const;
                T& operator * () const;
                bool operator == (const DLinkedListIterator&) const;
                bool operator != (const DLinkedListIterator&) const;
        };

        DLinkedList();
        ~DLinkedList();
        DLinkedList(const DLinkedList&);
        DLinkedList& operator = (const DLinkedList&);

        DLinkedListIterator begin();
        DLinkedListIterator end();
        const DLinkedListIterator cbegin();
        const DLinkedListIterator cend();
        DLinkedListIterator find(const T&);

        bool empty() const;
        size_t size() const;
        T& front();
        T& back();
        void assign(const size_t, const T&); // n copies of T
        void push_front(const T&);
        void push_back(const T&);
        void pop_front();
        void pop_back();
        void insertBefore(const size_t, const T&); // position, value 
        void erase(const size_t); // position
        void clear();
        void filter(bool (*pred)(const T& value));
        void map(T (*func)(const T& value));
};

#endif
