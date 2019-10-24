#include <iostream>

int main() {
    short case_number;
    int size;
    scanf(" %hd", &case_number);
    while (case_number-- > 0) {
        scanf(" %d", &size);
        char temp;
        if (size % 2) {
            while (size-- > 0)
                scanf(" %c", &temp);
            printf("NO\n");
            continue;
        }
        else {
            char* stack = new char[size / 2];
            int top = -1;
            int temp_size = size;
            while (size-- > 0) {
                scanf(" %c", &temp);
                if (temp == '(' || temp == '[' || temp == '{') {
                    if (top < (temp_size + 1) / 2 - 1)
                        stack[++top] = temp;
                    else
                        break;
                }
                else {
                    if (top == -1)
                        break;
                    else if (temp == ')') {
                        if (stack[top] == '(')
                            --top;
                        else
                            break;
                    }
                    else if (temp == ']') {
                        if (stack[top] == '[')
                            --top;
                        else
                            break;
                    }
                    else {
                        if (stack[top] == '{')
                            --top;
                        else
                            break;
                    }
                }
            }
            if (size > 0) {
                while (size-- > 0)
                    scanf(" %c", &temp);
                printf("NO\n");
            }
            else {
                if (top != -1)
                    printf("NO\n");
                else
                    printf("YES\n");
            }
        }
    }
    return 0;
}