#include <algorithm>
#include <iostream>
#include <vector>

void dfs(std::vector<std::vector<std::pair<int, int>>>& graph, std::vector<int>& used, std::vector<int>& tin, std::vector<int>& red, std::vector<int>& bridges, int& timer, int v, int p = -1) {
    used[v] = 1;
    tin[v] = timer;
    red[v] = timer;
    ++timer;

    for (int i = 0; i < graph[v].size(); ++i) {
        if (graph[v][i].first == p) {
            continue;
        }

        if (used[graph[v][i].first] == 0) {
            dfs(graph, used, tin, red, bridges, timer, graph[v][i].first, v);
            red[v] = std::min(red[v], red[graph[v][i].first]);

            if (red[graph[v][i].first] > tin[v]) {
                bridges.push_back(graph[v][i].second);
            }
        } else {
            red[v] = std::min(red[v], tin[graph[v][i].first]);
        }
    }
}

int main() {
    int n, m;
    std::cin >> n >> m;

    std::vector<std::vector<std::pair<int, int>>> graph (n + 1, std::vector<std::pair<int, int>> ());

    for (int i = 1; i < m + 1; ++i) {
        int v1, v2;
        std::cin >> v1 >> v2;

        graph[v1].push_back(std::make_pair(v2, i));
        graph[v2].push_back(std::make_pair(v1, i));
    }

    std::vector<int> used (n + 1, 0);
    std::vector<int> tin (n + 1, 0);
    std::vector<int> red (n + 1, 1000000000);
    std::vector<int> bridges;
    int timer = 0;

    for (int i = 1; i < n + 1; ++i) {
        if (used[i] == 0) {
            dfs(graph, used, tin, red, bridges, timer, i);
        }
    }

    std::cout << bridges.size() << '\n';

    std::sort(bridges.begin(), bridges.end());

    for (int i = 0; i < bridges.size(); ++i) {
        std::cout << bridges[i] << ' ';
    }

    return 0;
}
