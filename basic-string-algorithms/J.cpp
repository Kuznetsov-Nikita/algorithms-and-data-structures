#include <algorithm>
#include <cstring>
#include <iostream>
#include <string>
#include <vector>

std::vector<int> z_function(const std::string& s) {
    int n = s.size();
    std::vector<int> z (n, 0);
    int l = -1, r = -1;

    for (int i = 1; i < n; ++i) {
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

int main() {
    std::string t, p;
    std::cin >> t >> p;

    int k;
    std::cin >> k;

    std::vector<int> z1 = z_function(p + "#" + t);
    std::reverse(p.begin(), p.end());
    std::reverse(t.begin(), t.end());
    std::vector<int> z2 = z_function(p + "#" + t);

    std::vector<int> ans;

    for (int i = p.size() + 1; i < t.size() + 2; ++i) {
        if (z1[i] + z2[z2.size() - i + 1] + k >= p.size()) {
            ans.push_back(i - p.size());
        }
    }

    std::cout << ans.size() << '\n';
    for (int i = 0; i < ans.size(); ++i) {
        std::cout << ans[i] << ' ';
    }

    return 0;
}
