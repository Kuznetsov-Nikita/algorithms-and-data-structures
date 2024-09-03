#include <iostream>
#include <vector>
#include <stdio.h>
 
typedef struct Elem {
    long long int value;
    int number;
 
    Elem(long long int value, int number): value(value), number(number) {}
} Elem;
 
typedef struct {
    std::vector<Elem> tree;
    int size;
} Heap;
 
void makenull(Heap* h) {
    h->size = 0;
    h->tree.push_back(Elem(0, 0));
}
 
void sift_up(Heap* h, int i) {
    while (i > 1 && h->tree[i].value < h->tree[i / 2].value) {
        std::swap(h->tree[i], h->tree[i / 2]);
        i /= 2;
    }
}
 
void sift_down(Heap* h, int i) {
    while (2 * i <= h->size) {
        int j = -1;
 
        if (h->tree[2 * i].value < h->tree[i].value) {
            j = 2 * i;
        }
        if (2 * i + 1 <= h->size && h->tree[2 * i + 1].value < h->tree[i].value && (j == -1 || h->tree[2 * i].value > h->tree[2 * i + 1].value)) {
            j = 2 * i + 1;
        }
 
        if (j == -1) {
            break;
        } else {
            std::swap(h->tree[i], h->tree[j]);
            i = j;
        }
    }
}
 
void insert(Heap* h, int value, int number) {
    int i = h->size + 1;
    h->size++;
    h->tree.push_back(Elem(value, number));
 
    sift_up(h, i);
}
 
long long int get_min(Heap* h) {
    return h->tree[1].value;
}
 
void extract_min(Heap* h) {
    h->tree[1] = h->tree[h->size];
    h->tree.pop_back();
    h->size--;
 
    sift_down(h, 1);
}
 
void decrease_key(Heap* h, int key, int delta) {
    int i = 1;
    while (h->tree[i].number != key) {
        i++;
    }
 
    h->tree[i].value -= delta;
 
    sift_up(h, i);
}
 
int main() {
    Heap h;
    int q;
 
    makenull(&h);
 
    scanf("%d", &q);
 
    for (int i = 1; i <= q; ++i) {
        char command[15];
        scanf("\n%s", command);
 
        if (command[0] == 'i') {
            int value;
            scanf("%lld", &value);
            insert(&h, value, i);
        } else if (command[0] == 'g') {
            printf("%lld\n", get_min(&h));
        } else if (command[0] == 'e') {
            extract_min(&h);
        } else {
            int j, delta;
            scanf("%d %d", &j, &delta);
            decrease_key(&h, j, delta);
        }
    }
 
    return 0;
}