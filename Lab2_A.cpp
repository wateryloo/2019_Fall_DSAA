#include <iostream>
 
int main() {
    int test_case_number = 0;
    int length = 0;
    scanf(" %d", &test_case_number);
    while (test_case_number--) {
        int ith = 0;
        int input[100] = {0};
        int count[101] = {0};
        scanf(" %d", &length);
        for (int i = 0; i < length; ++i) {
            scanf(" %d", &input[i]);
        }
        for (int i = 0; i < length; ++i) {
            ++count[input[i]];
        }
        for (int i = 100; i > -1; --i) {
            if (count[i]) {
                ith += count[i];
                if (ith > 3) {
                    printf("wa\n");
                    break;
                }
                else if (ith == 3) {
                    if (count[i] > 1)
                        printf("wa\n");
                    else
                        printf("%d\n", i);
                    break;
                }
            }
        }
    }
    return 0;
}