#ifndef __LINKED_LIST_H_INCLUDED
#define __LINKED_LIST_H_INCLUDED

template <typename T>
class LinkedList {
    private:
        struct Node {
            T data;
            Node* nxt;

            Node(const T&, Node* = nullptr);
        };
        Node* head;

        void clear();
        void copy(const LinkedList&);

    public:
        class LinkedListIterator {
            private:
                Node* ptr;

            public:
                LinkedListIterator(Node* = nullptr);
                LinkedListIterator(const LinkedListIterator&);

                LinkedListIterator& operator = (const LinkedListIterator&);
                LinkedListIterator& operator ++ ();
                LinkedListIterator operator ++ (int);
                T& operator * () const; // const ?
                bool operator == (const LinkedListIterator&) const;
                bool operator != (const LinkedListIterator&) const;
        };

        LinkedList();
        ~LinkedList();
        LinkedList(const LinkedList&);
        LinkedList& operator = (const LinkedList&);

        T& front();
        void push_front(const T&);
        void pop_front();
        void push_back(const T&);
        void pop_back();
        bool empty() const;

        LinkedListIterator begin();
        LinkedListIterator end();
};

#endif
