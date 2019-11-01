#include <iostream>

int main() {
    std::cin.tie(nullptr);
    char code[26];
    for (int i = 0; i < 26; ++i)
        std::cin >> code[i];
    std::string s0, s1;
    std::cin >> s0;
    for (unsigned long i = 0; i < s0.length(); ++i)
        s1 += code[s0.at(i) - 'a'];
    int j = 0;
    int next[s0.length()];
    next[0] = 0;
    for (int i = 1; i < s0.length(); ++i) {
        while (j != 0 && s1[i] != s0[j])
            j = next[j - 1];
        if (s1[i] == s0[j])
            ++j;
        next[i] = j;
    }
    std::cout << s0.length() - next[s0.length() - 1] << std::endl;
    return 0;
}