#include <iostream>
#include <stdio.h>
#include <utility>

void init_tree(std::pair<int, int>* t, int v, int t_left, int t_right) {
    if (t_left == t_right) {
        t[v].first = (t_left % 12345) * (t_left % 12345) % 12345 + ((t_left % 23456) * (t_left % 23456) % 23456) * (t_left % 23456) % 23456;
        t[v].second = t[v].first;
    } else {
        int t_middle = (t_left + t_right) / 2;

        init_tree(t, v * 2, t_left, t_middle);
        init_tree(t, v * 2 + 1, t_middle + 1, t_right);

        t[v] = std::pair<int, int> (std::max(t[v * 2].first, t[v * 2 + 1].first), std::min(t[v * 2].second, t[v * 2 + 1].second));
    }
}

void update(std::pair<int, int>* t, int v, int t_left, int t_right, int pos, int value) {
    if (t_left == t_right) {
        t[v].first = value;
        t[v].second = value;
    } else {
        int t_middle = (t_left + t_right) / 2;

        if (pos <= t_middle) {
            update(t, v * 2, t_left, t_middle, pos, value);
        } else {
            update(t, v * 2 + 1, t_middle + 1, t_right, pos, value);
        }

        t[v] = std::pair<int, int> (std::max(t[v * 2].first, t[v * 2 + 1].first), std::min(t[v * 2].second, t[v * 2 + 1].second));
    }
}

std::pair<int, int> get_ans(std::pair<int, int>* t, int v, int t_left, int t_right, int left, int right) {
    if (t_left == left && t_right == right) {
        return t[v];
    } else {
        int t_middle = (t_left + t_right) / 2;

        if (right <= t_middle) {
            return get_ans(t, v * 2, t_left, t_middle, left, right);
        } else if (left >= t_middle + 1) {
            return get_ans(t, v * 2 + 1, t_middle + 1, t_right, left, right);
        } else {
            std::pair<int, int> pair_1 = get_ans(t, v * 2, t_left, t_middle, left, t_middle);
            std::pair<int, int> pair_2 = get_ans(t, v * 2 + 1, t_middle + 1, t_right, t_middle + 1, right);

            return std::pair<int, int> (std::max(pair_1.first, pair_2.first), std::min(pair_1.second, pair_2.second));
        }
    }
}

int main() {
    std::pair<int, int>* tree = new std::pair<int, int>[4 * 100001];
    init_tree(tree, 1, 1, 100001);

    int k;
    scanf("%d", &k);

    for (int i = 0; i < k; ++i) {
        int x, y;
        scanf("%d %d", &x, &y);

        if (x > 0) {
            std::pair<int, int> ans = get_ans(tree, 1, 1, 100001, x, y);
            printf("%d\n", ans.first - ans.second);
        } else {
            update(tree, 1, 1, 100001, -x, y);
        }
    }

    return 0;
}
