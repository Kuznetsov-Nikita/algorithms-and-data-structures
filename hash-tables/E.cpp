#include <fstream>
#include <vector>

const int size = 100000;

struct Elem {
    std::string key, val;
    Elem* next = nullptr;

    Elem(const std::string& key, const std::string& val, Elem* next): key(key), val(val), next(next) {}
};

int hash(const std::string& key) {
    const int p = 53;

    int ans = 0, p_pow = 1;
    for (size_t i = 0; i < key.size(); ++i) {
        ans = (ans + (key[i] - 'A' + 1) * p_pow) % size;
        p_pow = p_pow * p % size;
    }

    return ans;
}

void put(std::vector<Elem*>& hash_table, int h, const std::string& key, const std::string& val) {
    if (hash_table[h] == nullptr) {
        hash_table[h] = new Elem(key, val, nullptr);
    } else {
        Elem* ptr = hash_table[h];

        while (ptr != nullptr) {
            if (ptr->key == key) {
                ptr->val = val;
                break;
            }

            if (ptr->next != nullptr) {
                ptr = ptr->next;
            } else {
                ptr->next = new Elem(key, val, nullptr);
                break;
            }
        }
    }
}

void del(std::vector<Elem*>& hash_table, int h, const std::string& key) {
    if (hash_table[h] != nullptr) {
        Elem* ptr = hash_table[h];
        Elem* parent_ptr = nullptr;

        while (ptr != nullptr) {
            if (ptr->key == key) {
                if (parent_ptr != nullptr) {
                    parent_ptr->next = ptr->next;
                } else {
                    hash_table[h] = ptr->next;
                }

                delete ptr;

                break;
            }

            ptr = ptr->next;
            parent_ptr = ptr;
        }
    }
}

std::string get(std::vector<Elem*>& hash_table, int h, const std::string& key) {
    std::string val = "none";

    Elem* ptr = hash_table[h];

    while (ptr != nullptr) {
        if (ptr->key == key) {
            val = ptr->val;
            break;
        }

        ptr = ptr->next;
    }

    return val;
}

int main()
{
    std::ifstream f_input("map.in");
    std::ofstream f_output("map.out");

    std::vector<Elem*> hash_table(size, nullptr);

    std::string command;
    while (f_input >> command) {
        std::string key;
        f_input >> key;

        int h = hash(key);

        if (command == "put") {
            std::string val;
            f_input >> val;

            put(hash_table, h, key, val);
        } else if (command == "delete") {
            del(hash_table, h, key);
        } else if (command == "get") {
            f_output << get(hash_table, h, key) << '\n';
        }
    }

    return 0;
}
