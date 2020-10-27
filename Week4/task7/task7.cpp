#include "node.h"
#include<iostream>
/***********************************************************************
  Задача 6. Да се дефинира шаблон на функция removesub, която приема
  два параметъра first и second — указатели към линейни едносвързани
  списъци. Функцията да изтрива от списъка с начало first
  последователно всички срещания на подсписъци, които съвпадат със
  списъка с начало second. Например, при списък first с елементи 1, 2,
  3, 3, 3, 4, 5, 3, 3, 6 и second с елементи 3, 3, first да се
  преобразува до списъка 1, 2, 3, 4, 5, 6.
************************************************************************/

/***********************************************************************
 РЕШЕНИЕ:
************************************************************************/

template <typename T>
void removesub(node<T>*& first, node<T>* second){
    if(second == nullptr || first == nullptr) return;

    auto same = [](node<T>* a, node<T>* b, unsigned& len) {
        len = 0;
        while(a != nullptr && b != nullptr) {
            if(a->data != b->data) {
                return false;
            }
            len++;
            a = a->next;
            b = b->next;
        }
        return (b == nullptr);
    };

    auto deleteElem = [](node<T>*& prev, node<T>*& a, unsigned len) {
        node<T>* temp = a;
        node<T>* temp2;
        while(len > 0) {
            temp2 = temp->next;
            delete temp;
            temp = temp2;
            len--;
        }
        a = temp;
        prev->next = a;
    };

    unsigned len;
    node<T>* dummyFirst = new node<T>((1 << 30), first);
    first = dummyFirst;
    while(first->next != nullptr) {
        if(same(first->next, second, len)) {
            deleteElem(first, first->next, len);
        } else {
            first = first->next;
        }
    }
    first = dummyFirst->next;
}

/***********************************************************************
 КРАЙ НА РЕШЕНИЕТО
************************************************************************/

#define DOCTEST_CONFIG_IMPLEMENT
#include "doctest.h"

/***********************************************************************
  РАЗКОМЕНТИРАЙТЕ СЛЕДВАЩИЯ РЕД, ЗА ДА ВКЛЮЧИТЕ ТЕСТОВЕТЕ
************************************************************************/
#include "prob7_tests.h"

int main ()
{
    // пускане на тестовете
    doctest::Context().run();
    return 0;
}
