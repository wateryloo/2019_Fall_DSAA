import java.util.Scanner;

public class Lab5_C {
    public static void main(String[] args) {
        Scanner in = new Scanner(System.in);
        int count = in.nextInt();
        int res = 0;
        in.nextLine();
        String pattern, text;
        while (count-- > 0) {
            pattern = in.next();
            pattern = pattern.substring(0, (int)Math.ceil(pattern.length() / 3.0));
            text = in.next();
            if (kmp_matcher(text, pattern))
                ++res;
        }
        System.out.println(res);
        in.close();
    }

    private static int[] compute_prefix_function(String pattern_string) {
        int M = pattern_string.length();
        char[] pattern = pattern_string.toCharArray();
        int[] lps = new int[M];
        int len = 0;
        int i = 1;
        while (i < M) {
            if (pattern[i] == pattern[len]) {
                ++len;
                lps[i] = len;
                ++i;
            }
            else {
                if (len != 0)
                    len = lps[len - 1];
                else
                    lps[i++] = len;
            }
        }
        return lps;
    }

    private static boolean kmp_matcher(String text, String pattern_string) {
        int M = pattern_string.length();
        int N = text.length();
        int[] lps = compute_prefix_function(pattern_string);
        char[] pattern = pattern_string.toCharArray();
        int i = 0;
        int j = 0;
        while (i < N) {
            if (pattern[j] == text.charAt(i)) {
                ++i;
                ++j;
            }
            if (j == M)
                return true;
            else if (i < N && pattern[j] != text.charAt(i)) {
                if (j != 0)
                    j = lps[j - 1];
                else
                    ++i;
            }
        }
        return false;
    }

}