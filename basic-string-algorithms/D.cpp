#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

void solve(std::string& s) {
    std::vector<int> dots;
    std::vector<std::string> words;

    bool is_first_dot = (s[0] == '.') ? true : false;
    int i = 0;

    s += '#';
    while (i < s.size() - 1) {
        int dots_cnt = 0;
        while (i < s.size() - 1 && s[i] == '.') {
            ++i;
            ++dots_cnt;
        }
        if (dots_cnt != 0) {
            dots.push_back(dots_cnt);
        }
        dots_cnt = 0;

        std::string word;
        while (i < s.size() - 1 && s[i] != '.' && s[i] != '#') {
            word += s[i];
            ++i;
        }
        if (word.size() != 0) {
            words.push_back(word);
        }
    }

    std::sort(words.begin(), words.end());

    std::string ans;

    i = 0;
    int j = 0;
    if (is_first_dot) {
        for (int k = 0; k < dots[i]; ++k) {
            ans += '.';
        }
        ++i;
    }

    while (i < dots.size() || j < words.size()) {
        if (j < words.size()) {
            ans += words[j];
            ++j;
        }

        if (i < dots.size()) {
            for (int k = 0; k < dots[i]; ++k) {
                ans += '.';
            }
            ++i;
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
