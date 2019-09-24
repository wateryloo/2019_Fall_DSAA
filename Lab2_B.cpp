#include <iostream>
 
int main() {
    int length;
    int ith;
    int input[1000000] = {0};
    int count[1000001] = {0};
    scanf(" %d %d", &length, &ith);
    for (int i = 0; i < length; ++i) {
        scanf(" %d", &input[i]);
        ++count[input[i]];
    }
    for (int i = 0; i < 1000001; ++i) {
        if (count[i])
            ith = ith - count[i];
        if (ith < 1) {
            printf("%d", i);
            break;
        }
    }
    return 0;
}