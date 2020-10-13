#include <iostream>
#include "Stack.cpp"

void error() {
    std::cout << "Invalid input!\n";
}

int main() {
    // std::string s = "(1+((2+3)*(4*5)))";
    std::string s = "(21+((42/3)+((10/2)*5)))";
    // std::cin >> s;
    int n = (int)s.size();

    bool flag;
    Stack<char> chars, oper;
    Stack<double> nums;
    for(int i = 0; i < n; ++i) {
	char curr = s[i];
	if(curr == '(') {
	    chars.push(curr);
	} 
	else if(curr == ')') {
	    char top = chars.top(flag);
	    if(!flag || top != '(') {
		error();
		break;
	    }
	    chars.pop(flag);

	    char op = oper.top(flag);
	    if(!flag) {
		error();
		break;
	    }
	    oper.pop(flag);

	    double num2, num1;
	    num2 = nums.top(flag);
	    if(!flag) {
		error();
		break;
	    }
	    nums.pop(flag);
	    num1 = nums.top(flag);
	    if(!flag) {
		error();
		break;
	    }
	    nums.pop(flag);
	    if(op == '+') {
		nums.push(num1 + num2);	
	    } else if(op == '-') {
		nums.push(num1 - num2);
	    } else if(op == '*') {
		nums.push(num1 * num2);
	    } else if(op == '/') {
		if(num2 == 0) {
		    std::cout << "Div by 0!\n";
		    error();
		    break;
		}
		nums.push(num1 / num2);
	    } else {
		error();
		break;
	    }
	} else if(curr == '+' || curr == '-' || curr == '*' || curr == '/') {
	    oper.push(curr);
	} else if(curr >= '0' && curr <= '9') {
	    int number = curr - '0';
	    int j = i + 1;
	    while(j < n && (s[j] >= '0' && s[j] <= '9')) {
		number = number * 10 + s[j] - '0';
		j++;
	    }
	    nums.push(number);
	    i = j - 1;
	} else {
	    error();
	    break;
	}
    }

    if(oper.size() > 0 || chars.size() > 0 || nums.size() != 1) {
	std::cout << "Bad sizes\n";
	std::cout << "Oper size: " << oper.size() << std::endl;
	std::cout << "Chars size: " << chars.size() << std::endl;
	std::cout << "Nums size: " << nums.size() << std::endl;
    } else {
	std::cout << "Result: " << nums.top(flag) << std::endl;
	nums.pop(flag);
    }
    
    return 0;
}
