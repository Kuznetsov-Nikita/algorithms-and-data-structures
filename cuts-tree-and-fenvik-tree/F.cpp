#include <stdio.h>
#include <vector>

int t[128][128][128];

void update(int x, int y, int z, int val, int n) {
    for (int i = x; i < n; i = i | (i + 1)) {
        for (int j = y; j < n; j = j | (j + 1)) {
            for (int k = z; k < n; k = k | (k + 1)) {
                t[i][j][k] += val;
            }
        }
    }
}

int get_sum(int x, int y, int z) {
    int ans = 0;

    for (int i = x; i >= 0; i = (i & (i + 1)) - 1) {
        for (int j = y; j >= 0; j = (j & (j + 1)) - 1) {
            for (int k = z; k >= 0; k = (k & (k + 1)) - 1) {
                ans += t[i][j][k];
            }
        }
    }

    return ans;
}

int main() {
    int n;
    scanf("%d", &n);

    int command;
    do {
        scanf("%d", &command);

        if (command == 1) {
            int x, y, z, k;
            scanf("%d %d %d %d", &x, &y, &z, &k);

            update(x, y, z, k, n);
        } else if (command == 2) {
            int x_1, y_1, z_1, x_2, y_2, z_2;
            scanf("%d %d %d %d %d %d", &x_1, &y_1, &z_1, &x_2, &y_2, &z_2);

            printf("%d\n", get_sum(x_2, y_2, z_2) - get_sum(x_2, y_1 - 1, z_2) - get_sum(x_1 - 1, y_2, z_2) - get_sum(x_2, y_2, z_1 - 1) + get_sum(x_1 - 1, y_1 - 1, z_2) + get_sum(x_1 - 1, y_2, z_1 - 1) + get_sum(x_2, y_1 - 1, z_1 - 1) - get_sum(x_1 - 1, y_1 - 1, z_1 - 1));
        }
    } while (command != 3);

    return 0;
}
