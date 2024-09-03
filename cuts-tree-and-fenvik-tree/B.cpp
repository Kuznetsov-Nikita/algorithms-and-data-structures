#include <stdio.h>

void update(int* t, int x, int val, int n) {
    while (x < n) {
        t[x] += val;
        x |= x + 1;
    }
}

void build(int* a, int* t, int n) {
    for (int i = 0; i < n; ++i) {
        if (i % 2 == 0) {
            update(t, i, a[i], n);
        } else {
            update(t, i, -a[i], n);
        }
    }
}

long long int sum(int* t, int x) {
    long long int res = 0;

    while (x >= 0) {
        res += t[x];
        x = (x & (x + 1)) - 1;
    }

    return res;
}

long long int get_sum(int* t, int left, int right) {
    long long int res;

    if (left != 0) {
        res = sum(t, right) - sum(t, left - 1);
    } else {
        res = sum(t, right);
    }

    if (left % 2 == 1) {
        res *= -1;
    }

    return res;
}

int main() {
    int n;
    scanf("%d", &n);

    int a[100001] = {0};
    int t[100001] = {0};

    for (int i = 0; i < n; ++i) {
        scanf("%d", &a[i]);
    }
    build(a, t, n);

    int m;
    scanf("%d", &m);

    for (int i = 0; i < m; ++i) {
        int command;
        scanf("%d", &command);

        if (command == 0) {
            int i, j;
            scanf("%d %d", &i, &j);
            if (i % 2 == 1) {
                update(t, i - 1, -a[i - 1] + j, n);
            } else {
                update(t, i - 1, a[i - 1] - j, n);
            }
            a[i - 1] = j;
        } else {
            int l, r;
            scanf("%d %d", &l, &r);
            printf("%lld\n", get_sum(t, l - 1, r - 1));
        }
    }

    return 0;
}
