#include <iostream>

const int64_t m = 1000000007;

uint64_t opposite(uint64_t a) {
    uint64_t p = m - 2;
    uint64_t ans = 1;
    uint64_t a_p = a;

    while (p != 0) {
        if (p & 1) {
            ans = (ans * a_p) % m;
        }
        a_p = (a_p * a_p) % m;
        p >>= 1;
    }

    return ans;
}

int64_t solve(int64_t a, int64_t b) {
    a = (a + m) % m;
    b = (b + m) % m;
    return (b * opposite(a)) % m;
}

int main() {
    int64_t a, b, c, d;
    std::cin >> a >> b >> c >> d;

    std::cout << (solve(b, a) + solve(d, c)) % m;

    return 0;
}