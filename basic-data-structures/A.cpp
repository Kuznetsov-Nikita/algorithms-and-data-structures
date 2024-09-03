#include <iostream>
#include <string>
 
typedef struct Node {
    long long int value;
    int size;
    Node* previous;
 
    Node(long long int value): value(value), size(0), previous(nullptr) {}
} Node;
 
void clear(Node** stk) {
    *stk = nullptr;
 
    std::cout << "ok\n";
}
 
bool is_empty(Node* stk) {
    return stk == nullptr;
}
 
int size(Node* stk) {
    if (is_empty(stk)) {
        return 0;
    } else {
        return stk->size;
	}
}
 
long long int pop(Node** stk) {
    long long int value = (*stk)->value;
    *stk = (*stk)->previous;
 
    return value;
}
 
long long int back(Node* stk) {
    return stk->value;
}
 
void push(Node** stk, long long int n) {
    Node* tmp = new Node(n);
 
    tmp->previous = *stk;
 
    if (!is_empty(*stk)) {
        tmp->size = (*stk)->size + 1;
    } else {
        tmp->size = 1;
	}
 
    *stk = tmp;
 
    std::cout << "ok\n";
}
 
void exit() {
    std::cout << "bye\n";
}
 
int main() {
    Node* stk = nullptr;
 
    long long int n;
    std::string command;
 
    do {
        std::cin >> command;
 
        if (command[1] == 'u') {
            std::cin >> n;
            push(&stk, n);
        } else if (command == "pop") {
            if (is_empty(stk)) {
                std::cout << "error\n";
			} else {
                std::cout << pop(&stk) << "\n";
			}
        } else if (command == "back") {
            if (is_empty(stk)) {
                std::cout << "error\n";
            } else {
                std::cout << back(stk) << "\n";
			}
        } else if (command == "size") {
            std::cout << size(stk) << "\n";
        } else if (command == "clear") {
            clear(&stk);
        } else {
            exit();
		}
    } while (command != "exit");
 
    return 0;
}