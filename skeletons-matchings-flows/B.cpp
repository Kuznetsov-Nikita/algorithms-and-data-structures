#include <algorithm>
#include <iostream>
#include <vector>

const int inf = 100001;

class DSU {
private:
    int n;
    std::vector<int> parent;
    std::vector<int> size;

public:
    DSU(int n) {
        this->n = n;

        for (int i = 0; i < n; ++i) {
            parent.push_back(-1);
            size.push_back(1);
        }
    }

    int get(int v) {
        if (parent[v] == -1) {
            return v;;
        } else {
            return parent[v] = get(parent[v]);
        }
    }

    void unite(int v1, int v2) {
        v1 = get(v1);
        v2 = get(v2);

        if (v1 == v2) {
            return;
        }

        if (size[v1] < size[v2]) {
            std::swap(v1, v2);
        }

        parent[v2] = v1;
        size[v1] += size[v2];
    }
};

long long int cruscall_algorithm(std::vector<std::pair<int, std::pair<int, int>>>& graph, int n, int m) {
    std::sort(graph.begin(), graph.end());
    DSU dsu (n);
    long long int ans = 0;

    for (int i = 0; i < m; ++i) {
        if (dsu.get(graph[i].second.first) != dsu.get(graph[i].second.second)) {
            ans += graph[i].first;
            dsu.unite(graph[i].second.first, graph[i].second.second);
        }
    }

    return ans;
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);

    std::vector<std::pair<int, std::pair<int, int>>> graph;

    for (int i = 0; i < m; ++i) {
        int b, e, w;
        scanf("%d %d %d", &b, &e, &w);

        graph.push_back(std::make_pair(w, std::make_pair(b - 1, e - 1)));
    }

    printf("%lld", cruscall_algorithm(graph, n, m));

    return 0;
}