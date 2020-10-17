#include <iostream>
#include <cmath>
#include <cassert>

#include "../Stack/Stack.cpp" // new stack

const double EPS = 0.000000001;

bool nextEquation(int& index, const int& lim, const std::string& s, std::string& res) {
    while(index < lim && s[index] == ' ') {
        index++;
    }
    if(index >= lim) {
        return false;
    }
    res = "";
    while(index < lim && s[index] != '=') {
        res += s[index++];
    }
    index++;
    return true;
}

short getPriority(const char& ch) {
    if(ch == '(') return 0;
    if(ch == '+' || ch == '-') return 1;
    return 2;
}

void translate(const std::string& s, std::string& res) {
    res = "";
    int n = (int)s.size();

    Stack<char> op;
    op.push('(');

    for(int i = 0; i < n; ++i) {
        char curr = s[i];
        if(curr == ')') {
            while(op.top() != '(')  {
                res += op.top();
                op.pop();
            }
            op.pop();
        } else if(curr >= '0' && curr <= '9') {
            int j = i;
            while(j < n && (s[j] >= '0' && s[j] <= '9')) {
                res += s[j++];
            }
            res += '#';
            i = j - 1;
        } else if(curr == '+' || curr == '-' || curr == '*' || curr == '/') {
            short currPrior = getPriority(curr);
            while(!op.empty() && getPriority(op.top()) >= currPrior) {
                res += op.top();
                op.pop();
            }
            op.push(curr);
        } else if(curr == '(') {
            op.push(curr);
        }     
    }

    while(!op.empty()) {
        res += op.top();
        op.pop();
    }
    res.pop_back();
}

double calculate(const std::string& s) {
    int n = (int)s.size();
    Stack<double> nums;

    for(int i = 0 ; i < n; ++i) {
        char curr = s[i];
        if(curr >= '0' && curr <= '9') {
            int value = 0;
            while(s[i] != '#') {
                value = value * 10 + s[i++] - '0';
            }
            nums.push(value);
        } else {
            if(nums.size() < 2) {
                assert(false);
            }
            double b, a, c;
            b = nums.top(); nums.pop();
            a = nums.top(); nums.pop();
            switch(curr) {
                case '+':
                    c = a + b;
                    break;
                case '-':
                    c = a - b;
                    break;
                case '/':
                    if(b == 0) {
                        assert(0);
                    }
                    c = a / b;
                    break;
                case '*':
                    c = a * b;
                    break;
                default:
                    assert(0);
            }
            nums.push(c);
        }
    }

    if(nums.size() != 1) {
        assert(false);
    }

    return nums.top();
}

int main() {
    /*
    3 + 2 = 5
    7 - 3 * 2 + 1 = 4 * 2 + 1 = 8 + 1 = 9
    12 * 3 = 2 * 2 * 6 / 4 * 2 * (1 + 2) = 36 - 2 / 1 / 2 + (2 * 3) / (6 / 1) = 36
    3 / 2 * 2 = 3
    */
    std::string s;
    getline(std::cin, s);

    Stack<double> values;
    int index = 0, lim = (int)s.size();
    double value;
    std::string curr, trans;
    while(nextEquation(index, lim, s, curr)) {
        translate(curr, trans);
        value = calculate(trans);
        values.push(value);
    }

    double wanted = values.top();
    values.pop();
    int all = 0, good = 0;
    while(!values.empty()) {
        all++;
        value = values.top();
        values.pop();
        if(fabs(value - wanted) < EPS) {
            good++;
        }
    }

    std::cout << good << " / " << all << std::endl;

    return 0;
}
