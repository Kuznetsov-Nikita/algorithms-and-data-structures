#include <iostream>
#include <vector>

void find_euler_cicle(std::vector<std::vector<int>>& graph, std::vector<int>& ans, int n, int planet) {
    for (int i = 0; i < n; ++i) {
        if (graph[planet][i] == 1) {
            graph[planet][i] = 0;
            find_euler_cicle(graph, ans, n, i);
        }
    }

    ans.push_back(planet + 1);
}

int main() {
    int n, a;
    std::cin >> n >> a;

    std::vector<std::vector<int>> graph (n, std::vector<int> (n, 0));

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            std::cin >> graph[i][j];

            if (i == j) {
                graph[i][j] = 0;
            } else {
                graph[i][j] = 1 - graph[i][j];
            }
        }
    }

    std::vector<int> ans;
    find_euler_cicle(graph, ans, n, a - 1);

    for (int i = ans.size() - 1; i > 0; --i) {
        std::cout << ans[i] << ' ' << ans[i - 1] << '\n';
    }

    return 0;
}
