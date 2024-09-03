#include <iostream>
#include <vector>

const long long int mod = 1000000007;

bool xor_match(long long int a, long long int b) {
    long long int x = a xor b;
    long long int cnt = 0;

    while (x > 0) {
        ++cnt;
        x = x & (x - 1);
    }

    return (cnt % 3 == 0) ? true : false;
}

void compute_matrix(std::vector<std::vector<long long int>>& matrix, std::vector<long long int>& a, long long int n) {
    for (long long int i = 0; i < n; ++i) {
        for (long long int j = 0; j < n; ++j) {
            if (xor_match(a[i], a[j])) {
                matrix[i][j] = 1;
            }
        }
    }
}

std::vector<std::vector<long long int>> calculate(std::vector<std::vector<long long int>> matrix, long long int n, long long int k) {
    std::vector<std::vector<long long int>> res (n, std::vector<long long int> (n, 0));
    for (long long int i = 0; i < n; ++i) {
        res[i][i] = 1;
    }

    std::vector<std::vector<long long int>> p = matrix;

    while (k > 0) {
        if (k % 2 == 1) {
            for (long long int i = 0; i < n; ++i) {
                std::vector<long long int> new_row;
                for (long long int j = 0; j < n; ++j) {
                    long long int value = 0;
                    for (long long int l = 0; l < n; ++l) {
                        value = (value + res[i][l] * p[l][j]) % mod;
                    }
                    new_row.push_back(value);
                }
                res[i] = new_row;
            }
        }

        std::vector<std::vector<long long int>> p_old = p;
        for (long long int i = 0; i < n; ++i) {
            std::vector<long long int> new_row;
            for (long long int j = 0; j < n; ++j) {
                long long int value = 0;
                for (long long int l = 0; l < n; ++l) {
                    value = (value + p[i][l] * p_old[l][j]) % mod;
                }
                new_row.push_back(value);
            }
            p[i] = new_row;
        }

        k /= 2;
    }

    return res;
}

int main() {
    long long int n, k;
    std::cin >> n >> k;

    std::vector<long long int> a (n, 0);
    for (long long int i = 0; i < n; ++i) {
        std::cin >> a[i];
    }

    std::vector<std::vector<long long int>> matrix (n, std::vector<long long int> (n, 0));

    compute_matrix(matrix, a, n);

    std::vector<long long int> dp0 (n, 1);

    std::vector<std::vector<long long int>> matrix_pow = calculate(matrix, n, k - 1);
    long long int ans = 0;

    for (long long int i = 0; i < n; ++i) {
        long long int p = 0;
        for (long long int j = 0; j < n; ++j) {
            p = (p + matrix_pow[i][j] * dp0[j]) % mod;
        }
        ans = (ans + p) % mod;
    }

    std::cout << ans;

    return 0;
}
