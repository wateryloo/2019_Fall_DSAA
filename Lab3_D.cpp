#include <iostream>

struct DoubleLinkedList {
    int val = -1;
    int ind = -1;
    DoubleLinkedList* prev = this;
    DoubleLinkedList* next = this;
};

int main() {
    short count;
    int length, initial;
    scanf(" %hi", &count);
    while (count-- > 0) {
        scanf(" %d %d", &length, &initial);
        if (length == 1) {
            printf("1\n");
            continue;
        }
        DoubleLinkedList* head = new DoubleLinkedList();
        DoubleLinkedList* temp = head;
        for (int i = 0; i < length; ++i) {
            scanf(" %d", &temp->val);
            temp->ind = i + 1;
            if (i < length - 1) {
                temp->next = new DoubleLinkedList();
                temp->next->prev = temp;
                temp->next->next = head;
                temp->next->next->prev = temp->next;
                temp = temp->next;
            }
        }
        temp = head;
        initial = (initial - 1) % length;
        if (initial < length / 2) {
            for (int i = 0; i < initial; ++i)
                temp = temp->next;
        }
        else {
            initial = length - initial;
            for (int i = 0; i < initial; ++i)
                temp = temp->prev;
        }
        --length;
        initial =  (temp->val - 1) % length;
        temp->prev->next = temp->next;
        temp->next->prev = temp->prev;
        temp = temp->next;
        while (length > 1) {
            if (initial < length / 2) {
                while (initial-- > 0) {
                    temp = temp->next;
                }
            }
            else {
                initial = length - initial;
                while (initial-- > 0) {
                    temp = temp->prev;
                }
            }
            --length;
            initial =  (temp->val - 1) % length;
            temp->prev->next = temp->next;
            temp->next->prev = temp->prev;
            if (temp == head)
                head = head->next;
            temp = temp->next;
        }
        printf("%d\n", temp->ind);
    }
    return 0;
}