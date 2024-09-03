#include <algorithm>
#include <iostream>
#include <queue>
#include <set>
#include <vector>

const long long int inf = 1000000000000000000;

int main() {
    long long int h;
    std::cin >> h;

    int a, b, c;
    std::vector<int> tmp (3, 0);
    std::cin >> tmp[0] >> tmp[1] >> tmp[2];
    std::sort(tmp.begin(), tmp.end());
    a = tmp[0];
    b = tmp[1];
    c = tmp[2];

    if (a == 1) {
        std::cout << h;
    } else {
        std::vector<std::vector<std::pair<int, int>>> graph (a, std::vector<std::pair<int, int>> ());
        std::vector<int> used (a, 0);
        std::queue<int> q;

        q.push(1);
        used[1] = 1;

        while (!q.empty()) {
            int t = q.front();
            q.pop();

            graph[t].push_back(std::make_pair(b, (t + b % a) % a));
            graph[t].push_back(std::make_pair(c, (t + c % a) % a));

            if (used[(t + b % a) % a] == 0) {
                q.push((t + b % a) % a);
                used[(t + b % a) % a] = 1;
            }
            if (used[(t + c % a) % a] == 0) {
                q.push((t + c % a) % a);
                used[(t + c % a) % a] = 1;
            }
        }

        std::vector<long long int> dist (a, inf);
        dist[1] = 0;

        std::set<std::pair<long long int, int>> min_v;
        min_v.insert(std::make_pair(dist[1], 1));

        while (!min_v.empty()) {
            std::pair<long long int, int> v = *min_v.begin();
            min_v.erase(v);

            for (int i = 0; i < graph[v.second].size(); ++i) {
                if (v.first + graph[v.second][i].first < dist[graph[v.second][i].second]) {
                    min_v.erase(std::make_pair(dist[graph[v.second][i].second], graph[v.second][i].second));
                    dist[graph[v.second][i].second] = v.first + graph[v.second][i].first;
                    min_v.insert(std::make_pair(dist[graph[v.second][i].second], graph[v.second][i].second));
                }
            }
        }

        long long int ans = 0;

        for (int i = 0; i < a; ++i) {
            if (dist[i] != inf && dist[i] < h) {
                ans += (h - dist[i] - 1) / a + 1;
            }
        }

        std::cout << ans;
    }

    return 0;
}