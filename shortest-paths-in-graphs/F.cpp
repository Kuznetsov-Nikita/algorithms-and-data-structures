#include <iostream>
#include <set>
#include <vector>

const long long int inf = 1000000000000;

int main() {
    long long int n, m;
    std::cin >> n >> m;

    long long int start, finish;
    std::cin >> start >> finish;
    --start;
    --finish;

    std::vector<std::vector<std::pair<long long int, long long int>>> graph (n, std::vector<std::pair<long long int, long long int>> ());

    for (long long int i = 0; i < m; ++i) {
        long long int b, e, w;
        std::cin >> b >> e >> w;

        graph[b - 1].push_back(std::make_pair(e - 1, w));
        graph[e - 1].push_back(std::make_pair(b - 1, w));
    }

    std::vector<long long int> used (n, 0);
    std::vector<long long int> dist (n, inf);
    dist[start] = 0;

    std::set<std::pair<long long int, long long int>> min_v;

    for (long long int i = 0; i < n; ++i) {
        min_v.insert(std::make_pair(dist[i], i));
    }

    bool has_path = true;

    while (used[finish] == 0) {
        std::pair<long long int, long long int> v = *min_v.begin();

        if (v.first == inf) {
            has_path = false;
            break;
        }

        min_v.erase(min_v.begin());

        for (long long int i = 0; i < graph[v.second].size(); ++i) {
            if (dist[v.second] + graph[v.second][i].second < dist[graph[v.second][i].first]) {
                min_v.erase(std::make_pair(dist[graph[v.second][i].first], graph[v.second][i].first));
                dist[graph[v.second][i].first] = dist[v.second] + graph[v.second][i].second;
                min_v.insert(std::make_pair(dist[graph[v.second][i].first], graph[v.second][i].first));
            }
        }

        used[v.second] = 1;
    }

    if (has_path) {
        std::cout << dist[finish];
    } else {
        std::cout << -1;
    }

    return 0;
}
