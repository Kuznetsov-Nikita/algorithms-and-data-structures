#include <iostream>
#include <map>
#include <string>
#include <vector>

struct node {
    int left, right, parent, link;
    std::map<char, int> to;

    node(int left = 0, int right = 0, int parent = -1): left(left), right(right), parent(parent), link(-1) {}

    int& next(char c) {
        if (to.count(c) == 0) {
            to[c] = -1;
        }
        return to[c];
    }
};

std::pair<int, int> go(std::vector<node>& suffix_tree, const std::string& s, std::pair<int, int> ptr, int left, int right) {
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

int split(std::vector<node>& suffix_tree, const std::string& s, int& size, std::pair<int, int> ptr) {
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
    int prev_size = size;
    ++size;

    return prev_size;
}

int get_link(std::vector<node>& suffix_tree, const std::string& s, int& size, int v) {
    if (suffix_tree[v].link != -1) {
        return suffix_tree[v].link;
    }
    if (suffix_tree[v].parent == -1) {
        return 0;
    }

    int to = get_link(suffix_tree, s, size, suffix_tree[v].parent);
    int new_link = split(suffix_tree, s, size,
                    go(suffix_tree, s, std::make_pair(to, suffix_tree[to].right - suffix_tree[to].left),
                       suffix_tree[v].left + int(suffix_tree[v].parent == 0), suffix_tree[v].right));
    suffix_tree[v].link = new_link;
    return new_link;
}

void built_suffix_tree(std::vector<node>& suffix_tree, const std::string& s) {
    int size = 1;
    suffix_tree.push_back(node());
    std::pair<int, int> ptr = std::make_pair(0, 0);

    for (int i = 0; i < s.size(); ++i) {
        while (true) {
            std::pair<int, int> new_ptr = go(suffix_tree, s, ptr, i, i + 1);

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

void print_suffix_tree(const std::vector<node>& suffix_tree, int v, int& num) {
    int this_num = num;
    ++num;

    for (auto it = suffix_tree[v].to.begin(); it != suffix_tree[v].to.end(); ++it) {
        printf("%d %d %d\n", this_num, suffix_tree[(*it).second].left, suffix_tree[(*it).second].right);
        print_suffix_tree(suffix_tree, (*it).second, num);
    }
}

int main() {
    std::string s;
    std::cin >> s;

    std::vector<node> suffix_tree;
    built_suffix_tree(suffix_tree, s);

    printf("%d\n", suffix_tree.size());
    int num = 0;
    print_suffix_tree(suffix_tree, 0, num);

    return 0;
}
