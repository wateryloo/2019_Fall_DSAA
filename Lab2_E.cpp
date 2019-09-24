#include <iostream>
#define HP 0
#define AD 1
#define DF 2

long long soldiers[200000][3] = {0};

void quickSort(int lo, int hi);
long long becomeDouble(long long base, int time);
long long pow(int time, long long res);
int partition(int lo, int hi);
void swap(long long soldier1[], long long soldier[2]);

int main() {
    int soldierNumber;
    int doubleTime;
    int swapTime;
    int range = 0;
    long long res = 0;
    long long temp = 0;
    long long part = 0;
    long long prev = 0;
    scanf(" %d %d %d", &soldierNumber, &doubleTime, &swapTime);
    for (int i = 0; i < soldierNumber; ++i) {
        scanf(" %d %d", &soldiers[i][HP], &soldiers[i][AD]);
        soldiers[i][DF] = soldiers[i][HP] - soldiers[i][AD];
    }

    quickSort(0, soldierNumber - 1);

    for (int i = 0; i < soldierNumber && i < swapTime; ++i) {
        if (soldiers[i][DF] <= 0)
            break;
        ++range;
        part += soldiers[i][HP];
    }
    for (int i = range; i < soldierNumber; ++i) {
        part += soldiers[i][AD];
    }
    prev = part;

    for (int i = 0; i < soldierNumber; ++i) {
        if (i < range)
            part += becomeDouble(soldiers[i][HP], doubleTime) - soldiers[i][HP];
        else {
            if (range > 0) {
                if (swapTime <= range) {
                    if (becomeDouble(soldiers[i][HP], doubleTime) - soldiers[i][AD] - soldiers[range - 1][DF] > 0)
                        part += becomeDouble(soldiers[i][HP], doubleTime) - soldiers[i][AD] - soldiers[range - 1][DF];
                }
                else {
                    if (becomeDouble(soldiers[i][HP], doubleTime) - soldiers[i][AD])
                        part += becomeDouble(soldiers[i][HP], doubleTime) - soldiers[i][AD];
                }
            }
            else {
                if (swapTime) {
                    if (becomeDouble(soldiers[i][HP], doubleTime) - soldiers[i][AD] > 0) {
                        part += becomeDouble(soldiers[i][HP], doubleTime) - soldiers[i][AD];
                    }
                }
            }
        }
        temp = part;
        res = res >= temp ? res : temp;
        part = prev;
    }
    printf("%lld", res);
    return 0;
}

void quickSort(int lo, int hi) {
    if (hi <= lo)
        return;
    int j = partition(lo, hi);
    quickSort(lo, j - 1);
    quickSort(j + 1, hi);
}

long long becomeDouble(long long base, int time) {
    if (time == 0)
        return base;
    return pow(time, base);
}

long long pow(int time, long long res) {
    if (time == 0)
        return res;
    return pow(time - 1, res * 2LL);
}

int partition(int lo, int hi) {
    int i = lo;
    int j = hi + 1;
    long long v = soldiers[lo][DF];
    while (true) {
        while (soldiers[++i][DF] > v) {
            if (i == hi)
                break;
        }
        while (v > soldiers[--j][DF]) {
            if (j == lo)
                break;
        }
        if (i >= j)
            break;
        swap(soldiers[i], soldiers[j]);
    }
    swap(soldiers[lo], soldiers[j]);
    return j;
}

void swap(long long soldier1[], long long soldier2[]) {
    long temp[3] = {0};
    for (int i = 0; i < 3; ++i) {
        temp[i] = soldier1[i];
        soldier1[i] = soldier2[i];
    }
    for (int i = 0; i < 3; ++i)
        soldier2[i] = temp[i];
}