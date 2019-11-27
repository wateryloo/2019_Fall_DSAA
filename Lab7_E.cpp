// reference
// https://www.geeksforgeeks.org/avl-tree-set-1-insertion/
// https://www.geeksforgeeks.org/avl-tree-set-2-deletion/


/*
6 3
201 91 29 13 11 -5
3 1 2 1

 */

#include <iostream>

// height is counted bottom-up.
struct avl_node {
    int val;
    int height;
    int number;
    avl_node* left;
    avl_node* right;
    avl_node(int val) {
        this->val = val;
        this->height = 1;
        this->number = 1;
        this->left = nullptr;
        this->right = nullptr;
    }
};

inline int max(int a, int b);
inline int min(int a, int b);
int get_height(avl_node* n);
int get_number(avl_node* n);
avl_node* right_rotate(avl_node* root);
avl_node* left_rotate(avl_node* root);
void update_height(avl_node* root);
int get_balance_factor(avl_node* n);
avl_node* insert_node(int val, avl_node* old_root);
avl_node* delete_node(int val, avl_node* old_root);
avl_node* get_min_node(avl_node* root);
void inorder_traverse(avl_node* root);
avl_node* get_predecessor_node(int val, avl_node* root);
avl_node* get_successor_node(int val, avl_node* root);

int main() {
    int lengh;
    int width;
    int input_index = 0;
    int input[100000];
    int query_index;
    int query_temp_index;
    avl_node* root = nullptr;
    avl_node* temp;
    scanf(" %d %d", &lengh, &width);
    while (input_index < lengh) {
        scanf(" %d", &input[input_index++]);
    }
    input_index = 0;
    while (input_index < width - 1) {
        root = insert_node(input[input_index++], root);
    }
    while (input_index < lengh) {
        root = insert_node(input[input_index], root);
        temp = root;
        scanf(" %d", &query_index);
        query_temp_index = get_number(temp) - get_number(temp->right);
        while (query_index != query_temp_index) {
            if (query_index > get_number(temp->left)) {
                query_index = query_index - get_number(temp->left) - 1;
                temp = temp->right;
                query_temp_index = get_number(temp) - get_number(temp->right);
            }
            else {
                temp = temp->left;
                query_temp_index = get_number(temp) - get_number(temp->right);
            }
        }
        printf("%d\n", temp->val);
        ++input_index;
        root = delete_node(input[input_index - width], root);
    }
    return 0;
}

inline int max(int a, int b) {
    return a > b ? a : b;
}

inline int min(int a, int b) {
    return a < b ? a : b;
}

int get_height(avl_node* n) {
    if (n) {
        return n->height;
    }
    return 0;
}

int get_number(avl_node* n) {
    if (n) {
        return n->number;
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
    root->number = get_number(root->left) + get_number(root->right) + 1;
}

int get_balance_factor(avl_node* n) {
    if (n) {
        return get_height(n->left) - get_height(n->right);
    }
    return 0;
}

avl_node* insert_node(int val, avl_node* old_root) {
    if (old_root) {
        if (val < old_root->val) {
            old_root->left = insert_node(val, old_root->left);
        }
        else {
            old_root->right = insert_node(val, old_root->right);
        }
        // Bracktrace starts here.
        update_height(old_root);

        int balance_factor = get_balance_factor(old_root);
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

avl_node* delete_node(int val, avl_node* old_root) {
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
        int balance = get_balance_factor(old_root);
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
        printf("%d\t", root->val);
        inorder_traverse(root->right);
    }
}

avl_node* get_predecessor_node(int val, avl_node* root) {
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

avl_node* get_successor_node(int val, avl_node* root) {
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