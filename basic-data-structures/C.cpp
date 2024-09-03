#include <iostream>
#include <stack>
#include <stdio.h>
 
long long int find_answer(int n) {
    struct rectangle {
        int x;
        long long int h;
 
        rectangle(int x, long long int h): x(x), h(h) {}
    };
 
    std::stack<rectangle> stk;
    long long int answer = 0;
 
    stk.push(rectangle(0, -1));
 
    for (int i = 0; i <= n; i++) {
        long long int h;
 
        if (i < n) {
            scanf("%lld", &h);
        } else {
            h = 0;
		}
 
        int x = i;
 
        while (h <= stk.top().h) {
            x = stk.top().x;
            long long int square = stk.top().h * (i - x);
 
            stk.pop();
 
            if (square > answer) {
                answer = square;
			}
        }
 
        stk.push(rectangle(x, h));
    }
 
    return answer;
}
 
int main() {
    int n;
 
    scanf("%d", &n);
    printf("%lld", find_answer(n));
 
    return 0;
}