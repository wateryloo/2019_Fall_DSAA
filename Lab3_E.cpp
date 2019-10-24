#include <iostream>
#include <cmath>

long long operate(long long input, short digits);
long long pow10(int digits);

int main() {
    short count;
    scanf(" %hi", &count);
    while (count-- > 0) {
        short digits;
        long long number, fast, slow, max;
        scanf(" %hi %lld", &digits, &number);
        max = number;
        slow = operate(number, digits);
        fast = operate(number, digits);
        max = max > fast ? max : fast;
        max = max > slow ? max : slow;
        fast = operate(fast, digits);
        max = max > fast ? max : fast;
        max = max > slow ? max : slow;
        while (slow != fast) {
            slow = operate(slow, digits);
            fast = operate(fast, digits);
            max = max > fast ? max : fast;
            max = max > slow ? max : slow;
            fast = operate(fast, digits);
            max = max > fast ? max : fast;
            max = max > slow ? max : slow;
        }
        printf("%lld\n", max);
    }
    return 0;
}

long long operate(long long input, short digits) {
    input *= input;
    if (input > pow10(digits) - 1LL) {
        int total_digits = floor(log10(input)) + 1;
        int temp = total_digits - digits;
        input /= pow10(temp);
    }
    return input;
}

long long pow10(int digits) {
    if (digits == 0)
        return 1;
    return 10LL * pow10(digits - 1);
}