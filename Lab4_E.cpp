#include <iostream>

typedef struct DoubleLinkedList {
    int value;
    int index;
    DoubleLinkedList* prev;
    DoubleLinkedList* next;

    DoubleLinkedList(int value, int index) {
        this->value = value;
        this->index = index;
        this->prev = nullptr;
        this->next = nullptr;
    }
} DLL;

int main() {
    int case_number = 0;
    int testcase_number, length;
    scanf(" %d", &testcase_number);
    while (testcase_number-- > 0) {
        printf("Case %d:\n", ++case_number);
        scanf(" %d", &length);
        int input[50001] = {0}, left[50001] = {0}, right[50001] = {0};
        DLL* HEAD = new DLL(-1, -1);
        DLL* new_node;
        DLL* rear = HEAD;
        for (int i = 0; i < length; ++i) {
            scanf(" %d", &input[i]);
            new_node = new DLL(input[i], i + 1);
            while (rear != HEAD) {
                if (new_node->value > rear->value) {
                    if (new_node->index > rear->index + 1)
                        right[rear->index] = rear->next->index;
                    rear = rear->prev;
                }
                else
                    break;
            }
            new_node->prev = rear;
            rear->next = new_node;
            rear = rear->next;

            if (i == length - 1) {
                rear = rear->prev;
                while (rear != HEAD) {
                    right[rear->index] = rear->next->index;
                    rear = rear->prev;
                }
            }
        }

        HEAD = new DLL(-1, -1);
        rear = HEAD;
        for (int i = length - 1; i > -1; --i) {
            new_node = new DLL(input[i], i + 1);
            while (rear != HEAD) {
                if (new_node->value > rear->value) {
                    if (new_node->index < rear->index - 1)
                        left[rear->index] = rear->next->index;
                    rear = rear->prev;
                }
                else
                    break;
            }
            new_node->prev = rear;
            rear->next = new_node;
            rear = rear->next;

            if (i == 0) {
                rear = rear->prev;
                while (rear != HEAD) {
                    left[rear->index] = rear->next->index;
                    rear = rear->prev;
                }
            }
        }

        for (int i = 1; i < length + 1; ++i) {
            printf("%d %d \n", left[i], right[i]);
        }
    }
    return 0;
}