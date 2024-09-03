#include <cstring>
#include <iostream>
#include <string>
#include <vector>
#include <map>

struct node {
    std::map<char, int> to, move;
    int par, link, good_link;
    std::vector<int> word_num;
    char c;
    bool term;

    node() {
        term = false;
        link = -1;
        good_link = -1;
    }

    node(int p, char c): node() {
        par = p;
        this->c = c;
    }
};

void add(std::vector<node>& trie, const std::string& s, int num) {
    int v = 0;

    for (int i = 0; i < s.size(); ++i) {
        if (!trie[v].to.count(s[i] - 'a')) {
            trie.push_back(node(v, s[i] - 'a'));
            trie[v].to[s[i] - 'a'] = int(trie.size()) - 1;
        }
        v = trie[v].to[s[i] - 'a'];
    }

    trie[v].term = true;
    trie[v].word_num.push_back(num);
}

int get_move(std::vector<node>& trie, int v, char c);

int get_link(std::vector<node>& trie, int v) {
    if (trie[v].link == -1) {
        if (v == 0 || trie[v].par == 0) {
            trie[v].link = 0;
        } else {
            trie[v].link = get_move(trie, get_link(trie, trie[v].par), trie[v].c);
        }
    }

    return trie[v].link;
}

int get_move(std::vector<node>& trie, int v, char c) {
    if (!trie[v].move.count(c)) {
        if (trie[v].to.count(c)) {
            trie[v].move[c] = trie[v].to[c];
        } else {
            if (v == 0) {
                trie[v].move[c] = 0;
            } else {
                trie[v].move[c] = get_move(trie, get_link(trie, v), c);
            }
        }
    }

    return trie[v].move[c];
}

int get_good_link(std::vector<node>& trie, int v) {
    if (trie[v].good_link == -1) {
        int u = get_link(trie, v);

        if (u == 0) {
            trie[v].good_link = 0;
        } else {
            trie[v].good_link = (trie[u].term) ? u : get_good_link(trie, u);
        }
    }

    return trie[v].good_link;
}

void check(std::vector<node>& trie, const std::vector<std::string>& dict, std::vector<std::vector<int>>& ans, int v, int i) {
    for (int u = v; u != 0; u = get_good_link(trie, u)) {
        if (trie[u].term) {
            for (int j = 0; j < trie[u].word_num.size(); ++j) {
                ans[trie[u].word_num[j]].push_back(i - dict[trie[u].word_num[j]].size() + 1);
            }
        }
    }
}

void find_all_pos(std::vector<node>& trie, const std::vector<std::string>& dict, std::vector<std::vector<int>>& ans, const std::string& s) {
    int v = 0;

    for (int i = 0; i < s.size(); ++i) {
        v = get_move(trie, v, s[i] - 'a');
        check(trie, dict, ans, v, i + 1);
    }
}

int main() {
    std::string s;
    std::cin >> s;

    int n;
    std::cin >> n;

    std::vector<std::string> dict (n, "");
    std::vector<node> trie;
    trie.push_back(node(0, '#'));

    for (int i = 0; i < n; ++i) {
        std::cin >> dict[i];
        add(trie, dict[i], i);
    }

    std::vector<std::vector<int>> ans (n, std::vector<int> ());

    find_all_pos(trie, dict, ans, s);

    for (int i = 0; i < n; ++i) {
        std::cout << ans[i].size() << ' ';
        for (int j = 0; j < ans[i].size(); ++j) {
            std::cout << ans[i][j] << ' ';
        }
        std::cout << '\n';
    }

    return 0;
}
