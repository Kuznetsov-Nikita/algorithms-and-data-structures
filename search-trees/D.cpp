#include <fstream>
 
struct Cut {
    long long int prior, cnt, length;
    long long int sqr_sum;
 
    Cut* left;
    Cut* right;
 
    Cut(long long int length): prior(rand()), cnt(1), length(length), sqr_sum(length * length), left(nullptr), right(nullptr) {}
};
 
long long int get_cnt(Cut* tree) {
    if (tree != nullptr) {
        return tree->cnt;
    } else {
        return 0;
    }
}
 
void update_cnt(Cut* tree) {
    if (tree != nullptr) {
        tree->cnt = 1 + get_cnt(tree->left) + get_cnt(tree->right);
    }
}
 
long long int get_sqr_sum(Cut* tree) {
    if (tree != nullptr) {
        return tree->sqr_sum;
    } else {
        return 0;
    }
}
 
void update_sqr_sum(Cut* tree) {
    if (tree != nullptr) {
        tree->sqr_sum = tree->length * tree->length + get_sqr_sum(tree->left) + get_sqr_sum(tree->right);
    }
}
 
Cut* merge(Cut* tree1, Cut* tree2) {
    if (tree1 == nullptr) {
        return tree2;
    }
    if (tree2 == nullptr) {
        return tree1;
    }
 
    if (tree1->prior > tree2->prior) {
        tree1->right = merge(tree1->right, tree2);
 
        update_cnt(tree1);
        update_sqr_sum(tree1);
 
        return tree1;
    } else {
        tree2->left = merge(tree1, tree2->left);
 
        update_cnt(tree2);
        update_sqr_sum(tree2);
 
        return tree2;
    }
}
 
void split(Cut* tree, Cut* &tree1, Cut* &tree2, long long int key) {
    if (tree != nullptr) {
        if (get_cnt(tree->left) < key) {
            split(tree->right, tree->right, tree2, key - get_cnt(tree->left) - 1);
            tree1 = tree;
        } else {
            split(tree->left, tree1, tree->left, key);
            tree2 = tree;
        }
 
        update_cnt(tree);
        update_sqr_sum(tree);
    } else {
        tree1 = tree2 = nullptr;
    }
}
 
Cut* insert(Cut* tree, long long int value, long long int pos) {
    Cut* tree1;
    Cut* tree2;
    Cut*  new_tree = new Cut(value);
 
    split(tree, tree1, tree2, pos);
 
    return merge(merge(tree1, new_tree), tree2);
}
 
Cut* erase(Cut* &tree, long long int pos) {
    Cut* tree1;
    Cut* tree2;
    Cut* tree3;
    Cut* tree4;
 
    split(tree, tree1, tree2, pos);
    split(tree2, tree3, tree4, 1);
 
    tree = merge(tree1, tree4);
 
    delete tree3;
 
    return tree;
}
 
long long int get_length(Cut* &tree, long long int pos) {
    if (tree != nullptr) {
        int key = get_cnt(tree->left);
 
        if (pos < key){
            return get_length(tree->left, pos);
        } else if (pos == key) {
            return tree->length;
        } else {
            return get_length(tree->right, pos - key - 1);
        }
    } else {
        return 0;
    }
}
 
void inc_length(Cut* tree, long long int length, long long int pos) {
    if (tree != nullptr) {
        int key = get_cnt(tree->left);
 
        if (pos < key){
            inc_length(tree->left, length, pos);
            update_sqr_sum(tree);
        } else if (pos == key) {
            tree->sqr_sum -= tree->length * tree->length;
            tree->length += length;
            tree->sqr_sum += tree->length * tree->length;
        } else {
            inc_length(tree->right, length, pos - key - 1);
            update_sqr_sum(tree);
        }
    }
}
 
long long int get_tree_sqr_sum(Cut* tree) {
    return tree->sqr_sum;
}
 
 
void bankruptcy(Cut* &tree, long long int v, long long int* n) {
    long long int length = get_length(tree, v);
 
    tree = erase(tree, v);
 
    if (v == 0) {
        inc_length(tree, length, 0);
    } else if (v == *n - 1) {
        inc_length(tree, length, v - 1);
    } else {
        inc_length(tree, length / 2, v - 1);
        inc_length(tree, length - length / 2, v);
    }
 
    *n -= 1;
}
 
void separation(Cut* &tree, long long int v, long long int* n) {
    long long int length = get_length(tree, v);
 
    tree = erase(tree, v);
 
    tree = insert(tree, length / 2, v);
    tree = insert(tree, length - length / 2, v + 1);
 
    *n += 1;
}
 
 
int main() {
    std::ifstream f_input("river.in");
    std::ofstream f_output("river.out");
 
    long long int n, p;
 
    f_input >> n >> p;
 
    Cut* tree = nullptr;
 
    for (int i = 0; i < n; ++i) {
        long long int a;
 
        f_input >> a;
 
        Cut* new_tree = new Cut(a);
        tree = merge(tree, new_tree);
    }
 
    long long int k;
 
    f_input >> k;
 
    f_output << get_tree_sqr_sum(tree) << '\n';
 
    for (int i = 0; i < k; ++i) {
        long long int e, v;
 
        f_input >> e >> v;
 
        if (e == 1) {
            bankruptcy(tree, v - 1, &n);
        } else {
            separation(tree, v - 1, &n);
        }
 
        f_output << get_tree_sqr_sum(tree) << '\n';
    }
 
    f_input.close();
    f_output.close();
 
    return 0;
}