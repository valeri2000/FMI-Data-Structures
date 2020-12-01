#include "BST.cpp"

int main() {
    const std::vector<std::pair<int, std::string> > data = {
        {1, "One"},
        {2, "Two"},
        {3, "Three"},
        {4, "Four"},
        {5, "Five"},
        {6, "Six"},
        {7, "Seven"},
    };

    BST<int, std::string> tree(data);
    tree.print();
    tree.inorderPrint();

    std::cout << "4: " << tree.search(4).first << std::endl;
    std::cout << "1: " << tree.search(1).first << std::endl;
    std::cout << "7: " << tree.search(7).first << std::endl;
    std::cout << "10: " << tree.search(10).first << std::endl;

    std::cout << "Height: " << tree.height()
              << "\nLeaves: " << tree.countLeaves() << std::endl;

    tree.insert(std::make_pair(10, "Ten"));
    tree.print();
    std::cout << "Height: " << tree.height()
              << "\nLeaves: " << tree.countLeaves() << std::endl;
    std::cout << "10: " << tree.search(10).first << std::endl;

    tree.remove(4);
    tree.print();
    tree.remove(5);
    tree.print();
    tree.remove(2);
    tree.print();

    //BST<int, std::string> tree1(tree), tree2;
    //tree2 = tree;
    //tree2.print();
    //tree1.print();

    return 0;
}
