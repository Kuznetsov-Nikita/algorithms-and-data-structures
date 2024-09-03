#include <stdio.h>
 
void lsd_sort(unsigned long long int a[], int n) {
    unsigned long long int* b = new unsigned long long int[1000000];
 
    for (int byte_number = 0; byte_number < sizeof(unsigned long long int); ++byte_number) {
        unsigned long long int* id_bytes_cnt = new unsigned long long int[256];
 
        for (int i = 0; i < 256; ++i) {
            id_bytes_cnt[i] = 0;
        }
 
        for (int i = 0; i < n; ++i) {
            int byte = (a[i] >> (byte_number * 8)) & 0xFF;
            id_bytes_cnt[byte]++;
        }
 
        unsigned long long int cnt = 0;
 
        for (int i = 0; i < 256; ++i) {
            unsigned long long int tmp = id_bytes_cnt[i];
            id_bytes_cnt[i] = cnt;
            cnt += tmp;
        }
 
        for (int i = 0; i < n; ++i) {
            int byte = (a[i] >> (byte_number * 8)) & 0xFF;
            b[id_bytes_cnt[byte]] = a[i];
            id_bytes_cnt[byte]++;
        }
 
        for (int i = 0; i < n; ++i) {
            a[i] = b[i];
        }
 
        delete[] id_bytes_cnt;
    }
 
    delete[] b;
}
 
int main() {
    int n;
    unsigned long long int* a = new unsigned long long int[1000000];
 
    scanf("%d", &n);
 
    for (int i = 0; i < n; ++i) {
        scanf("%llu", &a[i]);
    }
 
    lsd_sort(a, n);
 
    for (int i = 0; i < n; ++i) {
        printf("%llu ", a[i]);
    }
 
    delete[] a;
 
    return 0;
}