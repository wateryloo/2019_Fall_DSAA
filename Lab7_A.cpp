#include <iostream>

int main() {
    int testcase_number;
    int binary_tree[150001][3] = {0};
    int queue[150000];
    scanf("%d ", &testcase_number);
    while (testcase_number > 0) {
        for (int i = 0; i < 150001; i = i + 1) {
            for (int j = 0; j < 3; j = j + 1) {
                binary_tree[i][j] = 0;
            }
        }
        int front = 0;
        int rear = 0;
        int node_number;
        int root = 0;
        testcase_number = testcase_number - 1;
        scanf("%d ", &node_number);
        for (int i = 1; i <= node_number; i = i + 1) {
            int left;
            int right;
            scanf("%d %d ", &left, &right);
            binary_tree[i][1] = left;
            binary_tree[left][0] = i;
            binary_tree[i][2] = right;
            binary_tree[right][0] = i;
        }
        for (int i = 1; i <= node_number; i = i + 1) {
            if (binary_tree[i][0] == 0) {
                root = i;
                break;
            }
        }
        queue[rear] = root;
        rear = rear + 1;
        while (front != rear) {
            if (binary_tree[queue[front]][1] == 0) {
                break;
            }
            queue[rear] = binary_tree[queue[front]][1];
            rear = rear + 1;
            if (binary_tree[queue[front]][2] == 0) {
                break;
            }
            queue[rear] = binary_tree[queue[front]][2];
            rear = rear + 1;
            front = front + 1;
        }
        if (rear == node_number) {
            printf("Yes\n");
        }
        else {
            printf("No\n");
        }
    }
    return 0;
}