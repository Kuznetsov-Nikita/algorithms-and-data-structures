#include <iostream>
#include <string>
#include <stack>
 
int main() {
    std::string brackets_sequence, answer = "yes";
    std::stack<char> stk;
 
    std::cin >> brackets_sequence;
 
    for (unsigned int i = 0; i < brackets_sequence.size(); i++) {
        if (brackets_sequence[i] == '(' || brackets_sequence[i] == '[' || brackets_sequence[i] == '{') {
            stk.push(brackets_sequence[i]);
        } else {
            if (stk.empty() || (brackets_sequence[i] == ')' && stk.top() != '(') || (brackets_sequence[i] == ']' && stk.top() != '[') || (brackets_sequence[i] == '}' && stk.top() != '{')) {
                answer = "no";
                break;
            }
 
            stk.pop();
        }
    }
 
    if (!stk.empty()) {
        answer = "no";
	}
 
    std::cout << answer;
 
    return 0;
}