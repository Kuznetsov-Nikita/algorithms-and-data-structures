#include <iostream>
#include <vector>

enum Colors {
    WHITE = 0,
    GRAY = 1,
    BLACK = 2
};

void dfs(std::vector<std::vector<int>>& graph, std::vector<int>& color, std::vector<int>& par, bool& has_cycle, int& begin, int& end, int v) {
    color[v] = GRAY;

    for (int i = 0; i < graph[v].size(); ++i) {
        if (color[graph[v][i]] == WHITE) {
            par[graph[v][i]] = v;
            dfs(graph, color, par, has_cycle, begin ,end, graph[v][i]);

            if (has_cycle) {
                return;
            }
        } else if (color[graph[v][i]] == GRAY) {
            has_cycle = true;
            begin = graph[v][i];
            end = v;
        }
    }

    color[v] = BLACK;
}

int main() {
    int n, m;
    std::cin >> n >> m;

    std::vector<std::vector<int>> graph (n + 1, std::vector<int> ());

    for (int i = 0; i < m; ++i) {
        int v1, v2;
        std::cin >> v1 >> v2;

        graph[v1].push_back(v2);
    }

    std::vector<int> color (n + 1, WHITE);
    std::vector<int> par(n + 1, -1);
    bool has_cycle = false;
    int begin = -1, end;

    for (int i = 1; i < n + 1; ++i) {
        if (!has_cycle && color[i] == WHITE) {
            dfs(graph, color, par, has_cycle, begin, end, i);
        } else if (has_cycle) {
            break;
        }
    }

    if (!has_cycle) {
        std::cout << "NO";
    } else {
        std::cout << "YES\n";

        std::vector<int> path;

        for (int v = end; v != begin; v = par[v]) {
            path.push_back(v);
        }
        path.push_back(begin);

        for (int i = path.size() - 1; i >= 0; --i) {
            std::cout << path[i] << ' ';
        }
    }

    return 0;
}
