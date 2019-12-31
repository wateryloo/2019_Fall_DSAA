#include <iostream>
#include <math.h>
 
/*
 * (2 * a0 + n - 1) * n / 2
 * */
 
int main() {
    int count;
    std::cin >> count;
 
    while (count--) {
        int sum;
        std::cin >> sum;
        if (sum == 1) {
            std::cout << "impossible" << std::endl;
            continue;
        }
        if (sum % 2) {
            std::cout << 2 << std::endl;
            continue;
        }
        else {
            int max_line_number = (int)sqrt(2 * sum) + 1;
            int line_number = 3;
            int valid = 0;
            while (line_number <= max_line_number) {
                if (line_number % 2) {
                    if (sum % line_number == 0) {
                        std::cout << line_number << std::endl;
                        valid = 1;
                        break;
                    }
                }
                else {
                    if (sum % line_number == line_number / 2) {
                        std::cout << line_number << std::endl;
                        valid = 1;
                        break;
                    }
                }
                ++line_number;
            }
            if (valid) {
                continue;
            }
            std::cout << "impossible" << std::endl;
        }
    }
    return 0;
}