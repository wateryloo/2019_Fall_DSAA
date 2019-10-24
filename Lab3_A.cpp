#include <iostream>

struct LinkedList {
    int coeff = 0;
    int expon = -1;
    LinkedList* next = nullptr;
};

LinkedList* addPolynomial(LinkedList* l0, LinkedList* l1);

int main() {
    short count;
    int queries[2000];
    scanf(" %hi", &count);
    while (count-- > 0) {
        auto* l0 = new LinkedList();
        auto* l1 = new LinkedList();
        auto* curNode = new LinkedList();
        int length0, length1, maxLength, queryNumber, exponCount;
        scanf(" %d", &length0);
        curNode = l0;
        for (int i = 0; i < length0; ++i) {
            auto* temp = new LinkedList();
            scanf(" %d %d", &temp->coeff, &temp->expon);
            curNode->next = temp;
            curNode = curNode->next;
        }
        scanf(" %d", &length1);
        curNode = l1;
        for (int i = 0; i < length1; ++i) {
            auto* temp = new LinkedList();
            scanf(" %d %d", &temp->coeff, &temp->expon);
            curNode->next = temp;
            curNode = curNode->next;
        }
        l0 = addPolynomial(l0, l1);
        scanf(" %d", &queryNumber);
        for (int i = 0; i < queryNumber; ++i)
            scanf(" %d", &queries[i]);
        for (int i = 0; i < queryNumber; ++i) {
            while (l0->expon < queries[i]) {
                l0 = l0->next;
                if (!l0) {
                    for (int j = i; j < queryNumber; ++j)
                        printf("0 ");
                    break;
                }
            }
            if (!l0)
                break;
            if (l0->expon == queries[i])
                printf("%d ", l0->coeff);
            if (l0->expon > queries[i])
                printf("0 ");
        }
        printf("\n");
    }
}

LinkedList* addPolynomial(LinkedList* l0, LinkedList* l1) {
    l0 = l0->next;
    l1 = l1->next;
    auto* l = new LinkedList();
    LinkedList* temp = l;
    while (l0 && l1) {
        if (l0->expon < l1->expon) {
            temp->next = new LinkedList();
            temp = temp->next;
            temp->coeff = l0->coeff;
            temp->expon = l0->expon;
            l0 = l0->next;
        }
        else if (l0->expon > l1->expon) {
            temp->next = new LinkedList();
            temp = temp->next;
            temp->coeff = l1->coeff;
            temp->expon = l1->expon;
            l1 = l1->next;
        }
        else {
            temp->next = new LinkedList();
            temp = temp->next;
            temp->coeff = l0->coeff + l1->coeff;
            temp->expon = l0->expon;
            l0 = l0->next;
            l1 = l1->next;
        }
    }
    if (l0) {
        temp->next = l0;
    }
    else {
        if (l1) {
            temp->next = l1;
        }
    }
    return l;
}