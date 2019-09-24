#include <iostream>
#define BLUE 0
#define RED 1
#define DF 2

typedef long long ll;
void modifiedQuickSort(ll input[100000][3], int lo, int hi, int index, bool ascending);
void modifiedQuickSort(ll input[100000][3], int lo, int hi, int index);
int modifiedPartition(ll input[100000][3], int lo, int hi, int index);
void swap(ll bead1[], ll bead2[]);

int main() {
    int count;
    scanf(" %d", &count);
    while (count-- > 0) {
        ll res = 0;
        ll red = 0;
        int length;
        int lo1 = -1;
        int hi1 = -1;
        int lo2 = -1;
        int hi2 = -2;
        scanf(" %d", &length);
        ll input[100000][3] = {0};
        for (int i = 0; i < length; ++i) {
            scanf(" %lld %lld", &input[i][BLUE], &input[i][RED]);
            input[i][DF] = input[i][BLUE] - input[i][RED];
        }
        modifiedQuickSort(input, 0, length - 1, DF, true);
        for (int i = 0; i < length; ++i) {
            if (i == 0) {
                if (input[i][DF] < 0) {
                    lo1 = 0;
                    if (input[length - 1][DF] < 0) {
                        hi1 = length - 1;
                        break;
                    }
                }
                else if (input[i][DF] == 0);
                else {
                    lo2 = 0;
                    hi2 = length - 1;
                    break;
                }
            }
            else {
                if (input[i][DF] < 0);
                else if (input[i][DF] == 0) {
                    if (lo1 == 0)
                        hi1 = i - 1;
                }
                else {
                    if (lo1 == 0) {
                        hi1 = i - 1;
                        lo2 = i;
                        hi2 = length - 1;
                        break;
                    }
                    else {
                        lo2 = i;
                        hi2 = length - 1;
                        break;
                    }
                }
            }
        }
        modifiedQuickSort(input, lo1, hi1, BLUE, true);
        modifiedQuickSort(input, lo2, hi2, RED, false);
        for (int i = 0; i < length; ++i) {
            if (i == 0)
                red += input[0][RED];
            else if (i == length - 1) {
                if (red > 0)
                    res += red >= input[length - 1][BLUE] ? input[length - 1][BLUE] : red;
            }
            else {
                if (red > 0) {
                    if (red >= input[i][BLUE]) {
                        res += input[i][BLUE];
                        red = red - input[i][BLUE] + input[i][RED];
                    }
                    else {
                        res += red;
                        red = input[i][RED];
                    }
                }
                else
                    red += input[i][RED];
            }
        }
        printf("%lld\n", res);
    }
    return 0;
}

void modifiedQuickSort(ll input[100000][3], int lo, int hi, int index, bool ascending) {
    if (ascending)
        modifiedQuickSort(input, lo, hi, index);
    else {
        for (int i = lo; i < hi + 1; ++i) {
            input[i][index] *= -1;
        }
        modifiedQuickSort(input, lo, hi, index);
        for (int i = lo; i < hi + 1; ++i)
            input[i][index] *= -1;
    }
}

void modifiedQuickSort(ll input[100000][3], int lo, int hi, int index) {
    if (hi <= lo)
        return;
    int j = modifiedPartition(input, lo, hi, index);
    modifiedQuickSort(input, lo, j - 1, index);
    modifiedQuickSort(input, j + 1, hi, index);
}

int modifiedPartition(ll input[100000][3], int lo, int hi, int index) {
    int i = lo;
    int j = hi + 1;
    ll v = input[lo][index];
    while (true) {
        while (input[++i][index] < v) {
            if (i == hi)
                break;
        }
        while (v < input[--j][index]) {
            if (j == lo)
                break;
        }
        if (i >= j)
            break;
        swap(input[i], input[j]);
    }
    swap(input[lo], input[j]);
    return j;
}

void swap(ll bead1[], ll bead2[]) {
    ll temp[3] = {0};
    for (int i = 0; i < 3; ++i) {
        temp[i] = bead1[i];
        bead1[i] = bead2[i];
    }
    for (int i = 0; i < 3; ++i)
        bead2[i] = temp[i];
}