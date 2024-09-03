#include <iostream>
#include <map>
#include <string>
#include <vector>

struct node {
    long long int left, right, parent, link, leaves;
    std::map<char, long long int> to;

    node(long long int left = 0, long long int right = 0, long long int parent = -1): left(left), right(right), parent(parent), link(-1), leaves(0) {}

    long long int& next(char c) {
        if (to.count(c) == 0) {
            to[c] = -1;
        }
        return to[c];
    }
};

std::pair<long long int, long long int> go(std::vector<node>& suffix_tree, const std::string& s, std::pair<long long int, long long int> ptr, long long int left, long long int right) {
    while (left < right) {
        if (ptr.second == suffix_tree[ptr.first].right - suffix_tree[ptr.first].left) {
            ptr.first = suffix_tree[ptr.first].next(s[left]);
            ptr.second = 0;

            if (ptr.first == -1) {
                return ptr;
            }
        } else {
            if (s[suffix_tree[ptr.first].left + ptr.second] != s[left]) {
                return std::make_pair(-1, -1);
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
    if (ptr.second == 0) {
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
    if (suffix_tree[v].link != -1) {
        return suffix_tree[v].link;
    }
    if (suffix_tree[v].parent == -1) {
        return 0;
    }

    long long int to = get_link(suffix_tree, s, size, suffix_tree[v].parent);
    long long int new_link = split(suffix_tree, s, size,
                    go(suffix_tree, s, std::make_pair(to, suffix_tree[to].right - suffix_tree[to].left),
                       suffix_tree[v].left + (long long int)(suffix_tree[v].parent == 0), suffix_tree[v].right));
    suffix_tree[v].link = new_link;
    return new_link;
}

void built_suffix_tree(std::vector<node>& suffix_tree, const std::string& s) {
    long long int size = 1;
    suffix_tree.push_back(node());
    std::pair<long long int, long long int> ptr = std::make_pair(0, 0);

    for (long long int i = 0; i < s.size(); ++i) {
        while (true) {
            std::pair<long long int, long long int> new_ptr = go(suffix_tree, s, ptr, i, i + 1);

            if (new_ptr.first != -1) {
                ptr = new_ptr;
                break;
            }

            int middle = split(suffix_tree, s, size, ptr);
            suffix_tree.push_back(node(i, s.size(), middle));
            suffix_tree[middle].next(s[i]) = size;
            ++size;

            ptr.first = get_link(suffix_tree, s, size, middle);
            ptr.second = suffix_tree[ptr.first].right - suffix_tree[ptr.first].left;

            if (middle == 0) {
                break;
            }
        }
    }
}

void find_k_string_with_repeats(const std::vector<node>& suffix_tree, long long int n, long long int v, long long int pos, long long int k, long long int& cur_num, std::pair<long long int, long long int>& answer) {
    if (suffix_tree[v].right - suffix_tree[v].left != pos || suffix_tree[v].right != n) {
        if (v != 0) {
            cur_num += suffix_tree[v].leaves;
        }
    }

    if (cur_num >= k) {
        answer = std::make_pair(v, pos);
        return;
    }

    if (suffix_tree[v].right - suffix_tree[v].left == pos || v == 0) {
        for (auto it = suffix_tree[v].to.begin(); it != suffix_tree[v].to.end(); ++it) {
            find_k_string_with_repeats(suffix_tree, n, (*it).second, 1, k, cur_num, answer);
            if (answer != std::pair<long long int, long long int> (0, 0)) {
                return;
            }
        }
    } else {
        if (suffix_tree[v].left + pos != suffix_tree[v].right) {
            find_k_string_with_repeats(suffix_tree, n, v, pos + 1, k, cur_num, answer);
        }
    }
}

std::string get_ans(const std::vector<node>& suffix_tree, std::string& s, long long int v, long long int n) {
    std::string ans;
    ans = s.substr(suffix_tree[v].left, n);
    v = suffix_tree[v].parent;

    while (v > 0) {
        ans = s.substr(suffix_tree[v].left, suffix_tree[v].right - suffix_tree[v].left) + ans;
        v = suffix_tree[v].parent;
    }

    return ans;
}

void count_leaves(std::vector<node>& suffix_tree, long long int v) {
    if (suffix_tree[v].to.size() == 0ll) {
        suffix_tree[v].leaves = 1ll;
    }
    for (auto it = suffix_tree[v].to.begin(); it != suffix_tree[v].to.end(); ++it) {
        count_leaves(suffix_tree, (*it).second);
        suffix_tree[v].leaves += suffix_tree[(*it).second].leaves;
    }
}

int main() {
    std::string s;
    std::cin >> s;

    long long int k;
    std::cin >> k;

    std::vector<node> suffix_tree;
    built_suffix_tree(suffix_tree, s + "$");
    count_leaves(suffix_tree, 0);

    long long int cur_num = 0;
    std::pair<long long int, long long int> ans = std::make_pair(0, 0);
    find_k_string_with_repeats(suffix_tree, s.size() + 1, 0, 1, k, cur_num, ans);

    if (ans == std::pair<long long int, long long int> (0, 0)) {
        std::cout << "No such line.";
    } else {
        std::cout << get_ans(suffix_tree, s, ans.first, ans.second);
    }

    return 0;
}