#include <iostream>
#include <string>
 
typedef struct {
    int max_tree[100001];
    int min_tree[100001];
    int size;
} Heap;
 
void makenull(Heap* h) {
    h->size = 0;
}
 
void sift_up_max(Heap* h, int i) {
    while (i > 1 && h->max_tree[i] > h->max_tree[i / 2]) {
        std::swap(h->max_tree[i], h->max_tree[i / 2]);
        i /= 2;
    }
}
 
void sift_up_min(Heap* h, int i) {
    while (i > 1 && h->min_tree[i] < h->min_tree[i / 2]) {
        std::swap(h->min_tree[i], h->min_tree[i / 2]);
        i /= 2;
    }
}
 
void sift_down_max(Heap* h, int i) {
    while (2 * i <= h->size) {
        int j = -1;
 
        if (h->max_tree[2 * i] > h->max_tree[i]) {
            j = 2 * i;
        }
        if (2 * i + 1 <= h->size && h->max_tree[2 * i + 1] > h->max_tree[i] && (j == -1 || h->max_tree[2 * i] < h->max_tree[2 * i + 1])) {
            j = 2 * i + 1;
        }
 
        if (j == -1) {
            break;
        } else {
            std::swap(h->max_tree[i], h->max_tree[j]);
            i = j;
        }
    }
}
 
void sift_down_min(Heap* h, int i) {
    while (2 * i <= h->size) {
        int j = -1;
 
        if (h->min_tree[2 * i] < h->min_tree[i]) {
            j = 2 * i;
        }
        if (2 * i + 1 <= h->size && h->min_tree[2 * i + 1] < h->min_tree[i] && (j == -1 || h->min_tree[2 * i] > h->min_tree[2 * i + 1])) {
            j = 2 * i + 1;
        }
 
        if (j == -1) {
            break;
        } else {
            std::swap(h->min_tree[i], h->min_tree[j]);
            i = j;
        }
    }
}
 
void insert(Heap* h, int value) {
    int i = h->size + 1;
    h->size++;
    h->max_tree[h->size] = value;
    h->min_tree[h->size] = value;
 
    sift_up_max(h, i);
    sift_up_min(h, i);
}
 
int get_max(Heap* h) {
    int result = h->max_tree[1];
    h->max_tree[1] = h->max_tree[h->size];
 
    int i = 1;
    while (h->min_tree[i] != result) {
        i++;
    }
 
    h->min_tree[i] = 1;
    sift_up_min(h, i);
    h->min_tree[1] = h->min_tree[h->size];
 
    h->size--;
 
    sift_down_max(h, 1);
    sift_down_min(h, 1);
 
    return result;
}
 
int get_min(Heap* h) {
    int result = h->min_tree[1];
    h->min_tree[1] = h->min_tree[h->size];
 
    int i = 1;
    while (h->max_tree[i] != result) {
        i++;
    }
 
    h->max_tree[i] = 2147483647;
    sift_up_max(h, i);
    h->max_tree[1] = h->max_tree[h->size];
 
    h->size--;
 
    sift_down_min(h, 1);
    sift_down_max(h, 1);
 
    return result;
}
 
int main() {
    Heap h;
    int n;
 
    std::cin >> n;
 
    makenull(&h);
    std::string t;
    std::getline(std::cin, t);
 
    for (int i = 0; i < n; ++i) {
        std::string command;
        std::getline(std::cin, command);
 
        if (command.find("GetMin") != -1) {
            std::cout << get_min(&h) << '\n';
        } else if (command.find("GetMax") != -1) {
            std::cout << get_max(&h) << '\n';
        } else {
            int value = 0;
 
            for (int j = command.find('(') + 1; command[j] != ')'; ++j) {
                if (command[j] >= '0' && command[j] <= '9') {
                    value = value * 10 + command[j] - '0';
                }
            }
 
            insert(&h, value);
        }
    }
 
    return 0;
}