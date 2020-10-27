#include "node.h"

/***********************************************************************
  Задача 3. Да се дефинира шаблон на булева функция dupsub, която
  приема два параметъра: указател към линеен едносвързан списък и
  неотрицателно число k. Функцията да връща истина, ако в списъка има
  поне два различни подсписъка с дължина k, които са с еднакви
  елементи. Примери за такива списъци са 1, 2, 3, 4, 1, 2, 5 и 1, 2,
  3, 3, 3, 4 за k = 2.
************************************************************************/

/***********************************************************************
 РЕШЕНИЕ:
************************************************************************/

template <typename T>
bool dupsub(node<T>* l, unsigned k) {
    auto same = [](node<T>* a, node<T>* b, unsigned len) {
        while(len > 0 && a != nullptr && b != nullptr) {
            if(a->data != b->data) {
                return false;
            }
            a = a->next;
            b = b->next;
            len--;
        }
        return (len == 0);
    };

    auto loopSublists = [same](node<T>* l, unsigned k) {
        if(l == nullptr || k == 0) {
            return false;
        }
        node<T>* a = l;
        node<T>* startb = a->next;
        unsigned _k = k - 1;
        while(startb != nullptr && _k > 0) {
            startb = startb->next;
            _k--;
        }
        if(_k > 0) {
            return false;
        }
        bool found = false;
        node<T>* b = startb;
        while(!found && a != nullptr) {
            if(b == nullptr) {
                a = a->next;
                if(startb == nullptr) break;
                startb = startb->next;
                b = startb;
            } else {
                found |= same(a, b, k);
                b = b->next;
            }
        }
        return found;
    };

    return loopSublists(l, k);
}

/***********************************************************************
 КРАЙ НА РЕШЕНИЕТО
************************************************************************/

#define DOCTEST_CONFIG_IMPLEMENT
#include "doctest.h"

/***********************************************************************
  РАЗКОМЕНТИРАЙТЕ СЛЕДВАЩИЯ РЕД, ЗА ДА ВКЛЮЧИТЕ ТЕСТОВЕТЕ
************************************************************************/
#include "prob5_tests.h"

int main ()
{
    // пускане на тестовете
    doctest::Context().run();
    return 0;
}
