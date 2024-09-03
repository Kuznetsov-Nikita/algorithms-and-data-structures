#include <iostream>
#include <math.h>
#include <vector>

bool correct(int mask1, int mask2, int m) {
    for (int i = 0; i < m - 1; ++i) {
        if (bool((1 << i) & mask1) == bool((1 << i) & mask2) && bool((1 << i) & mask1) == bool((1 << (i + 1)) & mask1) && bool((1 << i) & mask1) == bool((1 << (i + 1)) & mask2)) {
            return false;
        }
    }

    return true;
}

int main()
{
    int n, m;
    std::cin >> m >> n;

    if (m > n) {
        std::swap(m, n);
    }

    std::vector<std::vector<int>> dp (n, std::vector<int> (std::pow(2, m), 0));

    for (int mask = 0; mask < std::pow(2, m); ++mask) {
        dp[0][mask] = 1;
    }

    for (int i = 0; i < n - 1; ++i) {
        for (int mask1 = 0; mask1 < std::pow(2, m); ++mask1) {
            for (int mask2 = 0; mask2 < std::pow(2, m); ++mask2) {
                if (correct(mask1, mask2, m)) {
                    dp[i + 1][mask2] += dp[i][mask1];
                }
            }
        }
    }

    int ans = 0;

    for (int mask = 0; mask < std::pow(2, m); ++mask) {
        ans += dp[n - 1][mask];
    }

    std::cout << ans;

    return 0;
}
