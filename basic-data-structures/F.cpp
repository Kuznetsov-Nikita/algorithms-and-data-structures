#include <fstream>
 
long long int merge(int a[],int temp[], int left, int middle, int right) {
    int i = left, j = middle, k = left;
    long long int inverse_count = 0;
 
    while(i <= middle - 1 && j <= right) {
        if(a[i] <= a[j]) {
            temp[k] = a[i];
            k++;
            i++;
        } else {
            temp[k] = a[j];
            k++;
            j++;
 
            inverse_count += middle - i;
        }
    }
 
    while(i <= middle - 1) {
        temp[k] = a[i];
        k++;
        i++;
    }
 
    while(j <= right) {
        temp[k] = a[j];
        k++;
        j++;
    }
 
    for(i = left; i <= right; ++i) {
        a[i] = temp[i];
    }
 
    return inverse_count;
}
 
long long int merge_sort(int a[], int temp[], int left, int right) {
    long long int inverse_count = 0;
 
    if (right > left) {
        int middle = (right + left) / 2;
 
        inverse_count = merge_sort(a, temp, left, middle);
        inverse_count += merge_sort(a, temp, middle + 1, right);
 
        inverse_count += merge(a, temp, left, middle + 1, right);
    }
 
    return inverse_count;
}
 
int main() {
    std::ifstream f_input("inverse.in");
    std::ofstream f_output("inverse.out");
 
    int n;
    int a[1000000];
 
    f_input >> n;
 
    for (int i = 0; i < n; ++i) {
        f_input >> a[i];
    }
 
    int* temp = (int*)malloc(sizeof(int) * n);
    f_output << merge_sort(a, temp, 0, n - 1) << '\0';
 
    f_input.close();
    f_output.close();
 
    return 0;
}