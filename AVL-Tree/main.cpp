#include "AVL.cpp"

int main() {
    AVL<int, std::string> tree;
    tree.insert(1, "11");
    tree.insert(2, "12");
    tree.insert(3, "13");
    tree.insert(4, "14");
    tree.insert(5, "15");
    tree.insert(6, "16");
    tree.insert(7, "17");
    tree.insert(8, "18");
    tree.insert(9, "19");
    tree.insert(0, "0");
    tree.insert(-1, "01");
    tree.insert(-2, "02");
    tree.insert(-3, "03");
    tree.printKeys();
    
    auto p = tree.find(5);
    std::cout << p.first << ' ' << p.second << std::endl;
    p = tree.find(0);
    std::cout << p.first << ' ' << p.second << std::endl;
    p = tree.find(-2);
    std::cout << p.first << ' ' << p.second << std::endl;
    p = tree.find(1);
    std::cout << p.first << ' ' << p.second << std::endl;
    p = tree.find(-4);
    std::cout << p.second << std::endl;
    p = tree.find(10);
    std::cout << p.second << std::endl;

    AVL<int, std::string> tree2(tree), tree3;
    tree3 = tree;

    //tree2.printKeys();
    //tree3.printKeys();

    std::cout << "Hi\n";
    return 0;
}
