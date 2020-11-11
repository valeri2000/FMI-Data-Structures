#ifndef __SKIP_LIST_H_INCLUDED
#define __SKIP_LIST_H_INCLUDED

#include <cstring>
#include <utility>
#include <vector>

template <typename T>
class SkipList {
    private:
        struct Node {
            T data;
            Node* nxt;
            Node* skip;

            Node(const T&, Node* = nullptr, Node* = nullptr);
        };

        Node* head;
        size_t len;
        bool hasSkips;

        void clearSkips();
        void clear();
        void copy(const SkipList&);

    public:
        SkipList();
        SkipList(const SkipList&);
        ~SkipList();
        SkipList& operator = (const SkipList&);

        void insert(const T&); // ascending order <=
        void buildSkips();
        std::pair<size_t, unsigned> findWithSkips(const T&, bool&) const; // position and number of steps done
        size_t findWithNxt(const T&, bool&) const; // position = number of steps done
        void getElements(std::vector<T>&) const;
        size_t size() const;
};

#endif
