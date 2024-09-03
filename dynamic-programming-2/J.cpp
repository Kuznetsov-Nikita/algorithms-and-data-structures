#include <iostream>
#include <vector>

const long long int mod = 999999937;

std::vector<std::vector<long long int>> calculate(long long int n) {
    std::vector<std::vector<long long int>> ans = {{1}, {1}};
    std::vector<std::vector<long long int>> p = {{4, 1}, {1, 0}};

    while (n > 0) {
        if (n & 1) {
            long long int ans00 = ans[0][0];
            ans[0][0] = (p[0][0] * ans[0][0] % mod + p[0][1] * ans[1][0] % mod) % mod;
            ans[1][0] = (p[1][0] * ans00 % mod + p[1][1] * ans[1][0] % mod) % mod;
        }

        long long int p00 = p[0][0], p01 = p[0][1], p10 = p[1][0];
        p[0][0] = (p[0][0] * p[0][0] % mod + p[0][1] * p[1][0] % mod) % mod;
        p[0][1] = (p[0][1] * p00 % mod + p[1][1] * p[0][1] % mod) % mod;
        p[1][0] = (p[1][0] * p00 % mod + p[1][1] * p[1][0] % mod) % mod;
        p[1][1] = (p10 * p01 % mod + p[1][1] * p[1][1] % mod) % mod;

        n >>= 1;
    }

    return ans;
}

int main()
{
    long long int n;
    std::cin >> n;

    while (n != 0) {
        std::cout << calculate(n)[0][0] << '\n';
        std::cin >> n;
    }

    return 0;
}
