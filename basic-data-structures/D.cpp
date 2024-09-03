#include <stdio.h>
#include <deque>
 
int pop(std::deque<int>& goblins_queue) {
    int number = goblins_queue.front();
    goblins_queue.pop_front();
 
    return number;
}
 
void push(std::deque<int>& goblins_queue, int number) {
    goblins_queue.push_back(number);
}
 
void vip_push(std::deque<int>& goblins_queue, int number) {
    goblins_queue.push_front(number);
}
 
void balancing(std::deque<int>& goblins_queue_first, std::deque<int>& goblins_queue_second) {
    if (goblins_queue_second.size() > goblins_queue_first.size()) {
        int number = pop(goblins_queue_second);
        push(goblins_queue_first, number);
    }
}
 
int main() {
    std::deque<int> goblins_queue_first, goblins_queue_second;
    int n, number;
    char command;
 
    scanf("%d", &n);
 
    for (int i = 0; i < n; ++i) {
        scanf("\n%c", &command);
 
        if (command == '-') {
            printf("%d\n", pop(goblins_queue_first));
        } else {
            scanf("%d", &number);
 
            (command == '+') ? push(goblins_queue_second, number) : vip_push(goblins_queue_second, number);
        }
 
        balancing(goblins_queue_first, goblins_queue_second);
    }
 
    return 0;
}