#include <cstring>
#include <iostream>
#include <queue>
#include <string>
#include <vector>

struct node {
    int to[2];
    bool term;
    int link;

    node() {
        memset(to, -1, sizeof(to));
        term = false;
        link = -1;
    }
};

void add(std::vector<node>& trie, const std::string& s) {
    int v = 0;

    for (int i = 0; i < s.size(); ++i) {
        if (trie[v].to[s[i] - '0'] == -1) {
            trie.push_back(node());
            trie[v].to[s[i] - '0'] = int(trie.size()) - 1;
        }
        v = trie[v].to[s[i] - '0'];
    }

    trie[v].term = true;
}

void aho_corasick(std::vector<node>& trie) {
    trie[0].link = 0;

    for (int c = 0; c < 2; ++c) {
        if (trie[0].to[c] != -1) {
            continue;
        }
        trie[0].to[c] = 0;
    }

    std::queue<int> q;
    q.push(0);

    while (!q.empty()) {
        int v = q.front();
        q.pop();

        for (int c = 0; c < 2; ++c) {
            int u = trie[v].to[c];

            if (trie[u].link != -1) {
                continue;
            }

            trie[u].link = (v == 0 ? 0 : trie[trie[v].link].to[c]);

            for (int d = 0; d < 2; ++d) {
                if (trie[u].to[d] != -1) {
                    continue;
                }
                trie[u].to[d] = trie[trie[u].link].to[d];
            }

            q.push(u);
        }
    }
}

bool is_bad(std::vector<node>& trie, std::vector<bool>& used, int v) {
    used[v] = true;

    if (trie[v].term) {
        return true;
    }

    if (v == 0) {
        return false;
    }

    bool flag = is_bad(trie, used, trie[v].link);
    trie[v].term = flag;
    return flag;
}

void dfs(const std::vector<node>& trie, std::vector<int>& colors, int v, bool& has_cycle) {
    colors[v] = 1;

    for (int i = 0; i < 2; ++i) {
        if (!trie[trie[v].to[i]].term) {
            if (colors[trie[v].to[i]] == 0) {
                dfs(trie, colors, trie[v].to[i], has_cycle);

                if (has_cycle) {
                    return;
                }
            } else {
                if (colors[trie[v].to[i]] == 1) {
                    has_cycle = true;
                }
            }
        }
    }

    colors[v] = 2;
}

int main() {
    int n;
    std::cin >> n;

    std::vector<node> trie;
    trie.push_back(node());

    for (int i = 0; i < n; ++i) {
        std::string s;
        std::cin >> s;

        add(trie, s);
    }

    aho_corasick(trie);

    std::vector<bool> used (trie.size(), false);

    for (int v = 0; v < trie.size(); ++v) {
        if (!used[v]) {
            is_bad(trie, used, v);
        }
    }

    std::vector<int> colors (trie.size(), 0);
    bool has_cycle = false;
    dfs(trie, colors, 0, has_cycle);

    if (has_cycle) {
        std::cout << "TAK";
    } else {
        std::cout << "NIE";
    }

    return 0;
}
