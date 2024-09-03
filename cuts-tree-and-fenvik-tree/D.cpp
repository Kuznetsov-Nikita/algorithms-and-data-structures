#include <algorithm>
#include <set>
#include <stdio.h>
#include <vector>

struct my_pair {
    long long int first, second, third;

    my_pair(long long int first, long long int second, long long int third): first(first), second(second), third(third) {}
};

bool operator<(my_pair a, my_pair b) {
    return (a.first > b.first) || (a.first == b.first && a.second < b.second);
}

long long int t[300001];

void inc(int x, int n, long long int value) {
    while (x < n) {
        t[x] += value;
        x |= x + 1;
    }
}

long long int get_cnt(int x) {
    long long int res = 0;

    while (x >= 0) {
        res += t[x];
        x = (x & (x + 1)) - 1;
    }

    return res;
}

int main() {
    int n;
    scanf("%d", &n);

    std::vector<long long int> right_ends;
    std::set<my_pair> cuts;

    for (int i = 0; i < n; ++i) {
        long long int l, r;
        scanf("%lld %lld", &l, &r);

        if (cuts.count(my_pair(l, r, 0)) != 0) {
            int cnt = (*cuts.find(my_pair(l, r, 0))).third + 1;
            cuts.erase(my_pair(l, r, 0));
            cuts.insert(my_pair(l, r, cnt));
        } else {
            cuts.insert(my_pair(l, r, 1));
        }

        right_ends.push_back(r);
    }

    std::sort(right_ends.begin(), right_ends.end());

    long long int ans = 0;

    for (auto it = cuts.begin(); it != cuts.end(); ++it) {
        int p = lower_bound(right_ends.begin(), right_ends.end(), (*it).second) - right_ends.begin();

        ans += get_cnt(p) * (*it).third;
        inc(p, n, (*it).third);
    }

    printf("%lld", ans);

    return 0;
}
