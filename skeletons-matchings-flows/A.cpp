#include <iostream>
#include <set>
#include <vector>

const int inf = 100001;

long long int prime_algorithm(const std::vector<std::vector<std::pair<int, int>>>& graph, int n) {
    std::vector<int> min_edges (n, inf);
    min_edges[0] = 0;

    std::vector<int> min_edges_ends (n, -1);

    std::set<std::pair<int, int>> queue;
    queue.insert(std::make_pair(0, 0));

    std::vector<bool> used (n, false);

    long long int ans = 0;

    for (int i = 0; i < n; ++i) {
        std::pair<int, int> v = *(queue.begin());
        queue.erase(queue.begin());

        if (used[v.second]) {
            continue;
        }
        used[v.second] = true;

        if (min_edges_ends[v.second] != -1) {
            ans += v.first;
        }

        for (int j = 0; j < graph[v.second].size(); ++j) {
            if (!used[graph[v.second][j].first] && graph[v.second][j].second < min_edges[graph[v.second][j].first]) {
                queue.erase(std::make_pair(min_edges[graph[v.second][j].first], graph[v.second][j].first));
                min_edges[graph[v.second][j].first] = graph[v.second][j].second;
                min_edges_ends[graph[v.second][j].first] = v.second;
                queue.insert(std::make_pair(min_edges[graph[v.second][j].first], graph[v.second][j].first));
            }
        }
    }

    return ans;
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);

    std::vector<std::vector<std::pair<int, int>>> graph (n, std::vector<std::pair<int, int>> ());

    for (int i = 0; i < m; ++i) {
        int b, e, w;
        scanf("%d %d %d", &b, &e, &w);

        graph[b - 1].push_back(std::make_pair(e - 1, w));
        graph[e - 1].push_back(std::make_pair(b - 1, w));
    }

    printf("%lld", prime_algorithm(graph, n));

    return 0;
}