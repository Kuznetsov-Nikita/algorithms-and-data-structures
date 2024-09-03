#include <iostream>
#include <set>
#include <vector>

void dfs_1(std::vector<std::vector<int>>& graph, std::vector<int>& used, std::vector<int>& order, int v) {
    used[v] = 1;

    for (int i = 0; i < graph[v].size(); ++i) {
        if (used[graph[v][i]] == 0) {
            dfs_1(graph, used, order, graph[v][i]);
        }
    }

    order.push_back(v);
}

void dfs_2(std::vector<std::vector<int>>& graph, std::vector<int>& used, std::vector<int>& comp, int v, int comp_cnt) {
    used[v] = 1;
    comp[v] = comp_cnt;

    for (int i = 0; i < graph[v].size(); ++i) {
        if (used[graph[v][i]] == 0) {
            dfs_2(graph, used, comp, graph[v][i], comp_cnt);
        }
    }
}

int main() {
    int n, m;
    std::cin >> n >> m;

    std::vector<std::vector<int>> graph (n + 1, std::vector<int> ());
    std::vector<std::vector<int>> graph_t (n + 1, std::vector<int> ());

    for (int i = 1; i < m + 1; ++i) {
        int v1, v2;
        std::cin >> v1 >> v2;

        graph[v1].push_back(v2);
        graph_t[v2].push_back(v1);
    }

    std::vector<int> used (n + 1, 0);
    std::vector<int> order;
    std::vector<int> comp (n + 1, 0);
    int comp_cnt = 0;

    for (int i = 1; i < n + 1; ++i) {
        if (used[i] == 0) {
            dfs_1(graph, used, order, i);
        }
    }

    used = std::vector<int> (n + 1, 0);

    for (int i = 1; i < n + 1; ++i) {
        if (used[order[n - i]] == 0) {
            ++comp_cnt;
            dfs_2(graph_t, used, comp, order[n - i], comp_cnt);
        }
    }

    std::vector<std::set<int>> matrix (comp_cnt + 1, std::set<int> ());

    int cnt = 0;

    for (int i = 1; i < n + 1; ++i) {
        for (int j = 0; j < graph[i].size(); ++j) {
            if (comp[i] != comp[graph[i][j]]) {
                if (matrix[comp[i]].find(comp[graph[i][j]]) == matrix[comp[i]].end()) {
                    matrix[comp[i]].insert(comp[graph[i][j]]);
                    ++cnt;
                }
                if (matrix[comp[graph[i][j]]].find(comp[i]) == matrix[comp[graph[i][j]]].end()) {
                    matrix[comp[graph[i][j]]].insert(comp[i]);
                    ++cnt;
                }
            }
        }
    }

    std::cout << cnt / 2;

    return 0;
}
