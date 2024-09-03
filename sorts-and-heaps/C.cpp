#include <iostream>
#include <stdio.h>
#include <vector>
 
int partition(std::vector<int>& a, int left, int right) {
    if (left != right) {
        std::swap(a[left + rand() % (right - left)], a[right]);
    }
 
    int elem = a[right], j = left - 1;
 
    for (int i = left; i <= right; i++) {
        if (a[i] <= elem) {
            j++;
            std::swap(a[j], a[i]);
        }
    }
 
    return j;
}
 
int kth(std::vector<int>& a, int n, int k) {
    int left = 0, right = n - 1;
 
    while (true) {
        int pos = partition(a, left, right);
 
        if (pos < k) {
            left = pos + 1;
        } else if (pos > k) {
            right = pos - 1;
        } else {
            return a[k];
        }
    }
}
 
int main() {
    int n, k;
    std::vector<int> a;
 
    scanf("%d %d", &n, &k);
 
    for (int i = 0; i < n; ++i) {
        int elem;
        scanf("%d", &elem);
        a.push_back(elem);
    }
 
    printf("%d", kth(a, n, k));
 
    return 0;
}