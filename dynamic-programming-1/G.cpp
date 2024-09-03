#include <iostream>
#include <vector>

int main()
{
    std::string s1, s2;
    std::cin >> s1 >> s2;

    std::vector<int> dp_old(s2.length() + 1, 0);
    std::vector<int> dp_new(s2.length() + 1, 0);
    std::vector<std::vector<bool>> prev(s1.length() + 1, std::vector<bool> (s2.length() + 1, false));

    for (int i = 1; i <= s1.length(); ++i) {
        for (int j = 1; j <= s2.length(); ++j) {
            if  (s1[i - 1] != s2[j - 1]) {
                dp_new[j] = std::max(dp_old[j], dp_new[j - 1]);

                if (dp_old[j] >= dp_new[j - 1]) {
                    prev[i][j] = true;
                }
            } else {
                dp_new[j] = std::max(1 + dp_old[j - 1], std::max(dp_old[j], dp_new[j - 1]));

                if (1 + dp_old[j - 1] >= std::max(dp_old[j], dp_new[j - 1])) {
                    prev[i][j] = true;
                } else if (dp_old[j] >= dp_new[j - 1]) {
                    prev[i][j] = true;
                } else {
                    prev[i][j] = false;
                }
            }
        }

        dp_old = dp_new;
        dp_new = std::vector<int> (s2.length() + 1, 0);
    }

    std::string ans = "";
    short int i = s1.length();
    short int j = s2.length();
    while (i != 0 && j != 0) {
        if (s1[i - 1] == s2[j - 1]) {
            ans = s1[i - 1] + ans;
            --i;
            --j;
        } else {
            if (prev[i][j]) {
                --i;
            } else {
                --j;
            }
        }
    }

    std::cout << ans;

    return 0;
}

