#ifndef __BST_H_INCLUDED
#define __BST_H_INCLUDED

#include <vector>
#include <utility>

template <typename Key, typename Value>
class BST {
    private:
        struct Node {
            Key key;
            Value value;
            Node* left;
            Node* right;

            Node(const Key&, const Value&, Node* = nullptr, Node* = nullptr);
        };

        Node* build(const std::vector<std::pair<Key, Value> >&, unsigned, unsigned); 
        Node* copy(const Node*);
        void clear(Node*);
        void inorder(Node*) const;
        void helpPrint(Node*, unsigned) const;
        std::pair<Value, bool> helpSearch(Node*, const Key&) const;
        Node* insert(Node*, const std::pair<Key, Value>&);
        std::pair<unsigned, unsigned> dfs(Node*) const; // depth, leaves

        Node* root;

    public:
        BST();
        BST(const std::vector<std::pair<Key, Value> >&); // sorted vector
        BST(const BST&);
        BST& operator = (const BST&);
        ~BST();

        void print() const;
        void inorderPrint() const;
        std::pair<Value, bool> search(const Key&) const;
        void insert(const std::pair<Key, Value>&);
        // void remove(const Key&);
        unsigned height() const;
        unsigned countLeaves() const;
};

#endif
