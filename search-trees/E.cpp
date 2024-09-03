#include <set>
#include <unordered_map>
#include <stdio.h>
#include <string.h>

void Add(std::unordered_map<int, std::set<long long int>>& sets,
         std::unordered_map<long long int, std::set<int>>& numbers_in_sets, long long int e, int s) {
    sets[s].insert(e);
    numbers_in_sets[e].insert(s);
}

void Delete(std::unordered_map<int, std::set<long long int>>& sets,
            std::unordered_map<long long int, std::set<int>>& numbers_in_sets, long long int e, int s) {
    sets[s].erase(sets[s].find(e));
    numbers_in_sets[e].erase(numbers_in_sets[e].find(s));
}

void Clear(std::unordered_map<int, std::set<long long int>>& sets,
           std::unordered_map<long long int, std::set<int>>& numbers_in_sets, int s) {
    for (std::set<long long int>::iterator it = sets[s].begin(); it != sets[s].end(); ++it) {
        numbers_in_sets[*it].erase(numbers_in_sets[*it].find(s));
    }
    sets[s].clear();
}

void Listset(std::unordered_map<int, std::set<long long int>>& sets, int s) {
    if (sets[s].size() != 0) {
        for (std::set<long long int>::iterator it = sets[s].begin(); it != sets[s].end(); ++it) {
            printf("%lld ", *it);
        }
        printf("\n");
    } else {
        printf("-1\n");
    }
}

void Listsetof(std::unordered_map<long long int, std::set<int>>& numbers_in_sets, long long int e) {
    if (numbers_in_sets[e].size() != 0) {
        for (std::set<int>::iterator it = numbers_in_sets[e].begin(); it != numbers_in_sets[e].end(); ++it) {
            printf("%d ", *it);
        }
        printf("\n");
    } else {
        printf("-1\n");
    }
}

int main() {
    long long int n;
    int m, k;

    scanf("%lld %d %d", &n, &m, &k);

    std::unordered_map<int, std::set<long long int>> sets;
    std::unordered_map<long long int, std::set<int>> numbers_in_sets;

    for (int i = 0; i < k; ++i) {
        char command[12];

        scanf("\n%s", command);

        long long int e;
        int s;

        if (strcmp(command, "ADD") == 0) {
            scanf("%lld %d", &e, &s);

            Add(sets, numbers_in_sets, e, s);
        } else if (strcmp(command, "DELETE") == 0) {
            scanf("%lld %d", &e, &s);

            Delete(sets, numbers_in_sets, e, s);
        } else if (strcmp(command, "CLEAR") == 0) {
            scanf("%d", &s);

            Clear(sets, numbers_in_sets, s);
        } else if (strcmp(command, "LISTSET") == 0) {
            scanf("%d", &s);

            Listset(sets, s);
        } else {
            scanf("%lld", &e);

            Listsetof(numbers_in_sets, e);
        }
    }

    return 0;
}
