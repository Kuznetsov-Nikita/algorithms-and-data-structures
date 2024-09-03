#pragma GCC optimize("O2")

#include <iostream>
#include <functional>
#include <stdio.h>
#include <vector>

int main()
{
    long long int w, h, n;
    scanf("%lld %lld %lld", &w, &h, &n);

    if (5 * n >= w * h) {
        bool canvas[w + 1][h + 1];

        for (int i = 1; i <= w; ++i) {
            for (int j = 1; j <= h; ++j) {
                canvas[i][j] = false;
            }
        }

        for (int i = 0; i < n; ++i) {
            int x, y;
            scanf("%d %d", &x, &y);

            if (x >= 1 && y >= 1 && x <= w && y <= h) {
                canvas[x][y] = true;
            }
            if (x - 1 >= 1 && y >= 1 && x - 1 <= w && y <= h) {
                canvas[x - 1][y] = true;
            }
            if (x >= 1 && y - 1 >= 1 && x <= w && y - 1 <= h) {
                canvas[x][y - 1] = true;
            }
            if (x + 1 >= 1 && y >= 1 && x + 1 <= w && y <= h) {
                canvas[x + 1][y] = true;
            }
            if (x >= 1 && y + 1 >= 1 && x <= w && y + 1 <= h) {
                canvas[x][y + 1] = true;
            }
        }

        long long int cnt = 0;
        for (int i = 1; i <= w; ++i) {
            for (int j = 1; j <= h; ++j) {
                if (canvas[i][j]) {
                    ++cnt;
                }
            }
        }

        if (cnt == w * h) {
            printf("Yes");
        } else {
            printf("No");
        }
    } else {
        printf("No");
    }

    return 0;
}

