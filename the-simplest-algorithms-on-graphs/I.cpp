#include <algorithm>
#include <iostream>
#include <set>
#include <vector>
 
void dfs(std::vector<std::vector<int>>& graph, std::vector<int>& used, std::vector<int>& tin, std::vector<int>& red, std::set<int>& cutpoints, int& timer, int v, int p = -1) {
    used[v] = 1;
    tin[v] = timer;
    red[v] = timer;
    ++timer;
 
    int child_cnt = 0;
 
    for (int i = 0; i < graph[v].size(); ++i) {
        if (graph[v][i] == p) {
            continue;
        }
 
        if (used[graph[v][i]] == 0) {
            dfs(graph, used, tin, red, cutpoints, timer, graph[v][i], v);
            red[v] = std::min(red[v], red[graph[v][i]]);
 
            if (red[graph[v][i]] >= tin[v] && p != -1) {
                if (cutpoints.find(v) == cutpoints.end()) {
                    cutpoints.insert(v);
                }
            }
            ++child_cnt;
        } else {
            red[v] = std::min(red[v], tin[graph[v][i]]);
        }
    }
 
    if (p == -1 && child_cnt > 1) {
        if (cutpoints.find(v) == cutpoints.end()) {
            cutpoints.insert(v);
        }
    }
}
 
int main() {
    int n, m;
    std::cin >> n >> m;
 
    std::vector<std::vector<int>> graph (n + 1, std::vector<int> ());
 
    for (int i = 1; i < m + 1; ++i) {
        int v1, v2;
        std::cin >> v1 >> v2;
 
        graph[v1].push_back(v2);
        graph[v2].push_back(v1);
    }
 
    std::vector<int> used (n + 1, 0);
    std::vector<int> tin (n + 1, 0);
    std::vector<int> red (n + 1, 1000000000);
    std::set<int> cutpoints;
    int timer = 0;
 
    //dfs(graph, used, tin, red, cutpoints, timer, 1);
 
    for (int i = 1; i < n + 1; ++i) {
        if (used[i] == 0) {
            dfs(graph, used, tin, red, cutpoints, timer, i);
        }
    }
 
    std::cout << cutpoints.size() << '\n';
 
    //std::sort(cutpoints.begin(), cutpoints.end());
 
    for (std::set<int>::iterator it = cutpoints.begin(); it != cutpoints.end(); ++it) {
        std::cout << *it << '\n';
    }
 
    return 0;
}