#include <iostream>

struct DoubleLinkedList {
    char val = '\n';
    DoubleLinkedList* prev = this;
    DoubleLinkedList* next = this;
};

int main() {
    short count;
    int length;
    char input;
    scanf(" %hi", &count);
    while (count-- > 0) {
        DoubleLinkedList* head = new DoubleLinkedList();
        DoubleLinkedList* tail = new DoubleLinkedList();
        head->prev = nullptr;
        head->next = tail;
        tail->next = nullptr;
        tail->prev = head;
        DoubleLinkedList* temp = head->next;
        scanf(" %d", &length);
        while (length-- > 0) {
            scanf(" %c", &input);
            switch(input) {
                case 'I':
                    temp = head->next;
                    break;
                case 'H':
                    if (temp != head->next)
                        temp = temp->prev;
                    break;
                case 'L':
                    if (temp != tail)
                        temp = temp->next;
                    break;
                case 'x':
                    if (temp != tail) {
                        temp->prev->next = temp->next;
                        temp->next->prev = temp->prev;
                        temp = temp->next;
                    }
                    break;
                case 'r':
                    if (length) {
                        if (temp == tail) {
                            auto* new_node = new DoubleLinkedList();
                            temp->prev->next = new_node;
                            scanf(" %c", &temp->prev->next->val);
                            --length;
                            temp->prev->next->next = temp;
                            temp->prev->next->prev = temp->prev;
                            temp->prev = temp->prev->next;
                            temp = temp->prev;
                        }
                        else {
                            scanf(" %c", &temp->val);
                            --length;
                        }
                        break;
                    }
                    else
                        break;
                default:
                    auto* new_node = new DoubleLinkedList();
                    temp->prev->next = new_node;
                    temp->prev->next->val = input;
                    temp->prev->next->next = temp;
                    temp->prev->next->prev = temp->prev;
                    temp->prev = temp->prev->next;
                    break;
            }
        }
        temp = head->next;
        while (temp->val != '\n') {
            printf("%c", temp->val);
            temp = temp->next;
        }
        printf("\n");
    }
    return 0;
}