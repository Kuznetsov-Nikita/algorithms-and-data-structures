#include <iostream>
#include <set>
#include <vector>

const int MAX_SIZE = 2000000;

void compute_prime_dividers(std::vector<std::vector<int>>& prime_dividers) {
    std::vector<bool> used (MAX_SIZE, false);

    for (int i = 2; i < MAX_SIZE; ++i) {
        if (!used[i]) {
            for (int j = i; j < MAX_SIZE; j += i) {
                used[j] = true;
                prime_dividers[j].push_back(i);
            }
        }
    }
}

void compute_possible_numbers(std::set<int>& possible_numbers) {
    for (int i = 2; i < MAX_SIZE; ++i) {
        possible_numbers.insert(i);
    }
}

std::vector<int> solve(const std::vector<int>& a, int n) {
    std::set<int> possible_numbers;
    compute_possible_numbers(possible_numbers);

    std::vector<std::vector<int>> prime_dividers (MAX_SIZE, std::vector<int> ());
    compute_prime_dividers(prime_dividers);

    std::vector<int> b (n, 0);

    std::vector<bool> used (MAX_SIZE, false);
    bool is_equal = true;

    for (int i = 0; i < n; ++i) {
        int current;
        if (is_equal) {
            current = *(possible_numbers.lower_bound(a[i]));
            if (current != a[i]) {
                is_equal = false;
            }
        } else {
            current = *(possible_numbers.begin());
        }

        b[i] = current;

        for (int j = 0; j < prime_dividers[current].size(); ++j) {
            for (int k = prime_dividers[current][j]; k < MAX_SIZE; k += prime_dividers[current][j]) {
                if (!used[k]) {
                    used[k] = true;
                    possible_numbers.erase(k);
                }
            }
        }
    }

    return b;
}

int main() {
    int n;
    scanf("%d", &n);

    std::vector<int> a (n, 0);
    for (int i = 0; i < n; ++i) {
        scanf("%d", &a[i]);
    }

    std::vector<int> b = solve(a, n);

    for (int i = 0; i < n; ++i) {
        printf("%d ", b[i]);
    }

    return 0;
}