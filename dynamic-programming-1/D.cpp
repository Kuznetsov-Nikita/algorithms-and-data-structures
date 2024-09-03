#include <iostream>

long long int binomial(int x, int n, int k) {
    long long int ans = 0;
    double tmp = 1.0;

    for (int i = 1; i <= k; ++i) {
        tmp *= (float)x + 1 - i;
        tmp /= (float)i;
        ans += tmp;

        if (ans > n) {
            break;
        }
    }

    return ans;
}

int main() {
    int n, k;
    std::cin >> n >> k;
    n -= 1;

    int upper = n, lower = 0, mid = (upper - lower) / 2;

    while (upper - lower > 1) {
        mid = lower + (upper - lower) / 2;

        if (binomial(mid, n, k) < n) {
            lower = mid;
        } else {
            upper = mid;
        }
    }

    if (k == 0) {
        if (n == 0) {
            std::cout << 0;
        } else {
            std::cout << -1;
        }
    } else {
        std::cout << lower + 1;
    }

    return 0;
}
