#include <stdio.h>
#include <vector>

int main()
{
    int n;
    std::vector<int> first_seq;
    scanf("%d", &n);

    for (int i = 0; i < n; ++i) {
        int x;
        scanf("%d", &x);
        first_seq.push_back(x);
    }

    int m;
    std::vector<int> second_seq;
    scanf("%d", &m);

    for (int i = 0; i < m; ++i) {
        int x;
        scanf("%d", &x);
        second_seq.push_back(x);
    }

    std::vector<std::vector<int>> dp(n + 1, std::vector<int> (m + 1, 0));

    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            if  (first_seq[i - 1] != second_seq[j - 1]) {
                dp[i][j] = std::max(dp[i - 1][j], dp[i][j - 1]);
            } else {
                dp[i][j] = std::max(1 + dp[i - 1][j - 1], std::max(dp[i - 1][j], dp[i][j - 1]));
            }
        }
    }

    printf("%d", dp[n][m]);

    return 0;
}
