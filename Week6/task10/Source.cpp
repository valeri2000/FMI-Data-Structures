#include <vector>

#include "node.h"

/***********************************************************************
  Задача 2. Даден е вектор v от цели числа. Казваме, че двоичното
  дърво с положителни числа по върховете t представя v при следните
  условия:

    * v е празният вектор и t е празното дърво; или
    * ако v = v[0],…,v[k-1], a m = ⌊k / 2⌋ (долна цяла част), то коренът
    на t съдържа числото v[m], лявото поддърво на t представя вектора
    v[0],…,v[m-1], а дясното поддърво на t представя вектора
    v[m+1],…,v[k-1].

  Забележка: ако k = 2, то десния подвектор считаме за празен.

  Нека е даден следният шаблонът Node, дефиниран в node.h.
************************************************************************/

/***********************************************************************
  а) Да се реализира функция, която построява дърво, представящо
  вектора v, и връща указател към корена му.

  Упътване: Ако v е вектор, то с помощта на следния конструктор
  std::vector<unsigned> L(v.begin(), v.begin() + count) ще получите
  първите count елемента от v,
  а с std::vector<unsigned> R (v.begin() + start, v.end()), ще
  получите суфикса на v, започващ от елемента с индекс start.

  Пример:
  std::vector<unsigned> v{1, 2, 3, 4, 5, 6},
                        L(v.begin(), v.begin() + 3),
                        R(v.begin() + 4, v.end());

  Тогава L е векторът 1, 2, 3, а R е векторът 5, 6.

 РЕШЕНИЕ:
************************************************************************/

Node<unsigned>* recBuild(const std::vector<unsigned>& v, unsigned l, unsigned r) {
    if(l + 1 == r) {
        return new Node<unsigned>({v[l], nullptr, nullptr});
    }
    if(l >= r) {
        return nullptr;
    }
    unsigned m = l + (r - l) / 2;
    Node<unsigned>* leftNode = recBuild(v, l, m);
    Node<unsigned>* rightNode = recBuild(v, m + 1, r);
    return new Node<unsigned>({v[m], leftNode, rightNode});
}

Node<unsigned>* buildTree(const std::vector<unsigned>& v) {
    if(v.size() == 0) {
        return nullptr;
    }
    return recBuild(v, 0, v.size());
}

/***********************************************************************
 б) Да се реализира функция, която връща вектор, съставен от възлите
 по път в дървото от корен до листо, в който сумата на елементите е
 максимална.

 РЕШЕНИЕ:
************************************************************************/

std::vector<unsigned> res, currRes;
unsigned bestSum;

void go(Node<unsigned>* curr, unsigned currSum) {
    if(curr == nullptr) {
        if(currSum > bestSum || res.size() == 0) {
            bestSum = currSum;
            res = currRes;
        }
        return;
    }
    currRes.push_back(curr->data);
    go(curr->left, currSum + currRes.back());
    go(curr->right, currSum + currRes.back());
    currRes.pop_back();
}

// greedy, slow, but it works
std::vector<unsigned> sumMax(Node<unsigned>* t) {
    res.clear();
    currRes.clear();
    go(t, 0);
    return res;
}

/***********************************************************************
 КРАЙ НА РЕШЕНИЕТО
************************************************************************/

#define DOCTEST_CONFIG_IMPLEMENT
#include "../../Doctest/doctest.h"

/***********************************************************************
  РАЗКОМЕНТИРАЙТЕ СЛЕДВАЩИЯ РЕД, ЗА ДА ВКЛЮЧИТЕ ТЕСТОВЕТЕ
************************************************************************/
#include "prob_tests.h"

int main()
{
	// пускане на тестовете
	doctest::Context().run();
	return 0;
}
