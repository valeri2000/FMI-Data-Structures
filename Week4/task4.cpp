#include <iostream>
#include <vector>
#include <cassert>

template <typename T>
struct Node {
    T data;
    Node<T>* nxt;
};

template <typename T>
Node<T>* createList(const std::vector<T>& v) {
    int n = (int)v.size();
    Node<T>* res = nullptr;
    if(!n) {
        return res;
    }
    res = new Node<T>({v[0], nullptr});
    Node<T>* temp = res;
    for(int i = 1; i < n; ++i) {
        Node<T>* curr = new Node<T>({v[i], nullptr});
        temp->nxt = curr;
        temp = curr;
    }
    return res;
}

template <typename T>
void deleteList(Node<T>* l) {
    if(l == nullptr) {
        return;
    }
    if(l->nxt == nullptr) {
        delete l;
        l = nullptr;
        return;
    }
    deleteList(l->nxt);
    delete l;
    l = nullptr;
}

template <typename T>
void printList(Node<T>* l) {
    Node<T>* temp = l;
    std::cout << "List: ";
    while(temp != nullptr) {
        std::cout << temp->data << ' ';
        temp = temp->nxt;
    }
    std::cout << "\n";
}

template <typename T>
void reverse(Node<T>*& l) {
    Node<T>* temp = l;
    Node<T>* prev = nullptr;
    while(temp != nullptr) {
        Node<T>* nextTemp = temp->nxt; // get next
        temp->nxt = prev; // reverse previous link
        prev = temp;
        temp = nextTemp;
    }
    l = prev;
}

template <typename T>
bool compareLists(Node<T>* a, Node<T>* b) {
    bool same = true;
    while(b != nullptr) {
        if(a->data != b->data) {
            same = false;
            break;
        }
        a = a->nxt;
        b = b->nxt;
    }
    return same;
}

template <typename T>
bool isPali(Node<T>* l) {
    if(l == nullptr || l->nxt == nullptr) {
        return true;
    }
    Node<T>* slow, *fast;
    slow = l, fast = l;
    while(fast != nullptr && fast->nxt != nullptr) {
        fast = (fast->nxt)->nxt;
        slow = slow->nxt;
    }
    if(fast != nullptr) { // odd
        slow = slow->nxt;
    }
    // slow -> beginning of second half
    reverse(slow);
    bool res = compareLists(l, slow);
    reverse(slow);
    return res;
}

int main() {
    std::vector<int> v;
    Node<int>* l = nullptr;

    v = {};
    l = createList(v);
    assert(isPali(l) == 1);
    deleteList(l);

    v = {1};
    l = createList(v);
    assert(isPali(l) == 1);
    deleteList(l);

    v = {1, 2};
    l = createList(v);
    assert(isPali(l) == 0);
    deleteList(l);

    v = {1, 2, 1};
    l = createList(v);
    assert(isPali(l) == 1);
    deleteList(l);

    v = {1, 2, 1, 1};
    l = createList(v);
    assert(isPali(l) == 0);
    deleteList(l);

    v = {1, 1, 1, 1};
    l = createList(v);
    assert(isPali(l) == 1);
    deleteList(l);

    v = {1, 2, 2, 1};
    l = createList(v);
    assert(isPali(l) == 1);
    deleteList(l);

    v = {1, 2, 3, 1};
    l = createList(v);
    assert(isPali(l) == 0);
    deleteList(l);

    v = {1, 2, 3, 3, 2, 1};
    l = createList(v);
    assert(isPali(l) == 1);
    deleteList(l);

    v = {1, 2, 3, 2, 1};
    l = createList(v);
    assert(isPali(l) == 1);
    deleteList(l);

    std::cout << "Success\n";

    return 0;
}
