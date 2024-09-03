#include <iostream>
#include <string>
#include <vector>

int main() {
    int n;
    std::cin >> n;

    std::vector<std::string> table (n, "");

    for (int i = 0; i < n; ++i) {
        std::cin >> table[i];
    }

    std::vector<int> dp (1 << 18, 0);

    for (int i = 0; i < n; ++i) {
        for (int mask = 0; mask < 1 << 18; ++mask) {
            if (dp[mask] != 0) {
                int tmp = mask + 1;

                for (int k = n - 1; k > i; --k) {
                    if (tmp >= (1 << k)) {
                        tmp -= (1 << k);
                    }
                }

                if (tmp >= (1 << i)) {
                    continue;
                } else {
                    tmp = mask + 1;

                    for (int k = n - 1; k >= 0; --k) {
                        if (tmp >= (1 << k)) {
                            tmp -= (1 << k);
                        } else {
                            if (table[i][k] == 'Y') {
                                dp[mask + (1 << k) + (1 << i)] = dp[mask] + 1;
                            }
                        }
                    }
                }
            }
        }

        for (int j = 0; j < n; ++j) {
            if (table[i][j] == 'Y') {
                dp[(1 << j) + (1 << i) - 1] = 1;
            }
        }
    }

    int max = 0;

    for (int mask = 0; mask < (1 << 18); ++mask) {
        max = std::max(max, dp[mask]);
    }

    std::cout << max * 2;

    return 0;
}
