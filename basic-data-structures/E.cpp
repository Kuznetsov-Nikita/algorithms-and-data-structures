#include <stdio.h>
#include <cmath>
#include <algorithm>
 
int a[901][3001], b[901][3001];
 
int binary_search(int a[][3001], int b[][3001], int i, int j, int l) {
    int left = 0, right = l;
 
    a[i][0] = -100000;
    b[j][0] = 100000;
 
    while (right - left > 1) {
        int middle = left + (right - left) / 2;
 
        if (a[i][middle] - b[j][middle] >= 0) {
            right = middle;
        } else {
            left = middle;
		}
    }
 
    if (std::max(a[i][right], b[j][right]) < std::max(a[i][left], b[j][left])) {
        return right;
    } else {
        return left;
	}
}
 
int main() {
    int n, m, l, q;
 
    scanf("%d %d %d", &n, &m, &l);
 
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= l; ++j) {
            scanf("%d", &a[i][j]);
		}
	}
 
    for (int i = 1; i <= m; ++i) {
        for (int j = 1; j <= l; ++j) {
            scanf("%d", &b[i][j]);
		}
	}
 
    scanf("%d", &q);
 
    for (int k = 0; k < q; ++k) {
        int i, j;
 
        scanf("%d %d", &i, &j);
 
        printf("%d\n", binary_search(a, b, i, j, l));
    }
 
    return 0;
}