#include <iostream>
#include <functional>
#include <vector>

const int size = 400000;

struct Elem {
    int key, val;
    Elem* next = nullptr;

    Elem(int key, int val, Elem* next): key(key), val(val), next(next) {}
};

int hash(int n) {
    return std::hash<int>{}(n) % size;
}

int swap(std::vector<Elem*>& hash_table, int h1, int h2, int a, int b) {
    int pos1 = a, pos2 = b;

    if (a != b) {
        if (hash_table[h1] == nullptr) {
            hash_table[h1] = new Elem(a, a, nullptr);
        } else {
            Elem* ptr = hash_table[h1];

            while (ptr != nullptr) {
                if (ptr->key == a) {
                    pos1 = ptr->val;
                    break;
                }

                if (ptr->next != nullptr) {
                    ptr = ptr->next;
                } else {
                    ptr->next = new Elem(a, a, nullptr);
                    break;
                }
            }
        }

        if (hash_table[h2] == nullptr) {
            hash_table[h2] = new Elem(b, b, nullptr);
        } else {
            Elem* ptr = hash_table[h2];

            while (ptr != nullptr) {
                if (ptr->key == b) {
                    pos2 = ptr->val;

                    break;
                }

                if (ptr->next != nullptr) {
                    ptr = ptr->next;
                } else {
                    ptr->next = new Elem(b, b, nullptr);
                    break;
                }
            }
        }

        Elem* ptr = hash_table[h1];

        while (ptr->key != a) {
            ptr = ptr->next;
        }
        ptr->val = pos2;

        ptr = hash_table[h2];

        while (ptr->key != b) {
            ptr = ptr->next;
        }
        ptr->val = pos1;
    }

    return std::abs(pos1 - pos2);
}

int main()
{
    std::vector<Elem*> hash_table(size, nullptr);

    int n;
    std::cin >> n;

    for (int i = 0; i < n; ++i) {
        int a, b;
        std::cin >> a >> b;

        int h1 = hash(a);
        int h2 = hash(b);

        std:: cout << swap(hash_table, h1, h2, a, b) << '\n';
    }

    return 0;
}
