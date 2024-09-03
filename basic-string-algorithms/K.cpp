#include <iostream>
#include <string>
#include <vector>

std::vector<long long int> z_function(const std::string& s) {
    long long int n = s.size();
    std::vector<long long int> z (n, 0);
    long long int l = -1, r = -1;

    for (long long int i = 1; i < n; ++i) {
        if (l <= i && i <= r) {
            z[i] = std::min(z[i - l], r - i + 1);
        }

        while (i + z[i] < n && s[z[i]] == s[i + z[i]]) {
            ++z[i];
        }

        if (i + z[i] - 1 > r) {
            l = i;
            r = i + z[i] - 1;
        }
    }

    return z;
}

void solve(const std::string& s) {
    std::string tmp;
    long long int len = 0, ans = 0;

    for (long long int i = 0; i < s.size(); ++i) {
        tmp = s[i] + tmp;
        ++len;

        std::vector<long long int> z = z_function(tmp);
        long long int max_z = 0;

        for (long long int j = 0; j < len; ++j) {
            max_z = std::max(max_z, z[j]);
        }

        for (long long int j = len; j > max_z; --j) {
            ans += j;
        }
    }
    std::cout << ans;
}

int main() {
    std::string s;
    std::cin >> s;

    solve(s);

    return 0;
}
