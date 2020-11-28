#include "AVL.cpp"

int main() {
    AVL<int, std::string> tree;
    tree.insert(1, "a");
    tree.insert(2, "a");
    tree.insert(3, "a");
    tree.insert(4, "a");
    tree.insert(5, "a");
    tree.insert(6, "a");
    tree.insert(7, "a");
    tree.insert(8, "a");
    tree.insert(9, "a");
    tree.insert(0, "a");
    tree.insert(-1, "a");
    tree.insert(-2, "a");
    tree.insert(-3, "a");
    tree.printKeys();

    AVL<int, std::string> tree2(tree), tree3;
    tree3 = tree;

    //tree2.printKeys();
    //tree3.printKeys();

    std::cout << "Hi\n";
    return 0;
}
