#include <iostream>
#include <string>
#include <vector>

std::vector<int> build_suf_arr(const std::string s) {
    std::vector<int> cnt (256, 0);
    std::vector<int> permutation (s.size(), 0);
    std::vector<int> classes (s.size(), 0);

    for (int i = 0; i < s.size(); ++i) {
        ++cnt[s[i]];
    }
    for (int i = 1; i < 256; ++i) {
        cnt[i] += cnt[i - 1];
    }
    for (int i = s.size() - 1; i >= 0; --i) {
        cnt[s[i]] -= 1;
        permutation[cnt[s[i]]] = i;
    }

    classes[permutation[0]] = 0;
    int classes_cnt = 1;

    for (int i = 1; i < s.size(); ++i) {
        if (s[permutation[i]] != s[permutation[i - 1]]) {
            ++classes_cnt;
        }
        classes[permutation[i]] = classes_cnt - 1;
    }

    std::vector<int> permutation_new (s.size(), 0);
    std::vector<int> classes_new (s.size(), 0);

    for (int h = 0; (1 << h) < s.size(); ++h) {
        for (int i = 0; i < s.size(); ++i) {
            permutation_new[i] = permutation[i] - (1 << h);
            if (permutation_new[i] < 0) {
                permutation_new[i] += s.size();
            }
        }

        cnt = std::vector<int> (s.size(), 0);

        for (int i = 0; i < s.size(); ++i) {
            ++cnt[classes[permutation_new[i]]];
        }
        for (int i = 1; i < classes_cnt; ++i) {
            cnt[i] += cnt[i - 1];
        }
        for (int i = s.size() - 1; i >= 0; --i) {
            cnt[classes[permutation_new[i]]] -= 1;
            permutation[cnt[classes[permutation_new[i]]]] = permutation_new[i];
        }

        classes_new[permutation[0]] = 0;
        classes_cnt = 1;

        for (int i = 1; i < s.size(); ++i) {
            if (classes[permutation[i]] != classes[permutation[i - 1]] ||
                classes[(permutation[i] + (1 << h)) % s.size()] != classes[(permutation[i - 1] + (1 << h)) % s.size()]) {
                ++classes_cnt;
            }
            classes_new[permutation[i]] = classes_cnt - 1;
        }

        classes = classes_new;
    }

    return classes;
}

int main() {
    std::string s;
    std::cin >> s;

    std::vector<int> classes = build_suf_arr(s + "$");
    std::vector<int> ans (s.size(), 0);

    for (int i = 0; i < ans.size(); ++i) {
        ans[classes[i] - 1] = i + 1;
    }

    for (int i = 0; i < ans.size(); ++i) {
        std::cout << ans[i] << ' ';
    }

    return 0;
}
