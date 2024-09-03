#include <algorithm>
#include <iostream>
#include <map>
#include <string>
#include <vector>

struct node {
    long long int left, right, parent, link, leaves;
    std::map<long long int, long long int> to;

    node(long long int left = 0ll, long long int right = 0ll, long long int parent = -1ll): left(left), right(right), parent(parent), link(-1ll), leaves(0ll) {}

    long long int& next(long long int c) {
        if (to.count(c) == 0ll) {
            to[c] = -1ll;
        }
        return to[c];
    }
};

std::pair<long long int, long long int> go(std::vector<node>& suffix_tree, const std::string& s, std::pair<long long int, long long int> ptr, long long int left, long long int right) {
    while (left < right) {
        if (ptr.second == suffix_tree[ptr.first].right - suffix_tree[ptr.first].left) {
            ptr.first = suffix_tree[ptr.first].next(s[left]);
            ptr.second = 0ll;

            if (ptr.first == -1ll) {
                return ptr;
            }
        } else {
            if (s[suffix_tree[ptr.first].left + ptr.second] != s[left]) {
                return std::make_pair(-1ll, -1ll);
            }
            if (right - left < suffix_tree[ptr.first].right - suffix_tree[ptr.first].left - ptr.second) {
                return std::make_pair(ptr.first, ptr.second + right - left);
            }

            left += suffix_tree[ptr.first].right - suffix_tree[ptr.first].left - ptr.second;
            ptr.second = suffix_tree[ptr.first].right - suffix_tree[ptr.first].left;
        }
    }

    return ptr;
}

long long int split(std::vector<node>& suffix_tree, const std::string& s, long long int& size, std::pair<long long int, long long int> ptr) {
    if (ptr.second == suffix_tree[ptr.first].right - suffix_tree[ptr.first].left) {
        return ptr.first;
    }
    if (ptr.second == 0ll) {
        return suffix_tree[ptr.first].parent;
    }

    node v = suffix_tree[ptr.first];
    suffix_tree.push_back(node(v.left, v.left + ptr.second, v.parent));
    suffix_tree[v.parent].next(s[v.left]) = size;
    suffix_tree[size].next(s[v.left + ptr.second]) = ptr.first;
    suffix_tree[ptr.first].parent = size;
    suffix_tree[ptr.first].left += ptr.second;
    long long int prev_size = size;
    ++size;

    return prev_size;
}

long long int get_link(std::vector<node>& suffix_tree, const std::string& s, long long int& size, long long int v) {
    if (suffix_tree[v].link != -1ll) {
        return suffix_tree[v].link;
    }
    if (suffix_tree[v].parent == -1ll) {
        return 0ll;
    }

    long long int to = get_link(suffix_tree, s, size, suffix_tree[v].parent);
    long long int new_link = split(suffix_tree, s, size,
                    go(suffix_tree, s, std::make_pair(to, suffix_tree[to].right - suffix_tree[to].left),
                       suffix_tree[v].left + (long long int)(suffix_tree[v].parent == 0ll), suffix_tree[v].right));
    suffix_tree[v].link = new_link;
    return new_link;
}

void built_suffix_tree(std::vector<node>& suffix_tree, const std::string& s) {
    long long int size = 1;
    suffix_tree.push_back(node());
    std::pair<long long int, long long int> ptr = std::make_pair(0ll, 0ll);

    for (long long int i = 0ll; i < s.size(); ++i) {
        while (true) {
            std::pair<long long int, long long int> new_ptr = go(suffix_tree, s, ptr, i, i + 1ll);

            if (new_ptr.first != -1ll) {
                ptr = new_ptr;
                break;
            }

            long long int middle = split(suffix_tree, s, size, ptr);
            suffix_tree.push_back(node(i, s.size(), middle));
            suffix_tree[middle].next(s[i]) = size;
            ++size;

            ptr.first = get_link(suffix_tree, s, size, middle);
            ptr.second = suffix_tree[ptr.first].right - suffix_tree[ptr.first].left;

            if (middle == 0ll) {
                break;
            }
        }
    }
}

std::pair<long long int, long long int> find_refren(std::vector<node>& suffix_tree, long long int n, long long int v, long long int path) {
    std::pair<long long int, long long int> max_refren = std::make_pair(0ll, 0ll);

    for (auto it = suffix_tree[v].to.begin(); it != suffix_tree[v].to.end(); ++it) {
        std::pair<long long int, long long int> refren;
        if (suffix_tree[(*it).second].right != n + 1ll) {
            refren = find_refren(suffix_tree, n, (*it).second, path + suffix_tree[(*it).second].right - suffix_tree[(*it).second].left);
        } else {
            refren = find_refren(suffix_tree, n, (*it).second, path + suffix_tree[(*it).second].right - suffix_tree[(*it).second].left - 1ll);
        }

        if (refren.first > max_refren.first) {
            max_refren = refren;
        }
    }

    if (suffix_tree[v].to.size() == 0ll) {
        suffix_tree[v].leaves = 1ll;
    }
    for (auto it = suffix_tree[v].to.begin(); it != suffix_tree[v].to.end(); ++it) {
        suffix_tree[v].leaves += suffix_tree[(*it).second].leaves;
    }

    if (suffix_tree[v].leaves * path > max_refren.first) {
        max_refren = std::make_pair(suffix_tree[v].leaves * path, v);
    }

    return max_refren;
}

int main() {
    long long int n, m;
    scanf("%lld %lld", &n, &m);

    std::string s = "";
    for (long long int i = 0ll; i < n; ++i) {
        long long int symbol;
        scanf("%lld", &symbol);

        s.push_back('0' + symbol - 1ll);
    }
    s.push_back('$');

    std::vector<node> suffix_tree;
    built_suffix_tree(suffix_tree, s);

    std::pair<long long int, long long int> ans = find_refren(suffix_tree, n, 0ll, 0ll);

    std::vector<long long int> refren;
    long long int v = ans.second;
    while (v != 0ll) {
        for (long long int i = suffix_tree[v].right - 1ll; i >= suffix_tree[v].left; --i) {
            refren.push_back(s[i] - '0' + 1ll);
        }
        v = suffix_tree[v].parent;
    }
    std::reverse(refren.begin(), refren.end());

    if (refren[refren.size() - 1ll] == '$' - '0' + 1ll) {
        refren.pop_back();
    }
    printf("%lld\n", ans.first);
    printf("%lld\n", refren.size());
    for (long long int i = 0ll; i < refren.size(); ++i) {
        printf("%lld ", refren[i]);
    }

    return 0;
}