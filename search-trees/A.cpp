#include <iostream>

const int none = -1000000001;

struct Node {
    int key, height;

    Node* left;
    Node* right;

    Node(int key): key(key), height(1), left(nullptr), right(nullptr) {}
};

int get_height(Node* node) {
    return (node == nullptr) ? 0 : node->height;
}

void update_height(Node* node) {
    node->height = std::max(get_height(node->left), get_height(node->right)) + 1;
}

int delta(Node* node) {
    return get_height(node->right) - get_height(node->left);
}

Node* rotate_left(Node* node_parent) {
    Node* node_child = node_parent->right;

    node_parent->right = node_child->left;
    node_child->left = node_parent;

    update_height(node_parent);
    update_height(node_child);

    return node_child;
}

Node* rotate_right(Node* node_parent) {
    Node* node_child = node_parent->left;

    node_parent->left = node_child->right;
    node_child->right = node_parent;

    update_height(node_parent);
    update_height(node_child);

    return node_child;
}

Node* balance(Node* node) {
    update_height(node);

    if (delta(node) == 2) {
        if (delta(node->right) < 0) {
            node->right = rotate_right(node->right);
        }

        return rotate_left(node);
    }

    if (delta(node) == -2) {
        if (delta(node->left) > 0) {
            node->left = rotate_left(node->left);
        }

        return rotate_right(node);
    }

    return node;
}

Node* insert(Node* node, int key) {
    if (node == nullptr) {
        return new Node(key);
    }

    if (node->key > key) {
        node->left = insert(node->left, key);
    } else {
        node->right = insert(node->right, key);
    }

    return balance(node);
}

Node* find_min(Node* node) {
    if (node->left == nullptr) {
        return node;
    } else {
        return find_min(node->left);
    }
}

Node* erase_min(Node* node) {
    if (node->left == nullptr) {
		Node* return_node = node->right;
		delete node;
        return return_node;
    }

    node->left = erase_min(node->left);
    return balance(node);
}

Node* erase(Node* node, int key) {
    if (node->key > key) {
        node->left = erase(node->left, key);
    } else if (node->key < key) {
        node->right = erase(node->right, key);
    } else {
        Node* left = node->left;
        Node* right = node->right;

        delete node;

        if (right == nullptr) {
            return left;
        }

        Node* min = find_min(right);
        min->right = erase_min(right);
        min->left = left;

        return balance(min);
    }

    return balance(node);
}

bool exists(Node* node, int key) {
    if (node == nullptr) {
        return false;
    }

    if (node->key == key) {
        return true;
    } else if (node->key > key) {
        return exists(node->left, key);
    } else {
        return exists(node->right, key);
    }
}

int next(Node* node, int key, int min = none) {
    if (node == nullptr) {
        return min;
    }

    if (node->key > key) {
        if (min == none || node->key < min) {
            min = node->key;
        }

        return next(node->left, key, min);
    } else {
        return next(node->right, key, min);
    }
}

int prev(Node* node, int key, int max = none) {
    if (node == nullptr) {
        return max;
    }

    if (node->key < key) {
        if (max == none || node->key > max) {
            max = node->key;
        }

        return prev(node->right, key, max);
    } else {
        return prev(node->left, key, max);
    }
}

int main() {
    Node* tree = nullptr;

    std::string command;

    while (std::cin >> command) {
        int x;

        std::cin >> x;

        if (command == "insert") {
            if (!exists(tree, x)) {
                tree = insert(tree, x);
            }
        } else if (command == "delete") {
            if (exists(tree, x)) {
                tree = erase(tree, x);
            }
        } else if (command == "exists") {
            if (exists(tree, x)) {
                std::cout << "true\n";
            } else {
                std::cout << "false\n";
            }
        } else if (command == "next") {
            int ans = next(tree, x);

            if (ans != none) {
                std::cout << ans << '\n';
            } else {
                std::cout << "none\n";
            }
        } else if (command == "prev") {
            int ans = prev(tree, x);

            if (ans != none) {
                std::cout << ans << '\n';
            } else {
                std::cout << "none\n";
            }
        }
    }

    return 0;
}
