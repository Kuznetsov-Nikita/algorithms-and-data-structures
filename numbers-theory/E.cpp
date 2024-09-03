#include <iostream>
#include <vector>

const uint64_t MOD = 1000000007;

uint64_t factorial[200001];

uint64_t binpow(uint64_t a, uint64_t p) {
    uint64_t ans = 1;
    uint64_t a_p = a;

    while (p != 0) {
        if (p & 1) {
            ans = (ans * a_p) % MOD;
        }
        a_p = (a_p * a_p) % MOD;
        p >>= 1;
    }

    return ans;
}

uint64_t opposite(uint64_t a) {
    return binpow(a, MOD - 2);
}

void calculate_factorials(uint64_t n) {
    uint64_t current_factorial = 1;

    factorial[0] = 1;
    for (uint64_t i = 1; i <= n; ++i) {
        current_factorial = (current_factorial * i) % MOD;
        factorial[i] = current_factorial;
    }
}

uint64_t c(uint64_t n, uint64_t k) {
    return (factorial[n] * ((opposite(factorial[k]) * opposite(factorial[n - k])) % MOD)) % MOD;
}

uint64_t stirling_number(uint64_t n, uint64_t k) {
    if (n == 0 || k == 0) {
        if (n == 0 && k == 0) {
            return 1;
        } else {
            return 0;
        }
    }

    uint64_t number = 0;
    for (uint64_t i = 0; i <= k; ++i) {
        if ((k + i) % 2 == 0) {
            number = (number + (c(k, i) * binpow(i, n)) % MOD) % MOD;
        } else {
            number = (number + MOD - (c(k, i) * binpow(i, n)) % MOD) % MOD;
        }
    }
    number = (number * opposite(factorial[k])) % MOD;

    return number;
}

int main() {
    uint64_t n, k;
    std::cin >> n >> k;

    uint64_t sum = 0;
    for (uint64_t i = 0; i < n; ++i) {
        uint64_t w;
        std::cin >> w;

        sum = (sum + w) % MOD;
    }

    calculate_factorials(n);
    std::cout << (sum * ((stirling_number(n, k) + ((n - 1) * stirling_number(n - 1, k)) % MOD) % MOD)) % MOD;

    return 0;
}