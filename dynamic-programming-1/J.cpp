#include <stdio.h>
#include <vector>

int main()
{
    int s, n;
    scanf("%d %d", &s, &n);

    std::vector<int> ignots;

    for (int i = 0; i < n; ++i) {
        int w;
        scanf("%d", &w);
        ignots.push_back(w);
    }

    std::vector<std::vector<int>> dp (n + 1, std::vector<int> (s + 1, 0));

    for (int i = 0; i < n; ++i) {
        for (int w = 0; w <= s; ++w) {
            dp[i + 1][w] = std::max(dp[i + 1][w], dp[i][w]);

            if (w + ignots[i] <= s) {
                dp[i + 1][w + ignots[i]] = std::max(dp[i + 1][w + ignots[i]], dp[i][w] + ignots[i]);
            }
        }
    }

    printf("%d", dp[n][s]);

    return 0;
}
