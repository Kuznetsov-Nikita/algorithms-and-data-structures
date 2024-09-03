#include <iostream>
 
int main() {
    long long int n, p, q, maximum = 0;
    int a[200000];
 
    std::cin >> n >> p >> q;
 
    for (int i = 0; i < n; ++i) {
        std::cin >> a[i];
 
        if (a[i] > maximum) {
            maximum = a[i];
        }
    }
 
    long long int min_count = maximum / p;
    long long int max_count = maximum / q + (long long int)(maximum % q != 0);
    long long int count, elem;
 
    while (max_count - min_count > 1) {
        count = (max_count + min_count) / 2;
 
        elem = 0;
        for (int i = 0; i < n; ++i) {
            if (p != q) {
                if (a[i] <= q * count) {
                    elem += 0;
                } else {
                    elem += (a[i] - q * count) / (p - q) + (long long int)((a[i] - q * count) % (p - q) != 0);
                }
            } else {
                count = max_count;
                break;
            }
        }
 
        if (elem <= count) {
            max_count = count;
        } else {
            min_count = count;
        }
    }
 
    std::cout << max_count;
 
    return 0;
}