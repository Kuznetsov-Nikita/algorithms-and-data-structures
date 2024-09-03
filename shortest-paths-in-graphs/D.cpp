#include <stdio.h>
#include <vector>

const long long int plus_inf = 9223372036854775807;
const long long int minus_inf = -9223372036854775807;

void dfs(const std::vector<std::vector<std::pair<int, long long int>>>& graph, std::vector<int>& used, std::vector<long long int>& dp, int v) {
    used[v] = 1;
    dp[v] = minus_inf;

    for (int i = 0; i < graph[v].size(); ++i) {
        if (used[graph[v][i].first] == 0) {
            dfs(graph, used, dp, graph[v][i].first);
        }
    }
}

void ford_bellman(const std::vector<std::vector<std::pair<int, long long int>>>& graph, std::vector<long long int>& dp, int n, int s) {
    dp[s] = 0;

    for (int k = 0; k < n; ++k) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < graph[i].size(); ++j) {
                if (dp[i] < plus_inf && dp[graph[i][j].first] > dp[i] + graph[i][j].second) {
                    dp[graph[i][j].first] = dp[i] + graph[i][j].second;
                }
            }
        }
    }

    std::vector<int> used (n, 0);

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < graph[i].size(); ++j) {
            if (dp[i] < plus_inf && dp[graph[i][j].first] > dp[i] + graph[i][j].second && used[graph[i][j].first] == 0) {
                dfs(graph, used, dp, graph[i][j].first);
            }
        }
    }
}

int main() {
    int n, m, s;
    scanf("%d %d %d", &n, &m, &s);

    std::vector<std::vector<std::pair<int, long long int>>> graph (n, std::vector<std::pair<int, long long int>> ());

    for (int i = 0; i < m; ++i) {
        int v1, v2;
        long long int weight;
        scanf("%d %d %lld", &v1, &v2, &weight);

        graph[v1 - 1].push_back(std::make_pair(v2 - 1, weight));
    }

    std::vector<long long int> dp (n, plus_inf);

    ford_bellman(graph, dp, n, s - 1);

    for (int i = 0; i < n; ++i) {
        if (dp[i] == plus_inf) {
            printf("*\n");
        } else if (dp[i] == minus_inf) {
            printf("-\n");
        } else {
            printf("%lld\n", dp[i]);
        }
    }

    return 0;
}
