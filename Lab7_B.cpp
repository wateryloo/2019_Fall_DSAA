/*
bool is_complete_binary_tree(int root_index, int* left_child, int* right_child, int node_number) {
    return
            node_number == is_complete_binary_tree_helper(root_index, left_child, right_child);
}

int is_complete_binary_tree_helper(int root_index, int* left_child, int* right_child) {
    if (left_child[root_index] == 0 && right_child[root_index] == 0) {
        return 1;
    }
    else if (right_child[root_index] == 0) {
        return 2;
    }
    else {
        return 1 + is_complete_binary_tree_helper(left_child[root_index], left_child, right_child)
               + is_complete_binary_tree_helper(right_child[root_index], left_child, right_child);
    }
}
*/

#include <iostream>

using std::cin;
using std::cout;
using std::endl;

bool is_complete_binary_tree(int root_index, int* left_child, int* right_child, int node_number);

int main() {
    cin.tie(nullptr);
    int testcase_number;
    int testcase_index = 0;
    int node_number;
    int parent_index;
    int child_index;
    int node_index;
    bool res_flag;
    bool is_minheap;
    bool is_minheap_pending;
    cin >> testcase_number;
    while (testcase_index < testcase_number) {
        testcase_index = testcase_index + 1;
        res_flag = true;
        is_minheap_pending = true;
        cin >> node_number;
        int* nodes = new int[node_number + 1]();
        int* parent = new int[node_number + 1]();
        int* left_child = new int[node_number + 1]();
        int* right_child = new int[node_number + 1]();
        node_index = 1;
        while (node_index <= node_number) {
            cin >> nodes[node_index];
            node_index = node_index + 1;
        }
        if (node_index == 2) {
            cout << "Case #" << testcase_index << ": YES" << endl;
            continue;
        }
        while (node_index > 2) {
            node_index = node_index - 1;
            cin >> parent_index >> child_index;
            if (res_flag) {
                parent[child_index] = parent_index;
                if (left_child[parent_index] == 0) {
                    left_child[parent_index] = child_index;
                }
                else if (right_child[parent_index] == 0) {
                    right_child[parent_index] = child_index;
                }
                else {
                    res_flag = false;
                }
                if (nodes[parent_index] != nodes[child_index]) {
                    if (is_minheap_pending) {
                        is_minheap_pending = false;
                        is_minheap = nodes[parent_index] < nodes[child_index];
                    }
                    else {
                        res_flag = !((is_minheap && nodes[parent_index] > nodes[child_index]) ||
                                     (!is_minheap && nodes[parent_index] < nodes[child_index])); // Negation of XOR.
                    }
                }
            }
        }
        if (!res_flag) {
            cout << "Case #" << testcase_index << ": NO" << endl;
            continue;
        }
        node_index = 1;
        while (parent[node_index] != 0 && node_index <= node_number) {
            node_index = node_index + 1;
        }
        res_flag = node_index <= node_number &&
                is_complete_binary_tree(node_index, left_child, right_child, node_number);
        if (res_flag) {
            cout << "Case #" << testcase_index << ": YES" << endl;
        }
        else {
            cout << "Case #" << testcase_index << ": NO" << endl;
        }
    }
    return 0;
}

bool is_complete_binary_tree(int root_index, int* left_child, int* right_child, int node_number) {
    int* queue = new int[node_number]();
    queue[0] = root_index;
    int front = 0;
    int rear = 1;
    while (front != rear) {
        if (left_child[queue[front]] == 0) {
            break;
        }
        queue[rear] = left_child[queue[front]];
        rear = rear + 1;
        if (right_child[queue[front]] == 0) {
            break;
        }
        queue[rear] = right_child[queue[front]];
        rear = rear + 1;
        front = front + 1;
    }
    return rear == node_number;
}