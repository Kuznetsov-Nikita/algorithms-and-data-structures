#include <iostream>
#include <vector>

int gcd(int a, int b) {
    while (a != 0 && b != 0) {
        if (a > b) {
            a %= b;
        } else {
            b %= a;
        }
    }

    return a + b;
}

int main() {
    int n;
    std::cin >> n;

    std::vector<int> a (n, 0);

    int cnt_1 = 0;

    for (int i = 0; i < n; ++i) {
        std::cin >> a[i];
        if (a[i] == 1) {
            ++cnt_1;
        }
    }

    if (cnt_1 > 0) {
        std::cout << n - cnt_1;
    } else {
        int min_len = n + 1;
        for (int i = 0; i < n - 1; ++i) {
            int curr_gcd = gcd(a[i], a[i + 1]);

            if (curr_gcd == 1) {
                min_len = 2;
                break;
            }

            for (int j = i + 2; j < n; j++) {
                curr_gcd = gcd(curr_gcd, a[j]);

                if (curr_gcd == 1) {
                    min_len = std::min(min_len, j - i + 1);
                }
            }
        }

        if (min_len == n + 1) {
            std::cout << -1;
        } else {
            std::cout << min_len + n - 2;
        }
    }

    return 0;
}