#include <stdio.h>
#include <vector>

int main()
{
    int n, m;
    scanf("%d %d", &n, &m);

    std::vector<int> a(n + 1, 0), b(m + 1, 0);

    for (int i = 1; i <= n; ++i) {
        scanf("%d", &a[i]);
    }
    for (int i = 1; i <= m; ++i) {
        scanf("%d", &b[i]);
    }

    std::vector<std::vector<int>> dp(n + 1, std::vector<int> (m + 1, 0));

    for (int i = 1; i <= n; ++i) {
        int best = 0;

        for (int j = 1; j <= m; ++j) {
            dp[i][j] = dp[i - 1][j];

            if (a[i] == b[j] && dp[i - 1][j] < best + 1) {
                dp[i][j] = best + 1;
            }
            if (a[i] > b[j] && dp[i - 1][j] > best) {
                best = dp[i - 1][j];
            }
        }
    }

    int ans = 0;
    for (int i = 1; i <= m; ++i) {
        if (dp[n][i] > ans) {
            ans = dp[n][i];
        }
    }

    printf("%d", ans);

    return 0;
}

