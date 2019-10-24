#include <iostream>
#include <cmath>

typedef struct DoubleLinkedList {
    int index = -1;
    int val = -1;
    int res = -1;
    DoubleLinkedList* prev = nullptr;
    DoubleLinkedList* next = nullptr;
} DLL;

void quicksort_by_value(DLL** input, int lo, int hi);
int partition_by_value(DLL** input, int lo, int hi);
void quicksort_by_index(DLL** input, int lo, int hi);
int partition_by_index(DLL**, int lo, int hi);
void swap(DLL** input, int i1, int i2);

int main() {
    DLL** input = (DLL**)malloc(2000000 * sizeof(DLL*));
    int size;
    scanf(" %d", &size);
    for (int i = 0; i < size; ++i) {
        input[i] = new DLL();
        input[i]->index = i;
        scanf(" %d", &input[i]->val);
    }
    quicksort_by_value(input, 0, size - 1);
    for (int i = 0; i < size; ++i) {
        if (i) {
            input[i]->prev = input[i - 1];
            input[i]->prev->next = input[i];
        }
    }
    quicksort_by_index(input, 0, size - 1);
    for (int i = 0; i < size - 1; ++i) {
        if (input[i]->prev) {
            input[i]->res = abs(input[i]->prev->val - input[i]->val);
            input[i]->prev->next = input[i]->next;
        }
        if (input[i]->next) {
            if (input[i]->res == -1)
                input[i]->res = abs(input[i]->next->val - input[i]->val);
            else
                input[i]->res = input[i]->res < abs(input[i]->next->val - input[i]->val) ? input[i]->res : abs(input[i]->next->val - input[i]->val);
            input[i]->next->prev = input[i]->prev;
        }
        printf("%d ", input[i]->res);
    }
    return 0;
}

void quicksort_by_value(DLL** input, int lo, int hi) {
    if (hi <= lo)
        return;
    int j = partition_by_value(input, lo, hi);
    quicksort_by_value(input, lo, j - 1);
    quicksort_by_value(input, j + 1, hi);
}

int partition_by_value(DLL** input, int lo, int hi) {
    int i = lo;
    int j = hi + 1;
    int v = input[lo]->val;
    while (true) {
        while (input[++i]->val < v) {
            if (i == hi)
                break;
        }
        while (v < input[--j]->val) {
            if (j == lo)
                break;
        }
        if (i >= j)
            break;
        swap(input, i, j);
    }
    swap(input, lo, j);
    return j;
}

void quicksort_by_index(DLL** input, int lo, int hi) {
    if (hi <= lo)
        return;
    int j = partition_by_index(input, lo, hi);
    quicksort_by_index(input, lo, j - 1);
    quicksort_by_index(input, j + 1, hi);
}

int partition_by_index(DLL** input, int lo, int hi) {
    int i = lo;
    int j = hi + 1;
    int v = input[lo]->index;
    while (true) {
        while (input[++i]->index < v) {
            if (i == hi)
                break;
        }
        while (v < input[--j]->index) {
            if (j == lo)
                break;
        }
        if (i >= j)
            break;
        swap(input, i, j);
    }
    swap(input, lo, j);
    return j;
}

void swap(DLL** input, int i1, int i2) {
    auto* temp = input[i1];
    input[i1] = input[i2];
    input[i2] = temp;
}