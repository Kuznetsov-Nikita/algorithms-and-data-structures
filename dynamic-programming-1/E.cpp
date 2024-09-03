#include <stdio.h>
#include <vector>

int main()
{
    int n;
    scanf("%d", &n);

    std::vector<std::vector<long long int>> dp (n + 1, std::vector<long long int> (n + 1, 0));

    for (int i = 1; i <= n; ++i) {
        dp[i][i] = 1;
    }

    for (int i = 0; i <= n; ++i) {
        for (int j = 0; j <= n; ++j) {
            if (dp[i][j] > 0) {
                for (int k = 2 * j; k <= n - i; ++k) {
                    dp[i + k][k] += dp[i][j];
                }
            }
        }
    }

    long long int ans = 0;
    for (int i = 1; i <= n; i++) {
        ans += dp[n][i];
    }
    printf("%lld", ans);

    return 0;
}
