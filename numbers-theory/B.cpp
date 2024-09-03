#include <iostream>
#include <vector>

uint64_t solve(uint64_t n) {
    uint64_t ans = 0;

    std::vector<bool> prime (n + 1, true);
    prime[0] = false;
    prime[1] = false;

    for (uint64_t i = 2; i <= n; ++i) {
        if (prime[i]) {
            for (uint64_t j = i * i; j <= n; j += i) {
                if (prime[j]) {
                    ans += i;
                    prime[j] = false;
                }
            }
        }
    }

    return ans;
}

int main() {
    uint64_t n;
    std::cin >> n;
    std::cout << solve(n);

    return 0;
}