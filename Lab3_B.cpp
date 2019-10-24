#include <iostream>
#define head 100000
#define start 0
#define end 1

struct DoubleLinkedList {
    int val = -1;
    DoubleLinkedList* prev = this;
    DoubleLinkedList* next = this;
};

int main() {
    short count;
    int order0[2];
    int order1[2];
    DoubleLinkedList* s0;
    DoubleLinkedList* e0;
    DoubleLinkedList* s1;
    DoubleLinkedList* e1;
    DoubleLinkedList* line[100001];
    line[head] = new DoubleLinkedList();
    scanf(" %hi", &count);
    while (count-- > 0) {
        int length_of_team, number_of_orders;
        auto* temp = line[head];
        scanf(" %d %d", &length_of_team, &number_of_orders);
        for (int i = 0; i < length_of_team; ++i) {
            int val;
            scanf(" %d", &val);
            line[val] = new DoubleLinkedList();
            temp->next = line[val];
            auto* new_member = line[val];
            new_member->val = val;
            new_member->prev = temp;
            new_member->next = line[head];
            line[head]->prev = new_member;
            temp = temp->next;
        }
        for (int i = 0; i < number_of_orders; ++i) {
            scanf(" %d %d %d %d", &order0[start], &order0[end], &order1[start], &order1[end]);
            s0 = line[order0[start]];
            e0 = line[order0[end]];
            s1 = line[order1[start]];
            e1 = line[order1[end]];
            if (e0->next != s1) {
                temp = s0->prev;
                s0->prev = s1->prev;
                s0->prev->next = s0;
                s1->prev = temp;
                s1->prev->next = s1;
                temp = e0->next;
                e0->next = e1->next;
                e0->next->prev = e0;
                e1->next = temp;
                e1->next->prev = e1;
            }
            else {
                temp = s0->prev;
                s0->prev = e1;
                e0->next = e1->next;
                e0->next->prev = e0;
                e1->next = s0;
                s1->prev = temp;
                s1->prev->next = s1;
            }
        }
        temp = line[head];
        for (int i = 0; i < length_of_team; ++i) {
            temp = temp->next;
            printf("%d ", temp->val);
        }
        printf("\n");
    }
    return 0;
}