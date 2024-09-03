#include <stdio.h>
#include <vector>

const int N = 10000000;

void build_tree(std::vector<int>& a, std::vector<int>& tree, int v, int l, int r) {
    if (l == r) {
        tree[v] = a[l];
    } else {
        int m = (l + r) / 2;

        build_tree(a, tree, v * 2 + 1, l, m);
        build_tree(a, tree, v * 2 + 2, m + 1, r);
        tree[v] = std::min(tree[v * 2 + 1], tree[v * 2 + 2]);
    }
}

void push(std::vector<int>& tmp, std::vector<int>& tree, int v, int tl, int tr) {
    if (tmp[v] != N) {
        tree[v] = tmp[v];

        if (tl != tr) {
            tmp[v * 2 + 1] = tmp[v];
            tmp[v * 2 + 2] = tmp[v];
        }

        tmp[v] = N;
    }
}

void update(std::vector<int>& a, std::vector<int>& tmp, std::vector<int>& tree, int v, int tl, int tr, int l, int r, int val) {
    push(tmp, tree, v, tl, tr);
    if (r < tl || tr < l) {
        return;
    }

    if (l <= tl && tr <= r) {
        tmp[v] = val;
        push(tmp, tree, v, tl, tr);
        return;
    }

    int tm = tl + (tr - tl) / 2;

    update(a, tmp, tree, v * 2 + 1, tl, tm, l, r, val);
    update(a, tmp, tree, v * 2 + 2, tm + 1, tr, l, r, val);

    tree[v] = std::min(tree[v * 2 + 1], tree[v * 2 + 2]);
}

int find_min(std::vector<int>& tmp, std::vector<int>& tree, int v, int tl, int tr, int l, int r) {
    push(tmp, tree, v, tl, tr);

    if (tl > r || tr < l) {
        return N;
    }

    if (l <= tl && tr <= r) {
        return tree[v];
    }

    int tm = tl + (tr - tl) / 2;
    return std::min(find_min(tmp, tree, v * 2 + 1, tl, tm, l, r), find_min(tmp, tree, v * 2 + 2, tm + 1, tr, l, r));
}

int main() {
    int n;
    scanf("%d", &n);

    std::vector<int> a(n);
    std::vector<int> tree(4 * n, N);
    std::vector<int> tmp(4 * n, N);

    for (int i = 0; i < n; i++) {
        int r, g, b;
        scanf("%d %d %d", &r, &g, &b);
        a[i] = r + g + b;
    }

    build_tree(a, tree, 0, 0, n - 1);

    int m;
    scanf("%d", &m);

    for (int i = 0; i < m; i++) {
        int c, d, r, g, b, e, f;
        scanf("%d %d %d %d %d %d %d", &c, &d, &r, &g, &b, &e, &f);

        update(a, tmp, tree, 0, 0, n - 1, c, d, r + g + b);

        printf("%d ", find_min(tmp, tree, 0, 0, n - 1, e, f));
    }
}
