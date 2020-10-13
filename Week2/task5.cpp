#include <iostream>
#include <utility>
#include "Stack.cpp"

int main() {
    int n;
    std::cin >> n;

    Stack<std::pair<int, int> > st; bool flag; 
    for(int i = 0; i < n; ++i) {
	int x;
	std::cin >> x;
	if(st.empty()) {
	    st.push({x, x});
	} else {
	    st.push({x, std::max(st.top(flag).second, x)});
	}
    }	
    while(!st.empty()) {
	std::pair<int, int> top = st.top(flag);
	std::cout << "Maximum before popping " << top.first << " is " 
	          << top.second << std::endl;
	st.pop(flag);
    }

    return 0;
}
