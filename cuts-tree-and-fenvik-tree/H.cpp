#include <cmath>
#include <stdio.h>
#include <vector>

std::pair<int, int> get_mins(std::vector<int>& a, std::pair<int, int> elem_1, std::pair<int, int> elem_2) {
    int min_1_1 = (a[elem_1.first] < a[elem_2.first]) ? elem_1.first : elem_2.first;
    int min_1_2 = elem_1.first + elem_2.first - min_1_1;

    int min_1_1_second = a[elem_1.first] < a[elem_2.first] ? elem_1.second : elem_2.second;
    int min_2;

    if (min_1_1_second != -1) {
        min_2 = a[min_1_1_second] < a[min_1_2] ? min_1_1_second : min_1_2;
        if (min_2 == min_1_1) {
            min_2 = (a[elem_1.second] < a[elem_2.second]) ? elem_1.second : elem_2.second;
        }
    } else {
        min_2 = min_1_2;
    }

    return std::pair<int, int> (min_1_1, min_2);
}

int get_min_2(std::vector<int>& a, std::vector<std::vector<std::pair<int, int>>>& table, int left, int right) {
    int i = floor(log2(right - left + 1));
    return a[get_mins(a, table[i][left], table[i][right - pow(2, i) + 1]).second];
}

void build(std::vector<int>& a, std::vector<std::vector<std::pair<int, int>>>& table) {
    int exp = floor(log2(a.size())) + 1;

    std::vector<std::pair<int, int>> tmp;
    for (int i = 0; i < a.size(); ++i) {
        tmp.push_back(std::pair<int ,int> (i, -1));
    }
    table.push_back(tmp);

    int pow = 1;
    for (int i = 1; i < exp; ++i) {
        pow *= 2;

        std::vector<std::pair<int, int>> tmp;
        for (int j = 0; j < a.size() - pow + 1; ++j) {
            tmp.push_back(get_mins(a, table[i - 1][j], table[i - 1][j + pow / 2]));
        }
        table.push_back(tmp);
    }
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);

    std::vector<int> a;

    for (int i = 0; i < n; ++i) {
        int a_i;
        scanf("%d", &a_i);
        a.push_back(a_i);
    }

    std::vector<std::vector<std::pair<int, int>>> table;
    build(a, table);

    for (int i = 0; i < m; ++i) {
        int l, r;
        scanf("%d %d", &l, &r);

        printf("%d\n", get_min_2(a, table, l - 1, r - 1));
    }

    return 0;
}
