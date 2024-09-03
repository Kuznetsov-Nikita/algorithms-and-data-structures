#include <iostream>
#include <map>
#include <string>
#include <vector>

struct node {
    long long int len, link, cnt;
    std::map<char, long long int> to;

    node(long long int len = 0, long long int link = -1): len(len), link(link), cnt(0) {}

    long long int& next(char c) {
        if (to.count(c) == 0) {
            to[c] = -1;
        }
        return to[c];
    }
};

void add(std::vector<node>& suff_automat, long long int& last, long long int& cnt, char c) {
    suff_automat.push_back(node());
    long long int curr = suff_automat.size() - 1;
    long long int p = last;

    while (p != -1 && suff_automat[p].next(c) == -1) {
        suff_automat[p].to[c] = curr;
        suff_automat[curr].cnt += suff_automat[p].cnt;
        p = suff_automat[p].link;
    }
    cnt += suff_automat[curr].cnt;

    if (p == -1) {
        suff_automat[curr].link = 0;
        last = curr;
        return;
    }

    long long int q = suff_automat[p].to[c];
    if (suff_automat[q].len == suff_automat[p].len + 1) {
        suff_automat[curr].link = q;
        last = curr;
        return;
    }

    suff_automat.push_back(node());
    long long int clone = suff_automat.size() - 1;
    suff_automat[clone].len = suff_automat[p].len + 1;
    cnt -= suff_automat[q].cnt;
    while (p != -1 && suff_automat[p].next(c) == q) {
        suff_automat[p].to[c] = clone;
        suff_automat[clone].cnt += suff_automat[p].cnt;
        suff_automat[q].cnt -= suff_automat[p].cnt;
        p = suff_automat[p].link;
    }
    cnt += suff_automat[q].cnt + suff_automat[clone].cnt;

    suff_automat[clone].link = suff_automat[q].link;
    suff_automat[clone].to = suff_automat[q].to;
    suff_automat[q].link = clone;
    suff_automat[curr].link = clone;
    last = curr;
}

int main() {
    std::string s;
    std::cin >> s;

    std::vector<node> suff_automat;
    suff_automat.push_back(node());
    suff_automat[0].cnt = 1;

    long long int last = 0;
    long long int cnt = 0;
    for (long long int i = 0; i < s.size(); ++i) {
        add(suff_automat, last, cnt, s[i]);
        std::cout << cnt << '\n';
    }

    return 0;
}