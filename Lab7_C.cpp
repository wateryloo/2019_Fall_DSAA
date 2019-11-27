#include <iostream>

#define ll long long

void swap(ll&a, ll&b);
void min_heapify(ll sticks[], int stick_index, int stick_number);

int main() {
    int testcase_number;
    int stick_number;
    int stick_index;
    ll min_0;
    ll min_1;
    ll sum_of_two_min;
    ll res;
    ll sticks[100000];
    scanf(" %d", &testcase_number);
    while (testcase_number > 0) {
        testcase_number = testcase_number - 1;
        res = 0;
        stick_index = 0;
        scanf(" %d", &stick_number);
        while (stick_index < stick_number) {
            scanf(" %lld", &sticks[stick_index]);
            stick_index = stick_index + 1;
        }
        stick_index = stick_number - 1;
        while (stick_index > -1) {
            min_heapify(sticks, stick_index, stick_number);
            stick_index = stick_index - 1;
        }
        while (stick_number > 1) {
            min_0 = sticks[0];
            sticks[0] = sticks[stick_number - 1];
            stick_number = stick_number - 1;
            stick_index = 0;
            min_heapify(sticks, stick_index, stick_number);
            min_1 = sticks[0];
            sum_of_two_min = min_0 + min_1;
            res = res + sum_of_two_min;
            sticks[0] = sum_of_two_min;
            stick_index = 0;
            min_heapify(sticks, stick_index, stick_number);
        }
        printf("%lld\n", res);
    }
    return 0;
}

void swap(ll& a, ll& b) {
    ll temp = a;
    a = b;
    b = temp;
}

void min_heapify(ll sticks[], int stick_index, int stick_number) {
    while (true) {
        if (stick_index * 2 + 1 > stick_number - 1) {
            break;
        }
        else if (stick_index * 2 + 2 > stick_number - 1) {
            if (sticks[stick_index] > sticks[stick_index * 2 + 1]) {
                swap(sticks[stick_index], sticks[stick_index * 2 + 1]);
            }
            break;
        }
        else {
            int min_index = stick_index * 2 + 1;
            if (sticks[min_index] > sticks[min_index + 1]) {
                min_index = min_index + 1;
            }
            if (sticks[stick_index] > sticks[min_index]) {
                swap(sticks[stick_index], sticks[min_index]);
                stick_index = min_index;
            }
            else {
                break;
            }
        }
    }
}