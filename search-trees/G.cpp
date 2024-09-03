#include <stdio.h>
#include <set>
#include <vector>
#include <utility>
#include <algorithm>
 
struct Cut {
    unsigned int beg, end, lenght;
 
    Cut(unsigned int beg, unsigned int end): beg(beg), end(end), lenght(end - beg) {}
};
 
bool operator<(const Cut& cut_1, const Cut& cut_2) {
    return (cut_1.lenght < cut_2.lenght) || (cut_1.lenght == cut_2.lenght && cut_1.beg < cut_2.beg);
}
 
int main() {
    unsigned int n, y, x;
    scanf("%u %u %u", &n, &y, &x);
 
    std::vector<std::pair<unsigned int, unsigned int>> y_1;
    std::vector<std::pair<unsigned int, unsigned int>> y_2;
 
    for (unsigned int i = 0; i < n; ++i) {
        unsigned int xi, yi_1, yi_2;
        scanf("%u %u %u", &xi, &yi_1, &yi_2);
 
        y_1.push_back(std::pair<int, int> (yi_1, xi));
        y_2.push_back(std::pair<int, int> (yi_2, xi));
    }
 
    std::sort(y_1.begin(), y_1.end());
    std::sort(y_2.begin(), y_2.end());
 
    std::multiset<unsigned int> retails;
    std::set<Cut> cuts;
 
    retails.insert(x);
    cuts.insert(Cut(0, x));
 
    unsigned int i_y1 = 0, i_y2 = 0;
 
    for (unsigned int i = 0; i < y + 1; ++i) {
        while (i_y1 < y_1.size() && y_1[i_y1].first == i) {
            retails.insert(y_1[i_y1].second);
 
            std::multiset<unsigned int>::iterator it = retails.find(y_1[i_y1].second);
 
            unsigned int beg = 0;
            if (it != retails.begin()) {
                --it;
                beg = *it;
                ++it;
            }
            ++it;
            unsigned int end = *it;
            --it;
 
            cuts.erase(Cut(beg, end));
            cuts.insert(Cut(beg, y_1[i_y1].second));
            cuts.insert(Cut(y_1[i_y1].second, end));
 
            ++i_y1;
        }
 
        printf("%u\n", cuts.rbegin()->lenght);
 
        while (i_y2 < y_2.size() && y_2[i_y2].first == i) {
            std::multiset<unsigned int>::iterator it = retails.find(y_2[i_y2].second);
 
            unsigned int beg = 0;
            if (it != retails.begin()) {
                --it;
                beg = *it;
                ++it;
            }
            ++it;
            unsigned int end = *it;
            --it;
 
            cuts.erase(Cut(beg, y_2[i_y2].second));
            cuts.erase(Cut(y_2[i_y2].second, end));
            cuts.insert(Cut(beg, end));
 
            retails.erase(it);
            ++i_y2;
        }
    }
 
    return 0;
}