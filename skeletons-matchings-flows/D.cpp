#include <iostream>
#include <vector>

bool augment(const std::vector<std::vector<int>>& graph, std::vector<bool>& used, std::vector<int>& match, int v) {
    if (used[v]) {
        return false;
    }

    used[v] = true;

    for (int i = 0; i < graph[v].size(); ++i) {
        if (match[graph[v][i]] == -1 || augment(graph, used, match, match[graph[v][i]])) {
            match[graph[v][i]] = v;
            return true;
        }
    }

    return false;
}

int solve(const std::vector<std::vector<int>>& graph, int n, int m, int a, int b, int empty_cells) {
    std::vector<bool> used (n * m, false);
    std::vector<int> match (n * m, -1);

    for (int v = 0; v < n * m; ++v) {
        if (augment(graph, used, match, v)) {
            used = std::vector<bool> (n * m, false);
        }
    }

    int cnt = 0;
    for (int i = 0; i < n * m; ++i) {
        if (match[i] != -1) {
            ++cnt;
        }
    }

    return cnt * a + (empty_cells - 2 * cnt) * b;;
}

int main() {
    int n, m, a, b;
    scanf("%d %d %d %d\n", &n, &m, &a, &b);

    std::vector<std::vector<char>> bridge (n, std::vector<char> (m, '\0'));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m - 1; ++j) {
            scanf("%c", &bridge[i][j]);
        }
        if ( i != n - 1) {
            scanf("%c\n", &bridge[i][m - 1]);
        } else {
            scanf("%c", &bridge[i][m - 1]);
        }
    }

    std::vector<std::vector<int>> graph (n * m, std::vector<int> ());

    int empty_cells = 0;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (bridge[i][j] == '*') {
                ++empty_cells;

                if ((i + j) % 2 == 0) {
                    if (i != 0 && bridge[i - 1][j] == '*') {
                        graph[i * m + j].push_back(i * m + j - m);
                    }
                    if (j != 0 && bridge[i][j - 1] == '*') {
                        graph[i * m + j].push_back(i * m + j - 1);
                    }
                    if (i < n - 1 && bridge[i + 1][j] == '*') {
                        graph[i * m + j].push_back(i * m + j + m);
                    }
                    if (j < m - 1 && bridge[i][j + 1] == '*') {
                        graph[i * m + j].push_back(i * m + j + 1);
                    }
                }
            }
        }
    }

    if (a >= 2 * b) {
        printf("%d", empty_cells * b);
    } else {
        printf("%d", solve(graph, n, m, a, b, empty_cells));
    }

    return 0;
}