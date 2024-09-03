#include <iostream>
 
typedef struct {
    int tree[501];
    int size;
} Heap;
 
int cmp (const void* a, const void* b)
{
  return (*(int*)a - *(int*)b);
}
 
void makenull(Heap* h) {
    h->size = 0;
    h->tree[0] = 0;
}
 
void sift_up(Heap* h, int i) {
    while (i > 1 && h->tree[i] > h->tree[i / 2]) {
        std::swap(h->tree[i], h->tree[i / 2]);
        i /= 2;
    }
}
 
void sift_down(Heap* h, int i) {
    while (2 * i <= h->size) {
        int j = -1;
 
        if (h->tree[2 * i] > h->tree[i]) {
            j = 2 * i;
        }
        if (2 * i + 1 <= h->size && h->tree[2 * i + 1] > h->tree[i] && (j == -1 || h->tree[2 * i] < h->tree[2 * i + 1])) {
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
 
void insert(Heap* h, int value) {
    int i = h->size + 1;
    h->size++;
    h->tree[h->size] = value;
 
    sift_up(h, i);
}
 
int get_max(Heap* h) {
    return h->tree[1];
}
 
void extract_max(Heap* h) {
    h->tree[1] = h->tree[h->size];
    h->size--;
 
    sift_down(h, 1);
}
 
int main() {
    Heap h;
    int n, k;
 
    std::cin >> n >> k;
 
    makenull(&h);
 
    for (int i = 0; i < n; ++i) {
        int a;
        std::cin >> a;
 
        if (h.size < k) {
            insert(&h, a);
        } else if (h.size >= k && get_max(&h) > a) {
            extract_max(&h);
            insert(&h, a);
        }
    }
 
    qsort(h.tree, k + 1, sizeof(int), cmp);
 
    for (int i = 1; i <= k; ++i) {
        std::cout << h.tree[i] << ' ';
    }
 
    return 0;
}