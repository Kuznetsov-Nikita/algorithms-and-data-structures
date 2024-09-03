#include <cstring>
#include <iostream>
#include <map>
#include <vector>

template <typename T>
class FastAllocator {
public:
    const std::vector<int> fixed_size = {1, 2, 4, 8};
    using value_type = T;
    using pointer = T*;
    using const_pointer = const T*;
    using reference = T&;
    using const_reference = const T&;

    template <class U>
    struct rebind {
        using other = FastAllocator<U>;
    };

public:
    FastAllocator() = default;

    template <class U>
    FastAllocator<T>(const FastAllocator<U>&) {}

    template <class U>
    FastAllocator<T>& operator=(const FastAllocator<U>&) {
        return *this;
    }

    T* allocate(size_t n) {
        return reinterpret_cast<T*>(::operator new(n * sizeof(T)));
    }

    void deallocate(T* ptr, size_t) {
        ::operator delete(ptr);
    }

    template <typename ...Args>
    void construct(T* ptr, const Args& ...args) {
        new (ptr) T(args...);
    }

    void destroy(T* ptr) {
        ptr->~T();
    }

    bool operator==(const FastAllocator<T>&) {
        return true;
    }

    bool operator!=(const FastAllocator<T>& another) {
        return !(*this == another);
    }

    ~FastAllocator() {

    }
};

struct node {
    int len, link;
    int to[26];

    node(int len = 0, int link = -1): len(len), link(link) {
        memset(to, -1, sizeof(to));
    }
};

void add(std::vector<node, FastAllocator<node>>& suff_automat, int& sz, int& last, char c) {
    ++sz;
    int curr = sz - 1;
    int p = last;

    while (p != -1 && suff_automat[p].to[c - 'a'] == -1) {
        suff_automat[p].to[c - 'a'] = curr;
        p = suff_automat[p].link;
    }

    if (p == -1) {
        suff_automat[curr].link = 0;
        last = curr;
        return;
    }

    int q = suff_automat[p].to[c - 'a'];
    if (suff_automat[q].len == suff_automat[p].len + 1) {
        suff_automat[curr].link = q;
        last = curr;
        return;
    }

    ++sz;
    int clone = sz - 1;
    suff_automat[clone].len = suff_automat[p].len + 1;
    while (p != -1 && suff_automat[p].to[c - 'a'] == q) {
        suff_automat[p].to[c - 'a'] = clone;
        p = suff_automat[p].link;
    }
    suff_automat[clone].link = suff_automat[q].link;
    memcpy(suff_automat[clone].to, suff_automat[q].to, sizeof(suff_automat[clone].to));
    suff_automat[q].link = clone;
    suff_automat[curr].link = clone;
    last = curr;
}

bool find(std::vector<node, FastAllocator<node>>& suff_automat, const char* s, int v, int i) {
    if (i >= strlen(s)) {
        return true;
    }
    if (suff_automat[v].to[tolower(s[i]) - 'a'] == -1) {
        return false;
    }

    return find(suff_automat, s, suff_automat[v].to[tolower(s[i]) - 'a'], i + 1);
}

int main() {
    std::vector<node, FastAllocator<node>> suff_automat (200000, node());
    int sz = 1;
    int last = 0;

    char command = '\0';
    while ((command = getchar()) != EOF) {
        char s[100000];
        scanf("%s", s);

        if (command == 'A') {
            for (int i = 0; i < strlen(s); ++i) {
                add(suff_automat, sz, last, tolower(s[i]));
            }
        } else {
            if (find(suff_automat, s, 0, 0)) {
                printf("YES\n");
            } else {
                printf("NO\n");
            }
        }

        getchar();
    }

    return 0;
}