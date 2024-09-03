#include <iostream>
#include <stdio.h>
#include <vector>

int main()
{
    int n, m;
    scanf("%d %d", &n, &m);

    std::vector<int> a (n + 1, 0);

    for (int i = 1; i <= n; ++i) {
        scanf("%d", &a[i]);
    }

    std::vector<int> new_v (n + 1, 0);
    std::vector<std::vector<int>> old_v (n + 1, std::vector<int> (m + 1, 0));

    for (int i = 2; i <= n; ++i) {
        for (int j = 1; j <= i - 1; ++j) {
            new_v[i] += std::abs(a[i] - a[j]);
        }
    }

    std::vector<std::vector<int>> lens (n + 1, std::vector<int> (n + 1, 0));

    for (int i = 2; i <= n; ++i) {
        for (int j = 1; j <= n - 1; ++j) {
            int sum = 0;

            for (int t = j + 1; t <= i - 1; ++t) {
                sum += std::min(std::abs(a[i] - a[t]), std::abs(a[t] - a[j]));
            }

            lens[i][j] = sum;
        }
    }

    for (int k = 2; k <= m; ++k) {
        std::vector<int> lst = new_v;

        for (int i = 1; i <= n; ++i) {
            new_v[i] = 2147483647 / 2;
        }

        for (int i = 2; i <= n; ++i) {
            for (int j = 1; j <= i - 1; ++j) {
                if (new_v[i] > lens[i][j] + lst[j]) {
                    old_v[i][k] = j;
                    new_v[i] = lens[i][j] + lst[j];
                }
            }
        }
    }

    for (int i = 1; i <= n - 1; ++i) {
        for (int j = i + 1; j <= n; ++j) {
            new_v[i] += std::abs(a[i] - a[j]);
        }
    }

    int res = 2147483647 / 2, ci = 0;

    for (int i = 1; i <= n; ++i) {
        if (res > new_v[i]) {
            res = new_v[i];
            ci = i;
        }
    }

    printf("%d\n", res);

    std::vector<int> ans (m + 1, 0);

    int x = ci;

    for (int i = m; i >= 1; --i) {
        ans[i] = a[x];
        x = old_v[x][i];
    }

    for (int i = 1; i <= m; ++i) {
        printf("%d ", ans[i]);
    }

    return 0;
}
