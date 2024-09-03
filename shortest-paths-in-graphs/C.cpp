#include <iostream>
#include <vector>

const int inf = 1000000000;

void floid(const std::vector<std::vector<int>>& graph, std::vector<std::vector<int>>& paths_len, int n) {
    for (int k = 0; k < n; ++k) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                paths_len[i][j] = std::min(paths_len[i][j], paths_len[i][k] + paths_len[k][j]);
            }
        }
    }
}

int main() {
    int n;
    std::cin >> n;

    std::vector<std::vector<int>> graph (n, std::vector<int> (n, 0));
    std::vector<std::vector<int>> paths_len (n, std::vector<int> (n, 0));

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            std::cin >> graph[i][j];

            if (graph[i][j] == 0) {
                paths_len[i][j] = inf;
            } else {
                paths_len[i][j] = graph[i][j];
            }
        }
    }

    floid(graph, paths_len, n);

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (i == j) {
                std::cout << 0 << ' ';
            } else {
                std::cout << paths_len[i][j] << ' ';
            }
        }
        std::cout << '\n';
    }

    return 0;
}
