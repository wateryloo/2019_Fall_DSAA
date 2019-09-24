#include <iostream>

void modifiedMerge(int lo, int mid, int hi);
void modifiedMergeSort(int lo, int hi);

long long res;
long long aux[100000];
long long input[100000];

int main() {
    res = 0L;
    for (int i = 0; i < 100000; ++i) {
        aux[i] = 0;
        input[i] = 0;
    }
    int length = 0;
    scanf(" %d", &length);
    for (int i = 0; i < length; ++i) {
        scanf(" %d", &input[i]);
    }
    modifiedMergeSort(0, length - 1);
    printf("%lld", res);
    return 0;
}

void modifiedMerge(int lo, int mid, int hi) {
    long long leftSum = 0;
    int i = lo;
    int j = mid + 1;
    int leftLength = mid - lo + 1;
    for (int k = lo; k <= hi; ++k) {
        aux[k] = input[k];
        if (k <= mid)
            leftSum += input[k];
    }

    for (int k = lo; k <= hi; ++k) {
        if (i > mid)
            input[k] = aux[j++];
        else if (j > hi)
            input[k] = aux[i++];
        else if (aux[j] < aux[i]) {
            int temp = 1;
            while (j + temp <= hi && aux[j + temp] == aux[j])
                ++temp;
            for (int l = 0; l < temp; ++l) {
                input[k + l] = aux[j];
            }
            res += leftLength * temp * aux[j] + temp * leftSum;
            j += temp;
            --k;
            k += temp;
        }
        else {
            input[k] = aux[i];
            leftSum -= aux[i++];
            --leftLength;
        }
    }
}

void modifiedMergeSort(int lo, int hi) {
    if (hi <= lo)
        return;
    int mid = lo + (hi - lo) / 2;
    modifiedMergeSort(lo, mid);
    modifiedMergeSort(mid + 1, hi);
    modifiedMerge(lo, mid, hi);
}