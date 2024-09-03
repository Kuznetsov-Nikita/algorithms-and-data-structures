#include <iostream>
#include <vector>
 
typedef struct Border {
    int pos;
    int type;
 
    Border(int pos, int type): pos(pos), type(type) {}
} Border;
 
void quick_sort(std::vector<Border>& borders, int left, int right) {
    int i = left, j = right;
    int middle = borders[left + (right - left) / 2].pos;
 
    while (i <= j) {
        while (borders[i].pos < middle) {
            i++;
        }
        while (borders[j].pos > middle) {
            j--;
        }
 
        if (i <= j) {
            std::swap(borders[i], borders[j]);
            i++;
            j--;
        }
    }
 
    if (left < j) {
        quick_sort(borders, left, j);
    }
    if (i < right) {
        quick_sort(borders, i, right);
    }
}
 
int main() {
    int n;
    std::vector<Border> borders;
 
    std::cin >> n;
 
    for (int i = 0; i < n; ++i) {
        int left, right;
 
        std::cin >> left >> right;
 
        borders.push_back(Border(left, 0));
        borders.push_back(Border(right, 1));
    }
 
    quick_sort(borders, 0, 2 * n - 1);
 
    int balance = 1, length = 0;
    for (int i = 1; i < 2 * n; ++i) {
        if (balance == 1) {
            length += borders[i].pos - borders[i - 1].pos;
        }
 
        if (borders[i].type == 0) {
            balance++;
        } else {
            balance--;
        }
    }
 
    std::cout << length;
 
    return 0;
}