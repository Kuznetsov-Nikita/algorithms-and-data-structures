#include <iostream>
#include <vector>

int main() {
    int n, m;
    std::cin >> n >> m;

    std::vector<std::vector<int>> matrix (n, std::vector<int> (m, 0));

    for (int i = 0; i < m; ++i) {
        int u, v;
        std::cin >> u >> v;

        matrix[u - 1][i] = 1;
        matrix[v - 1][i] = 1;
    }

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            std::cout << matrix[i][j] << ' ';
        }
        std::cout << '\n';
    }

    return 0;
}
