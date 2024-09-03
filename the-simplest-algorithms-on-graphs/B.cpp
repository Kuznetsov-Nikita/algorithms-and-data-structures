#include <iostream>
#include <vector>

void dfs(std::vector<std::vector<int>>& graph, std::vector<int>& used, std::vector<int>& tin, std::vector<int>& tout, int& timer, int v) {
    used[v] = 1;
    tin[v] = timer;
    ++timer;

    for (int i = 0; i < graph[v].size(); ++i) {
        if (used[graph[v][i]] == 0) {
            dfs(graph, used, tin, tout, timer, graph[v][i]);
        }
    }

    tout[v] = timer;
    ++timer;
}

int main() {
    int n;
    std::cin >> n;

    std::vector<std::vector<int>> graph (n + 1, std::vector<int> ());
    int root;

    for (int i = 1; i < n + 1; ++i) {
        int v;
        std::cin >> v;

        if (v == 0) {
            root = i;
        } else {
            graph[v].push_back(i);
        }
    }

    std::vector<int> used (n + 1, 0);
    std::vector<int> tin (n + 1, 0);
    std::vector<int> tout (n + 1, 0);
    int timer = 0;

    dfs(graph, used, tin, tout, timer, root);

    int m;
    std::cin >> m;

    for (int i = 0; i < m; ++i) {
        int a, b;
        std::cin >> a >> b;

        if (tin[a] < tin[b] && tout[b] < tout[a]) {
            std::cout << "1\n";
        } else {
            std::cout << "0\n";
        }
    }

    return 0;
}
