#include <iostream>
#include <vector>

void dfs_1(const std::vector<std::vector<int>>& graph, std::vector<int>& used, std::vector<int>& order, int v) {
    used[v] = 1;

    for (int i = 0; i < graph[v].size(); ++i) {
        if (used[graph[v][i]] == 0) {
            dfs_1(graph, used, order, graph[v][i]);
        }
    }

    order.push_back(v);
}

void dfs_2(const std::vector<std::vector<int>>& graph, std::vector<int>& used, std::vector<int>& comp, int v, int comp_cnt) {
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

    std::vector<int> lamps_status (n, 0);

    for (int i = 0; i < n; ++i) {
        std::cin >> lamps_status[i];
    }

    std::vector<std::vector<int>> lamps_graph (n, std::vector<int> ());


    for (int i = 0; i < m; ++i) {
        int x;
        std::cin >> x;

        for (int j = 0; j < x; ++j) {
            int lamp;
            std::cin >> lamp;

            lamps_graph[lamp - 1].push_back(i);
        }
    }

    std::vector<std::vector<int>> imp_graph (2 * m, std::vector<int> ());

    for (int i = 0; i < n; ++i) {
        if (lamps_status[i] == 0) {
            imp_graph[lamps_graph[i][0] + m].push_back(lamps_graph[i][1]);
            imp_graph[lamps_graph[i][1] + m].push_back(lamps_graph[i][0]);
            imp_graph[lamps_graph[i][0]].push_back(lamps_graph[i][1] + m);
            imp_graph[lamps_graph[i][1]].push_back(lamps_graph[i][0] + m);
        } else {
            imp_graph[lamps_graph[i][0]].push_back(lamps_graph[i][1]);
            imp_graph[lamps_graph[i][1]].push_back(lamps_graph[i][0]);
            imp_graph[lamps_graph[i][0] + m].push_back(lamps_graph[i][1] + m);
            imp_graph[lamps_graph[i][1] + m].push_back(lamps_graph[i][0] + m);
        }
    }

    std::vector<int> used (2 * m, 0);
    std::vector<int> order;
    std::vector<int> comp (2 * m, -1);

    for (int i = 0; i < 2 * m; ++i) {
        if (used[i] == 0) {
            dfs_1(imp_graph, used, order, i);
        }
    }

    used = std::vector<int> (2 * m, 0);
    int comp_cnt = 0;

    for (int i = 0; i < 2 * m; ++i) {
        if (used[order[2 * m - i - 1]] == 0) {
            ++comp_cnt;
            dfs_2(imp_graph, used, comp, order[2 * m - i - 1], comp_cnt);
        }
    }

    bool flag = true;
    for (int i = 0; i < m; ++i) {
        if (comp[i] == comp[i + m]) {
            flag = false;
            break;
        }
    }

    if (flag) {
        std::cout << "YES";
    } else {
        std::cout << "NO";
    }

    return 0;
}
