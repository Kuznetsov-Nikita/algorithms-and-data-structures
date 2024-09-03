#include <iostream>
#include <vector>

void dfs(std::vector<std::vector<int>>& graph, std::vector<int>& used, std::vector<int>& comp, int cur_comp_num, int v) {
    used[v] = 1;
    comp[v] = cur_comp_num;

    for (int i = 0; i < graph[v].size(); ++i) {
        if (used[graph[v][i]] == 0) {
            dfs(graph, used, comp, cur_comp_num, graph[v][i]);
        }
    }
}

int main() {
    int n, m;
    std::cin >> n >> m;

    std::vector<std::vector<int>> graph (n + 1, std::vector<int> ());

    for (int i = 0; i < m; ++i) {
        int v1, v2;
        std::cin >> v1 >> v2;

        graph[v1].push_back(v2);
        graph[v2].push_back(v1);
    }

    std::vector<int> used (n + 1, 0);
    std::vector<int> comp (n + 1, 0);

    int cur_comp_num = 0;

    for (int i = 1; i < n + 1; ++i) {
        if (used[i] == 0) {
            ++cur_comp_num;
            dfs(graph, used, comp, cur_comp_num, i);
        }
    }

    std::cout << cur_comp_num << '\n';
    for (int i = 1; i < n + 1; ++i) {
        std::cout << comp[i] << ' ';
    }

    return 0;
}
