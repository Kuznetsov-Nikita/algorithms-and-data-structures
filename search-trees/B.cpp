#include <iostream>
 
struct Node {
    int key;
    long long int sum;
 
    Node* left;
    Node* right;
    Node* parent;
 
    Node(int key, Node* left = nullptr, Node* right = nullptr): key(key), sum(key), left(left), right(right), parent(nullptr) {}
};
 
void update_sum(Node* node) {
    if (node != nullptr) {
        node->sum = node->key + ((node->left != nullptr) ? node->left->sum : 0) + ((node->right != nullptr) ? node->right->sum : 0);
    }
}
 
void rotate(Node* parent, Node* child) {
    Node* grandparent = parent->parent;
    if (grandparent != nullptr) {
        if (grandparent->left == parent) {
            grandparent->left = child;
        } else {
            grandparent->right = child;
        }
    }
 
    if (parent->left == child) {
        parent->left = child->right;
        child->right = parent;
    } else {
        parent->right = child->left;
        child->left = parent;
    }
 
    if (child->left != nullptr) {
        child->left->parent = child;
    }
    if (child->right != nullptr) {
        child->right->parent = child;
    }
 
    if (parent->left != nullptr) {
        parent->left->parent = parent;
    }
    if (parent->right != nullptr) {
        parent->right->parent = parent;
    }
 
    child->parent = grandparent;
}
 
Node* splay(Node* node) {
    if (node->parent == nullptr) {
        return node;
    }
 
    Node* parent = node->parent;
    Node* grandparent = node->parent->parent;
 
    if (grandparent == nullptr) {
        rotate(parent, node);
 
        update_sum(parent);
        update_sum(node);
        return node;
    } else {
        if ((grandparent->left == parent) == (parent->left == node)) {
            rotate(grandparent, parent);
            rotate(parent, node);
 
            update_sum(grandparent);
            update_sum(parent);
            update_sum(node);
        } else {
            rotate(parent, node);
            rotate(grandparent, node);
 
            update_sum(grandparent);
            update_sum(parent);
            update_sum(node);
        }
 
        return splay(node);
    }
}
 
Node* find(Node* node, int key) {
    if (node == nullptr) {
        return nullptr;
    }
 
    if (node->key == key) {
        return splay(node);
    }
 
    if (key < node->key && node->left != nullptr) {
        return find(node->left, key);
    }
    if (key > node->key && node->right != nullptr) {
        return find(node->right, key);
    }
 
    return splay(node);
}
 
int find_max(Node* node) {
    if (node->right == nullptr) {
        return node->key;
    } else {
        return find_max(node->right);
    }
}
 
Node* merge(Node* node1, Node* node2) {
    if (node1 == nullptr) {
        return node2;
    }
    if (node2 == nullptr) {
        return node1;
    }
 
    node2 = find(node2, node1->key);
    node2->left = node1;
    node1->parent = node2;
 
    update_sum(node2);
 
    return node2;
}
 
void split(Node* node, Node* &node1, Node* &node2, int key) {
    if (node == nullptr) {
        node1 = nullptr;
        node2 = nullptr;
    }
 
    node = find(node, key);
 
    if (node->key == key) {
        node1 = node->left;
        node2 = node->right;
 
        if (node1 != nullptr) {
            node1->parent = nullptr;
        }
        if (node2 != nullptr) {
            node2->parent = nullptr;
        }
    }
 
    if (node->key < key) {
        node2 = node->right;
        node->right = nullptr;
        if (node2 != nullptr) {
            node2->parent = nullptr;
        }
        node1 = node;
    } else {
        node1 = node->left;
        node->left = nullptr;
        if (node1 != nullptr) {
            node1->parent = nullptr;
        }
        node2 = node;
    }
 
    update_sum(node1);
    update_sum(node2);
}
 
Node* insert(Node* node, int key) {
    if (node == nullptr) {
        node = new Node(key);
    }
 
    node = find(node, key);
    if (node->key != key) {
        Node* node1 = nullptr;
        Node* node2 = nullptr;
        Node* new_node = new Node(key);
 
        split(node, node1, node2, key);
 
        node = merge(node1, merge(new_node, node2));
 
        if (node->left != nullptr) {
            node->left->parent = node;
        }
        if (node->right != nullptr) {
            node->right->parent = node;
        }
    }
 
    return node;
}
 
long long int get_sum(Node* node) {
    if (node == nullptr) {
        return 0;
    } else {
        return node->key + get_sum(node->left) + get_sum(node->right);
    }
}
 
long long int sum(Node* &node, int left, int right) {
    if (find_max(node) < left) {
        return 0;
    }
 
    Node* node1 = nullptr;
    Node* node2 = nullptr;
    Node* node3 = nullptr;
    Node* node4 = nullptr;
 
    if (node != nullptr) {
        node = find(node, left);
 
        if (node->key < left) {
            node2 = node->right;
            node->right = nullptr;
            if (node2 != nullptr) {
                node2->parent = nullptr;
            }
            node1 = node;
        } else {
            node1 = node->left;
            node->left = nullptr;
            if (node1 != nullptr) {
                node1->parent = nullptr;
            }
            node2 = node;
        }
    }
 
    update_sum(node1);
    update_sum(node2);
 
    if (node2 != nullptr) {
        node2 = find(node2, right);
 
        if (node2->key <= right) {
            node4 = node2->right;
            node2->right = nullptr;
            if (node4 != nullptr) {
                node4->parent = nullptr;
            }
            node3 = node2;
        } else {
            node3 = node2->left;
            node2->left = nullptr;
            if (node3 != nullptr) {
                node3->parent = nullptr;
            }
            node4 = node2;
        }
    }
 
    update_sum(node3);
    update_sum(node4);
 
    long long int ans = (node3 != nullptr) ? node3->sum : 0;
 
    node = merge(node1, merge(node3, node4));
 
    if (node->left != nullptr) {
        node->left->parent = node;
    }
    if (node->right != nullptr) {
        node->right->parent = node;
    }
 
    return ans;
}

void delete_tree(Node* tree) {
    if (tree->left != nullptr) {
        delete_tree(tree->left);
    }


    if (tree->right != nullptr) {
        delete_tree(tree->right);
    }

    delete tree;
}
 
int main() {
    std::ios_base::sync_with_stdio(0);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
 
    int n;
    std::cin >> n;
 
    Node* tree = nullptr;
    long long int y = 0;
    char prev_command = '+';
 
    for (int i = 0; i < n; ++i) {
        char command;
        std::cin >> command;
 
        if (command == '+') {
            int x;
            std::cin >> x;
 
            if (prev_command == '?') {
                tree = insert(tree, (x + y) % 1000000000);
            } else {
                tree = insert(tree, x);
            }
        } else {
            int left, right;
            std::cin >> left >> right;
 
            y = sum(tree, left, right);
            std::cout << y << '\n';
        }
 
        prev_command = command;
    }
	
	if (tree != nullptr) {
        delete_tree(tree);
    }
 
    return 0;
}