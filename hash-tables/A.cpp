#include <iostream>
#include <stdio.h>
#include <vector>

const int size = 100000;

struct Var {
    int val = 0;
    std::string var;
    Var* next = nullptr;

    Var(int val, const std::string& var, Var* next): val(val), var(var), next(next) {}
};

int hash(const std::string& var) {
    const int p = 31;

    int ans = 0, p_pow = 1;
    for (size_t i = 0; i < var.size(); ++i) {
        ans = (ans + (var[i] - 'a' + 1) * p_pow) % size;
        p_pow = p_pow * p % size;
    }

    return ans;
}

int change_table(std::vector<Var*>& hash_table, int h, int val, const std::string& var) {
    int new_val = 0;

    if (hash_table[h] == nullptr) {
        hash_table[h] = new Var(val, var, nullptr);
        new_val = val;
    } else {
        Var* ptr = hash_table[h];

        while (ptr != nullptr) {
            if (ptr->var == var) {
                ptr->val += val;
                new_val = ptr->val;
                break;
            }

            if (ptr->next != nullptr) {
                ptr = ptr->next;
            } else {
                ptr->next = new Var(val, var, nullptr);
                new_val = val;
                break;
            }
        }
    }

    return new_val;
}

int main()
{
    std::vector<Var*> hash_table(size, nullptr);

    std::string var;
    while (std::cin >> var) {
        int val;
        scanf("%d", &val);

        int h = hash(var);
        printf("%d\n", change_table(hash_table, h, val, var));
    }

    return 0;
}
