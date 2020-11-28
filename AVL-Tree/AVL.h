#ifndef __AVL_H_INCLUDED
#define __AVL_H_INCLUDED

#include <utility>

template <typename Key, typename Value>
class AVL {
    private:
        struct Node {
            Key key;
            Value value;
            Node *left, *right;
            int height;

            Node(const Key&, const Value&, Node* = nullptr, Node* = nullptr, const int& = 1);
        };

        Node* root;

        int getHeight(Node*&) const;
        int getBalance(Node*) const;
        Node* rotateLeft(Node*);
        Node* rotateRight(Node*);

        Node* copy(const Node*);
        void del(Node*&);
        Node* insert(Node*, const Key&, const Value&);
        void printKeys(Node*, unsigned) const;

    public:
        AVL();
        AVL(const AVL&);
        ~AVL();
        AVL& operator = (const AVL&);

        void insert(const Key&, const Value&);
        // void remove(const Key&);
        // std::pair<Value, bool> find(const Key&) const;
        void printKeys() const;
};

#endif
