#include <stdio.h>
#include <set>
#include <queue>
 
std::queue<int> cars[100001];
int command[500000];
 
long long int solve(int p, int k) {
    long long int ans = 0;
 
    std::set<std::pair<long long int, long long int>, std::greater<std::pair<long long int, long long int>>> cars_on_floor;
 
    for (int i = 0; i < p; ++i) {
        int key = command[i];
        long long res = 0;
 
        if (!cars[command[i]].empty()) {
            res = cars[command[i]].front();
            cars[command[i]].pop();
        } else {
            res = 100000001;
        }
 
        if (cars_on_floor.find(std::pair<int, int> (res, key)) != cars_on_floor.end()) {
            cars_on_floor.erase(std::pair<int, int> (res, key));
 
            if (!cars[command[i]].empty()) {
                cars_on_floor.insert(std::pair<int, int> (cars[command[i]].front(), key));
            } else {
                cars_on_floor.insert(std::pair<int, int> (100000001, key));
            }
        } else if (cars_on_floor.size() < k) {
            if (!cars[command[i]].empty()) {
                cars_on_floor.insert(std::pair<int, int> (cars[command[i]].front(), key));
            } else {
                if (!cars[command[i]].empty()) {
                    cars_on_floor.insert(std::pair<int, int> (100000001, key));
                }
            }
 
            ++ans;
        } else {
            cars_on_floor.erase(cars_on_floor.begin());
 
            if (!cars[command[i]].empty()) {
                cars_on_floor.insert(std::pair<int, int> (cars[command[i]].front(), key));
            } else {
                cars_on_floor.insert(std::pair<int, int> (100000001, key));
            }
 
            ++ans;
        }
    }
 
    return ans;
}
 
int main() {
    int n, k, p;
    scanf("%d %d %d", &n, &k, &p);
 
    for (int i = 0; i < p; ++i) {
        int number;
        scanf("%d", &number);
 
        command[i] = number;
        cars[number].push(i);
    }
 
    printf("%lld", solve(p, k));
 
    return 0;
}