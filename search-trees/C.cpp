#include <iostream>
 
struct Node {
    long long int prior, cnt, key;
 
    Node* left;
    Node* right;
 
    Node(long long int key): prior(rand()), cnt(1), key(key), left(nullptr), right(nullptr) {}
};
 
long long int get_cnt(Node* tree) {
    if (tree != nullptr) {
        return tree->cnt;
    } else {
        return 0;
    }
}
 
void update_cnt(Node* tree) {
    if (tree != nullptr) {
        tree->cnt = 1 + get_cnt(tree->left) + get_cnt(tree->right);
    }
}
 
Node* merge(Node* tree1, Node* tree2) {
    if (tree1 == nullptr) {
        return tree2;
    }
    if (tree2 == nullptr) {
        return tree1;
    }
 
    if (tree1->prior > tree2->prior) {
        tree1->right = merge(tree1->right, tree2);
 
        update_cnt(tree1);
 
        return tree1;
    } else {
        tree2->left = merge(tree1, tree2->left);
 
        update_cnt(tree2);
 
        return tree2;
    }
}
 
void insertion_split(Node* tree, Node* &tree1, Node* &tree2, long long int key) {
    if (tree != nullptr) {
        if (tree->key < key) {
            insertion_split(tree->left, tree1, tree->left, key);
            tree2 = tree;
        } else {
            insertion_split(tree->right, tree->right, tree2, key);
            tree1 = tree;
        }
 
        update_cnt(tree);
    } else {
        tree1 = tree2 = nullptr;
    }
}
 
void erasion_split(Node* tree, Node* &tree1, Node* &tree2, long long int key) {
    if (tree != nullptr) {
        if (tree->key > key) {
            erasion_split(tree->right, tree->right, tree2, key);
            tree1 = tree;
        } else {
            erasion_split(tree->left, tree1, tree->left, key);
            tree2 = tree;
        }
 
        update_cnt(tree);
    } else {
        tree1 = tree2 = nullptr;
    }
}
 
long long int find_kth(Node* tree, long long int k) {
    Node* cur = tree;
 
    while (cur != nullptr) {
        long long int cnt_left = get_cnt(cur->left);
 
        if (cnt_left + 1 == k) {
            return cur->key;
        }
 
        cur = (cnt_left + 1 > k) ? cur->left : cur->right;
        if (cnt_left + 1 < k) {
            k -= cnt_left + 1;
        }
    }
 
    return 0;
}
 
Node* insert(Node* tree, long long int key) {
    Node* tree1;
    Node* tree2;
    Node*  new_tree = new Node(key);
 
    insertion_split(tree, tree1, tree2, key);
 
    return merge(merge(tree1, new_tree), tree2);
}
 
Node* erase(Node* &tree, long long int key) {
    Node* tree1;
    Node* tree2;
    Node* tree3;
    Node* tree4;
 
    erasion_split(tree, tree1, tree2, key);
    erasion_split(tree2, tree3, tree4, key - 1);
 
    tree = merge(tree1, tree4);
 
    delete tree3;
 
    return tree;
}
 
int main() {
    std::ios_base::sync_with_stdio(0);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
 
    Node* tree = nullptr;
 
    long long int n;
    std::cin >> n;
 
    for (long long int i = 0; i < n; ++i) {
        long long int c, k;
        std::cin >> c >> k;
 
        if (c == 1) {
            tree = insert(tree, k);
        } else if (c == -1) {
            tree = erase(tree, k);
        } else {
            std::cout << find_kth(tree, k) << '\n';
        }
    }
 
    return 0;
}