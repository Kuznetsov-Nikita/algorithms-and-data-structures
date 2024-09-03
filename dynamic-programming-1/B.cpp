#include <algorithm>
#include <functional>
#include <stdio.h>
#include <vector>

const int inf = 2147483647;

bool predicat(const int& a, const int& b) {
    return !(a <= b);
}

int main()
{
    int n;
    scanf("%d", &n);

    std::vector<int> a (n, 0);

    for (int i = 0; i < n; ++i) {
        scanf("%d", &a[i]);
    }

    std::vector<int> dp (n + 1, -inf - 1);
    dp[0] = inf;

    std::vector<int> pos (n, 0);
    pos[0] = -1;

    std::vector<int> prev (n - 1, 0);
    int len = 0;

    for (int i = 0; i < n; ++i) {
        int j = int(std::upper_bound(dp.begin(), dp.end(), a[i], predicat) - dp.begin());

        if (dp[j - 1] >= a[i] && a[i] >= dp[j]) {
            dp[j] = a[i];
            pos[j] = i;
            prev[i] = pos[j - 1];
            len = std::max(len, j);
        }
    }

    printf("%d\n", len);

    std::vector<int> answer (len, 0);
    int p = pos[len];

    while (p != -1) {
        answer[len - 1] = p + 1;
        --len;
        p = prev[p];
    }

    for (int i = 0; i < answer.size(); ++i) {
        printf("%d ", answer[i]);
    }

    return 0;
}
