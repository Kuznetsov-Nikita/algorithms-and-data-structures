#include <iostream>
#include <vector>
 
const int inf = 1000000000;
 
int main() {
    int n;
    std::cin >> n;
 
    std::vector<std::vector<int>> graph (n, std::vector<int> (n, 0));
 
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            std::cin >> graph[i][j];
        }
    }
 
    std::vector<std::vector<int>> dp (n, std::vector<int> ((1 << n), inf));
    std::vector<std::vector<std::pair<int, int>>> prev (n, std::vector<std::pair<int, int>> ((1 << n), std::make_pair(-1, -1)));
    dp[0][0] = 0;
 
    for (int i = 0; i < n; ++i) {
            dp[i][(1 << i)] = 0;
    }
 
    for (int mask = 1; mask < (1 << n); ++mask) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if ((mask >> j) & 1) {
                    continue;
                }
 
                int new_mask = mask | (1 << j);
                dp[j][new_mask] = std::min(dp[j][new_mask], dp[i][mask] + graph[i][j]);
 
                if (dp[j][new_mask] >= dp[i][mask] + graph[i][j]) {
                    prev[j][new_mask].first = i;
                    prev[j][new_mask].second = mask;
                }
            }
        }
    }
 
    int ans = inf;
    int prev_i, prev_j = (1 << n) - 1;;
    for (int i = 0; i < n; ++i) {
        if (dp[i][(1 << n) - 1] < ans) {
            ans = dp[i][(1 << n) - 1];
            prev_i = i;
        }
    }
 
    std::cout << ans << '\n';
 
    while (prev_i != -1 && prev_j != -1) {
        std::cout << prev_i + 1 << " ";
        int t = prev_i;
        prev_i = prev[prev_i][prev_j].first;
        prev_j = prev[t][prev_j].second;
    }
 
    return 0;
}