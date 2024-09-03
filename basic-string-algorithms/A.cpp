#include <iostream>
#include <string>
#include <vector>

std::vector<int> prefix_function(const std::string& s) {
    int n = s.size();
    std::vector<int> p (n, 0);

    for (int i = 1; i < n; ++i) {
        int j = p[i - 1];

        while (j > 0 && s[j] != s[i]) {
            j = p[j - 1];
        }

        if (s[j] == s[i]) {
            ++j;
        }

        p[i] = j;
    }

    return p;
}

void solve(const std::string& s, const std::string& t) {
    std::vector<int> p = prefix_function(t + '#' + s);

    for (int i = t.size() + 1; i < p.size(); ++i) {
        if (p[i] == t.size()) {
            std::cout << i - 2 * t.size() << ' ';
        }
    }
}

int main() {
    std::string s, t;
    std::cin >> s >> t;

    solve(s, t);

    return 0;
}