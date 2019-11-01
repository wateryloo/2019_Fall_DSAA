#include <iostream>

using std::cin;
using std::string;

// private static int[] compute_prefix_function(String pattern_string) {
//     int M = pattern_string.length();
//     char[] pattern = pattern_string.toCharArray();
//     int[] lps = new int[M];
//     int len = 0;
//     int i = 1;
//     while (i < M) {
//         if (pattern[i] == pattern[len]) {
//             ++len;
//             lps[i] = len;
//             ++i;
//         }
//         else {
//             if (len != 0)
//                 len = lps[len - 1];
//             else
//                 lps[i++] = len;
//         }
//     }
//     return lps;
// }

int main() {
    std::cin.tie(nullptr);
    int count;
    string input;
    int next[200001] = {0};
    cin >> count;
    while (count-- > 0) {
        cin >> input;

        int M = input.length();
        int len = 0;
        int ind = 1;
        while (ind < M) {
            if (input[ind] == input[len]) {
                ++len;
                next[ind] = len;
                ++ind;
            }
            else {
                if (len != 0)
                    len = next[len - 1];
                else
                    next[ind++] = len;
            }
        }

        int i = (int)input.length() - 1;
        int loop = M - next[i];
        int temp = M % loop;
        int res = (loop - temp) % loop;
        if (loop == M)
            printf("%d\n", M);
        else if (next[i])
            printf("%d\n", res);
        else
            printf("0\n");
    }
}