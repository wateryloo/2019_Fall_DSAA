#include <iostream>

struct avl_node {
    long long val;
    long long height;
    long long number;
    avl_node* left;
    avl_node* right;
    avl_node(long long val) {
        this->val = val;
        this->height = 1;
        this->left = nullptr;
        this->right = nullptr;
    }
};

inline long long max(long long a, long long b);
inline long long min(long long a, long long b);
long long get_height(avl_node* n);
avl_node* right_rotate(avl_node* root);
avl_node* left_rotate(avl_node* root);
void update_height(avl_node* root);
long long get_balance_factor(avl_node* n);
avl_node* insert_node(long long val, avl_node* old_root);
avl_node* delete_node(long long val, avl_node* old_root);
avl_node* get_min_node(avl_node* root);
void inorder_traverse(avl_node* root);
avl_node* get_predecessor_node(long long val, avl_node* root);
avl_node* get_successor_node(long long val, avl_node* root);

int main() {
    long long total_number;
    long long input_flag;
    long long tree_flag;
    long long character_value;
    long long sum = 0;
    long long dif1;
    long long dif2;
    avl_node* predecessor;
    avl_node* successor;
    avl_node* root = nullptr;
    scanf(" %lld", &total_number);
    while (total_number-- > 0) {
        scanf(" %lld %lld", &input_flag, &character_value);
        if (root) {
            if (input_flag == tree_flag) {
                root = insert_node(character_value, root);
            }
            else {
                predecessor = get_predecessor_node(character_value, root);
                successor = get_successor_node(character_value, root);
                if (predecessor && successor) {
                    dif1 = predecessor->val - character_value;
                    dif2 = successor->val - character_value;
                    dif1 = dif1 > 0 ? dif1 : -dif1;
                    dif2 = dif2 > 0 ? dif2 : -dif2;
                    if (dif1 > dif2) {
                        sum += dif2;
                        root = delete_node(successor->val, root);
                    }
                    else {
                        sum += dif1;
                        root = delete_node(predecessor->val, root);
                    }
                }
                else if (predecessor) {
                    dif1 = predecessor->val - character_value;
                    dif1 = dif1 > 0 ? dif1 : -dif1;
                    sum += dif1;
                    root = delete_node(predecessor->val, root);
                }
                else {
                    dif2 = successor->val - character_value;
                    dif2 = dif2 > 0 ? dif2 : -dif2;
                    sum += dif2;
                    root = delete_node(successor->val, root);
                }
            }
        }
        else {
            root = insert_node(character_value, root);
            tree_flag = input_flag;
        }
    }
    printf("%lld\n", sum);
    return 0;
}

inline long long max(long long a, long long b) {
    return a > b ? a : b;
}

inline long long min(long long a, long long b) {
    return a < b ? a : b;
}

long long get_height(avl_node* n) {
    if (n) {
        return n->height;
    }
    return 0;
}

avl_node* right_rotate(avl_node* old_root) {
    if (old_root) {
        avl_node* new_root = old_root->left;
        avl_node* old_root_left_child = new_root->right;
        new_root->right = old_root;
        old_root->left = old_root_left_child;

        // Cannot understand this part.
        update_height(old_root);
        update_height(new_root);
        //

        return new_root;
    }
    return nullptr;
}

avl_node* left_rotate(avl_node* old_root) {
    if (old_root) {
        avl_node* new_root = old_root->right;
        avl_node* old_root_right_child = new_root->left;
        new_root->left = old_root;
        old_root->right = old_root_right_child;

        // Cannot understand this part.
        update_height(old_root);
        update_height(new_root);
        //

        return new_root;
    }
    return nullptr;
}

void update_height(avl_node* root) {
    root->height = max(get_height(root->left), get_height(root->right)) + 1;
}

long long get_balance_factor(avl_node* n) {
    if (n) {
        return get_height(n->left) - get_height(n->right);
    }
    return 0;
}

avl_node* insert_node(long long val, avl_node* old_root) {
    if (old_root) {
        if (val < old_root->val) {
            old_root->left = insert_node(val, old_root->left);
        }
        else {
            old_root->right = insert_node(val, old_root->right);
        }
        // Bracktrace starts here.
        update_height(old_root);

        long long balance_factor = get_balance_factor(old_root);
        if (balance_factor > 1 && val < old_root->left->val) {
            return right_rotate(old_root);
        }
        if (balance_factor < -1 && val >= old_root->right->val) {
            return left_rotate(old_root);
        }
        if (balance_factor > 1 && val >= old_root->left->val) {
            old_root->left = left_rotate(old_root->left);
            return right_rotate(old_root);
        }
        if (balance_factor < -1 && val < old_root->right->val) {
            old_root->right = right_rotate(old_root->right);
            return left_rotate(old_root);
        }
        return old_root;
    }

    return new avl_node(val);
}

avl_node* delete_node(long long val, avl_node* old_root) {
    if (old_root) {
        if (val < old_root->val) {
            old_root->left = delete_node(val, old_root->left);
        }
        else if (val > old_root->val) {
            old_root->right = delete_node(val, old_root->right);
        }
        else {
            if (!old_root->left || !old_root->right) {
                avl_node* temp = old_root->left ? old_root->left : old_root->right;
                if (temp) {
                    old_root = temp;
                }
                else {
                    delete(old_root);
                    return nullptr;
                }
            }
            else {
                avl_node* temp = get_min_node(old_root->right);
                old_root->val = temp->val;
                old_root->right = delete_node(temp->val, old_root->right);
            }
        }
        update_height(old_root);
        long long balance = get_balance_factor(old_root);
        if (balance > 1 && get_balance_factor(old_root->left) >= 0) {
            return right_rotate(old_root);
        }
        if (balance > 1 && get_balance_factor(old_root->left) < 0) {
            old_root->left = left_rotate(old_root->left);
            return right_rotate(old_root);
        }
        if (balance < -1 && get_balance_factor(old_root->right) <= 0) {
            return left_rotate(old_root);
        }
        if (balance < -1 && get_balance_factor(old_root->right) > 0) {
            old_root->right = right_rotate(old_root->right);
            return left_rotate(old_root);
        }
        return old_root;
    }
    return nullptr;
}

avl_node* get_min_node(avl_node* root) {
    avl_node* current = root;
    while (current->left) {
        current = current->left;
    }
    return current;
}

void inorder_traverse(avl_node* root) {
    if (root) {
        inorder_traverse(root->left);
        printf("%lld\t", root->val);
        inorder_traverse(root->right);
    }
}

avl_node* get_predecessor_node(long long val, avl_node* root) {
    avl_node* p = nullptr;
    avl_node* u = root;
    while (u) {
        if (u->val == val) {
            p = u;
            return p;
        }
        else if (u->val > val) {
            u = u->left;
        }
        else {
            p = u;
            u = u->right;
        }
    }
    return p;
}

avl_node* get_successor_node(long long val, avl_node* root) {
    avl_node* s = nullptr;
    avl_node* u = root;
    while (u) {
        if (u->val == val) {
            s = u;
            return s;
        }
        else if (u->val < val) {
            u = u->right;
        }
        else {
            s = u;
            u = u->left;
        }
    }
    return s;
}