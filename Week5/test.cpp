#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../Doctest/doctest.h"

#include "SkipList.cpp"

TEST_CASE("Empty list") {
    SkipList<int> l;
    CHECK(l.size() == 0);
}

TEST_CASE("insert(), size()") {
    SkipList<int> l;
    std::vector<int> v = {5, 1, 2, 4, 3, 6, -10};
    for(const int& i : v) {
        l.insert(i);
    }
    std::sort(v.begin(), v.end());
    std::vector<int> vl;
    l.getElements(vl);
    CHECK(vl == v);
    CHECK(l.size() == v.size());
}

TEST_CASE("findWithNxt()") {
    SkipList<int> l;
    std::vector<int> v = {5, 1, 2, 4, 3, 6, -10};
    for(const int& i : v) {
        l.insert(i);
    }
    size_t index;
    bool ok;
    index = l.findWithNxt(-10, ok);
    CHECK(index == 0);
    CHECK(ok == true);
    index = l.findWithNxt(2, ok);
    CHECK(index == 2);
    CHECK(ok == true);
    index = l.findWithNxt(6, ok);
    CHECK(index == 6);
    CHECK(ok == true);
    index = l.findWithNxt(8, ok);
    CHECK(ok == false);
    index = l.findWithNxt(-20, ok);
    CHECK(ok == false);
    index = l.findWithNxt(1, ok);
    CHECK(ok == true);
    CHECK(index == 1);
}

TEST_CASE("findWithSkips()") {
    SkipList<int> l;
    for(int i = 1; i <= 10000; i += 2) {
        l.insert(i);
    }
    l.buildSkips();
    bool ok;
    for(int i = 1; i <= 10000; i += 2) {
        CHECK(l.findWithSkips(i, ok).first == l.findWithNxt(i, ok));
        auto smth = l.findWithSkips(i + 1, ok);
        CHECK(ok == false);
    }
    auto smth = l.findWithSkips(9999, ok);
    std::cout << "With skipping -> index " << smth.first << " with " << smth.second << " steps!\n";
}

