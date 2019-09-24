#include <iostream>

void quickSort(long long input[], int lo, int hi);
int partition(long long input[], int lo, int hi);
void swap(long long *i, long long *j);
void merge(long long input[], int lo, int mid, int hi);
void mergeSort(long long input[], int lo, int hi);

long long aux[3000] = {0};

int main() {
    int length;
    long long sum;
    scanf(" %d %lld", &length, &sum);
    if (length < 3) {
        printf("0");
        return 0;
    }
    long long res = 0;
    long long input[3000] = {0};
    for (int i = 0; i < length; ++i) {
        scanf(" %lld", &input[i]);
    }
    mergeSort(input, 0, length - 1);
    for (int i = 0; i < length - 2; ++i) {
        long long x = input[i];
        long long j = i + 1;
        long long k = length - 1;
        while (j < k) {
            if (x + input[j] + input[k] < sum) {
                ++j;
                continue;
            }
            if (x + input[j] + input[k] == sum) {
                if (input[j] == input[k]) {
                    res += (k - j) * (k - j + 1) / 2;
                    break;
                }

                long long temp = 1;
                while (k - temp > j && input[k - temp] == input[k])
                    ++temp;

                long long count = 1L;
                while (j + count < k && input[j] == input[j + count])
                    ++count;

                res += temp * count;
                j += count;
                k -= temp;

                continue;
            }
            while (x + input[j] + input[k] > sum) {
                --k;
                if (k <= j)
                    break;
            }
            if (k <= j)
                break;
        }
    }
    printf("%lld", res);
    return 0;
}

void quickSort(long long input[], int lo, int hi) {
    if (hi <= lo)
        return;
    int j = partition(input, lo, hi);
    quickSort(input, lo, j - 1);
    quickSort(input, j + 1, hi);
}

int partition(long long input[], int lo, int hi) {
    int i = lo;
    int j = hi + 1;
    long long v = input[lo];
    while (true) {
        while (input[++i] < v) {
            if (i == hi)
                break;
        }
        while (v < input[--j]) {
            if (j == lo)
                break;
        }
        if (i >= j)
            break;
        swap(&input[i], &input[j]);
    }
    swap(&input[lo], &input[j]);
    return j;
}

void swap(long long *i, long long *j) {
    long long temp = *i;
    *i = *j;
    *j = temp;
}

void merge(long long input[], int lo, int mid, int hi) {
    int i = lo;
    int j = mid + 1;
    for (int k = lo; k <= hi; ++k)
        aux[k] = input[k];

    for (int k = lo; k <= hi; ++k) {
        if (i > mid)
            input[k] = aux[j++];
        else if (j > hi)
            input[k] = aux[i++];
        else if (aux[j] < aux[i])
            input[k] = aux[j++];
        else
            input[k] = aux[i++];
    }
}

void mergeSort(long long input[], int lo, int hi) {
    if (hi <= lo)
        return;
    int mid = lo + (hi - lo) / 2;
    mergeSort(input, lo, mid);
    mergeSort(input, mid + 1, hi);
    merge(input, lo, mid, hi);
}