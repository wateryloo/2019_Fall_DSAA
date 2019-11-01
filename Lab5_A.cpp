#include <iostream>

int main() {
    int count;
    std::string s;
    std::cin >> count;
    while (count-- > 0) {
        std::cin >> s;
        int length = s.size();
        printf("%d\n", length * (length + 1) / 2);
    }
    return 0;
}