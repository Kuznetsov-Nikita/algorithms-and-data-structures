#include <algorithm>
#include <iostream>
#include <cmath>
#include <vector>

void calculate(std::vector<std::pair<int, bool>>& half, int l, int r, const std::vector<int>& x, int& mask, int cur_sum, int c, int m, int num) {
    if (l == r || cur_sum > c) {
        if (cur_sum <= c) {
            half[mask] = std::make_pair(cur_sum, true);
        }
        return;
    }

    mask |= (1 << l >> m * num);
    calculate(half, l + 1, r, x, mask, cur_sum + x[l], c, m, num);
    mask &= ~(1 << l >> m * num);
    calculate(half, l + 1, r, x, mask, cur_sum, c, m, num);
}

int main() {
    int n;
    std::cin >> n;

    std::vector<int> x (n, 0);
    for (int i = 0; i < n; ++i) {
        std::cin >> x[i];
    }

    int c;
    std::cin >> c;

    int m = n / 2;
    std::vector<std::pair<int, bool>> first_half (std::pow(2, m + 1), std::make_pair(c + 1, false));
    std::vector<std::pair<int, bool>> second_half (std::pow(2, m + 1), std::make_pair(c + 1, false));
    int mask = 0;

    calculate(first_half, 0, m, x, mask, 0, c, m, 0);
    calculate(second_half, m, n, x, mask, 0, c, m, 1);

    int cnt = 0;

    std::sort(second_half.begin(), second_half.end());
    for (int i = 0; i < std::pow(2, m + 1); ++i) {
        if (first_half[i].second) {
            cnt += int(std::upper_bound(second_half.begin(), second_half.end(), std::make_pair(c - first_half[i].first, true)) - second_half.begin());
        }
    }

    std::cout << cnt;

    return 0;
}
