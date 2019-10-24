#include <iostream>

int main() {
    short testcase_number;
    scanf(" %hd", &testcase_number);
    while (testcase_number-- > 0) {
        int stack[300000];
        int count[300001] = {0};
        int length, input, top = -1, smallest = 1;
        scanf(" %d", &length);
        int index_range = length;
        while (length-- > 0) {
            scanf(" %d", &input);
            ++count[input];
            while (count[smallest] && smallest <= index_range)
                ++smallest;
            if (smallest > index_range) {
                while (top > -1) {
                    if (input < stack[top]) {
                        printf("%d ", input);
                        input = 300001;
                    }
                    printf("%d ", stack[top--]);
                }
                if (input != 300001)
                    printf("%d ", input);
                break;
            }
            if (input < smallest) {
                if (input < stack[top] || top == -1) {
                    printf("%d ", input);
                    input = 300001;
                }
                while (stack[top] < smallest && top > -1) {
                    if (input < stack[top]) {
                        printf("%d ", input);
                        input = 300001;
                    }
                    printf("%d ", stack[top--]);
                }
            }
            else {
                while (stack[top] < smallest && top > -1)
                    printf("%d ", stack[top--]);
                stack[++top] = input;
            }

        }
        printf("\n");
    }
    return 0;
}