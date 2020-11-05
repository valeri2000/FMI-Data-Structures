#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../Doctest/doctest.h"

#include <vector>
#include "DLinkedList.cpp"

TEST_CASE("Empty list") {
    DLinkedList<int> l; DLinkedList<double> l1;
    CHECK(l.empty() == true);
    CHECK(l.size() == 0);
}

TEST_CASE("push_front() and front()") {
    DLinkedList<int> l;
    l.push_front(1);
    CHECK(l.empty() == false);
    CHECK(l.size() == 1);
    CHECK(l.front() == 1);
    l.push_front(2);
    CHECK(l.empty() == false);
    CHECK(l.size() == 2);
    CHECK(l.front() == 2);
}

TEST_CASE("push_back() and back()") {
    DLinkedList<int> l;
    l.push_back(1);
    CHECK(l.empty() == false);
    CHECK(l.size() == 1);
    CHECK(l.back() == 1);
    l.push_back(2);
    CHECK(l.empty() == false);
    CHECK(l.size() == 2);
    CHECK(l.front() == 1);
    CHECK(l.back() == 2);
}

TEST_CASE("assign()") {
    DLinkedList<int> l;
    l.assign(4, 2);
    CHECK(l.size() == 4);
    CHECK(l.front() == 2);
    CHECK(l.back() == 2);
}

TEST_CASE("pop_front()") {
    DLinkedList<int> l;
    l.push_front(1);
    l.pop_front();
    CHECK(l.size() == 0);
    CHECK(l.empty() == true);
    l.push_front(2);
    l.push_front(3);
    l.push_front(4);
    l.pop_front();
    CHECK(l.size() == 2);
    CHECK(l.empty() == false);
    CHECK(l.front() == 3);
    CHECK(l.back() == 2);
}

TEST_CASE("pop_back()") {
    DLinkedList<int> l;
    l.push_back(1);
    l.pop_back();
    CHECK(l.size() == 0);
    CHECK(l.empty() == true);
    l.push_front(2);
    l.push_front(3);
    l.push_front(4);
    l.pop_back();
    CHECK(l.size() == 2);
    CHECK(l.empty() == false);
    CHECK(l.front() == 4);
    CHECK(l.back() == 3);
}

TEST_CASE("insertBefore()") {
    DLinkedList<int> l;
    l.push_back(1);
    l.insertBefore(0, 3);
    CHECK(l.size() == 2);
    CHECK(l.front() == 3);
    CHECK(l.back() == 1);
    l.insertBefore(1, 2);
    CHECK(l.size() == 3);
    CHECK(l.front() == 3);
    CHECK(l.back() == 1);
    l.insertBefore(3, 0);
    CHECK(l.front() == 3);
    CHECK(l.back() == 0);
}

TEST_CASE("erase()") {
    DLinkedList<int> l;
    l.push_back(1);
    l.erase(0);
    CHECK(l.empty() == true);
    CHECK(l.size() == 0);
    l.push_back(1);
    l.push_back(2);
    l.erase(1);
    CHECK(l.size() == 1);
    CHECK(l.front() == 1);
    l.push_back(2);
    l.erase(0);
    CHECK(l.front() == 2);
    l.push_front(1);
    l.push_back(3);
    l.erase(1);
    CHECK(l.size() == 2);
    CHECK(l.front() == 1);
    CHECK(l.back() == 3);
}

TEST_CASE("clear()") {
    DLinkedList<int> l;
    l.push_back(1);
    l.clear();
    CHECK(l.size() == 0);
    CHECK(l.empty() == true);
    l.push_back(1); l.push_back(1);
    l.clear();
    CHECK(l.size() == 0);
    CHECK(l.empty() == true);
    l.push_back(1); l.push_back(1); l.push_back(1);
    l.clear();
    CHECK(l.size() == 0);
    CHECK(l.empty() == true);
}

TEST_CASE("filter()") {
    DLinkedList<int> l;
    for(size_t i = 1; i <= 6; ++i) {
        l.push_back(i);
    }
    auto odd = [](const int& value) {
        return value % 2 == 1;
    };
    l.filter(odd);
    CHECK(l.size() == 3);
    CHECK(l.front() == 1);
    CHECK(l.back() == 5);
    l.pop_back();
    CHECK(l.back() == 3);
}

TEST_CASE("map()") {
    DLinkedList<int> l;
    for(size_t i = 1; i <= 6; ++i) {
        l.push_back(i);
    }
    auto mul2 = [](const int& value) {
        return value * 2;
    };
    l.map(mul2);
    CHECK(l.size() == 6);
    CHECK(l.front() == 2);
    CHECK(l.back() == 12);
    l.pop_back();
    CHECK(l.back() == 10);
}

TEST_CASE("Copy list") {
    DLinkedList<int> l;
    for(size_t i = 1 ; i <= 6; ++i) {
        l.push_back(i);
    }
    DLinkedList<int> l1(l), l2;
    l2 = l;
    CHECK(l1.size() == 6);
    CHECK(l2.size() == 6);
    CHECK(l1.empty() == 0);
    CHECK(l2.empty() == 0);
    CHECK(l1.front() == 1);
    CHECK(l2.back() == 6);
    l1.pop_back();
    l2.pop_front();
    CHECK(l1.back() == 5);
    CHECK(l2.front() == 2);
}

TEST_CASE("Iterator") {
    DLinkedList<int> l;
    std::vector<int> v;
    for(size_t i = 1 ; i <= 6; ++i) {
        l.push_back(i);
        v.push_back(i);
    }
    CHECK(*l.begin() == 1);
    l.pop_front();
    CHECK(*l.begin() == 2);
    l.push_front(1);
    size_t index = 0;
    for(auto it = l.begin(); it != l.end(); ++it) {
        CHECK(v[index++] == *it);
    }
    index = 0;
    for(auto it = l.begin(); it != l.end(); it++) {
        CHECK(v[index++] == *it);
    }
    index = v.size() - 1;
    for(auto it = --l.end(); it != l.begin(); --it) {
        CHECK(v[index--] == *it);
    }
    index = v.size() - 1;
    for(auto it = --l.end(); it != l.begin(); it--) {
        CHECK(v[index--] == *it);
    }
    v.pop_back();
    l.pop_back();
    index = 0;
    for(auto it = l.begin(); it != l.end(); ++it) {
        CHECK(v[index++] == *it);
    }
    index = v.size() - 1;
    for(auto it = --l.end(); it != l.begin(); --it) {
        CHECK(v[index--] == *it);
    }
}

