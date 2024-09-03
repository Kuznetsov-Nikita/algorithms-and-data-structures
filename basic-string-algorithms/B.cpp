#include <iostream>
#include <string>
#include <vector>

void solve(const std::vector<int>& cubes, int n) {
    int l = 0, r = -1;
    std::vector<int> eval_palindromes (n, 0);

    for (int i = 0; i < n; ++i) {
        int k;
        if (i > r) {
            k = 0;
        } else {
            k = std::min(eval_palindromes[l + r - i + 1], r - i + 1);
        }

        while (i + k < n && i - k - 1 >= 0 && cubes[i + k] == cubes[i - k - 1]) {
            ++k;
        }
        eval_palindromes[i] = k;

        if (i + k - 1 > r) {
            l = i - k;
            r = i + k - 1;
        }
    }

    for (int i = n; i >= 0; --i) {
        if (eval_palindromes[i] == i) {
            printf("%d ", n - i);
        }
    }
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);

    std::vector<int> cubes (n, 0);

    for (int i = 0; i < n; ++i) {
        scanf("%d", &cubes[i]);
    }

    solve(cubes, n);

    return 0;
}
