#include <iostream>
#include <fstream>
#include "Stack.cpp"

bool isValidSequence(std::ifstream& in) {
    Stack<char> st;
    bool fl;

    std::string s;
    getline(in, s);
    std::cout << "String: " << s << std::endl;

    bool okey = true;
    for(const char& ch : s) {
	if(ch == '(' || ch == '{' || ch == '[') {
	    st.push(ch);
	}
	else if(ch == ')') {
	    if(st.empty()) {
		okey = false;
		break;
	    }	
	    char top = st.top(fl);
	    st.pop(fl);
	    if(top != '(') {
		okey = false;
		break;
	    }
	}
	else if(ch == '}') {
	    if(st.empty()) {
		okey = false;
		break;
	    }	
	    char top = st.top(fl);
	    st.pop(fl);
	    if(top != '{') {
		okey = false;
		break;
	    }
	}
	else {
	    if(st.empty()) {
		okey = false;
		break;
	    }	
	    char top = st.top(fl);
	    st.pop(fl);
	    if(top != '[') {
		okey = false;
		break;
	    }
	}
    }

    return okey;
}

int main() {
    std::ifstream in("task11.in");
    bool isValid = isValidSequence(in);
    std::cout << "Valid: " << isValid << std::endl;
    in.close();

    std::ifstream in2("task12.in");
    isValid = isValidSequence(in2);
    std::cout << "Valid: " << isValid << std::endl;
    in2.close();

    return 0;
}
