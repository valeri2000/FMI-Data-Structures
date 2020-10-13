#include <iostream>
#include "Stack.cpp"

short getPrior(const char& ch) {
    if(ch == '+' || ch == '-') return 1;
    return 2; // *, /
}

void error() {
    std::cout << "Bad input data\n";
}

void calculate(const std::string& s) {
    int n = s.size();
    Stack<double> nums; bool flag;
    for(int i = 0; i < n; ++i) {
	if(s[i] == '+' || s[i] == '-' || s[i] == '*' || s[i] == '/') {
	   double num2 = nums.top(flag);
	   if(!flag) {
		error();
		break;
	   }
	   nums.pop(flag);
	   double num1 = nums.top(flag);
	   if(!flag) {
		error();
		break;
	   }
	   nums.pop(flag);
	   switch(s[i]) {
		case '+':
		    nums.push(num1 + num2);
		    break;
		case '-':
		    nums.push(num1 - num2);
		    break;
		case '*':
		    nums.push(num1 * num2);
		    break;
		case '/':
		    if(num2 == 0) {
			std::cout << "Div by zero!\n";
			break;
		    }
		    nums.push(num1 / num2);
		    break;
		default:
		    error();
	   }
	} else if(s[i] >= '0' && s[i] <= '9') {
	    nums.push(s[i] - '0');
	} else {
	    error();
	    break;
	}
    }
    if(nums.size() != 1) {
	std::cout << "Bad stack size!\n";
    } else {
	std::cout << nums.top(flag) << std::endl;
    }
}

int main() {
    std::string s = "4+2*3+5*6/3+6*2";
    // std::cin >> s;
    int n = (int)s.size();

    std::string res;
    Stack<char> oper; bool flag;
    for(int i = 0; i < n; ++i) {
	int curr = s[i];
	
	if(curr == '+' || curr == '-' || curr == '*' || curr == '/') {
	    while(!oper.empty() &&
		  getPrior(oper.top(flag)) >= getPrior(curr)) {
		res += oper.top(flag);
		oper.pop(flag);
	    }
	    oper.push(curr);
	} else if(curr >= '0' && curr <= '9') {
	    res += curr;
	} else {
	    error();
	    break;
	}
    }
    while(!oper.empty()) {
	res += oper.top(flag);
	oper.pop(flag);
    }

    std::cout << res << std::endl;
    calculate(res);
    return 0;
}
