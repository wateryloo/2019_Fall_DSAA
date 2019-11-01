import java.util.Arrays;
import java.util.Scanner;

public class Lab5_E {
    public static void main(String[] args) {
        final long BASE = 97;
        Scanner in = new Scanner(System.in);
        String s1, s2, t;
        s1 = in.nextLine();
        t = in.nextLine();
        if (s1.length() < t.length())
            s2 = t;
        else {
            s2 = s1;
            s1 = t;
        }
        s1 = s1.trim();
        s2 = s2.trim();
        char[] l1 = s1.toCharArray();
        char[] l2 = s2.toCharArray();
        int left = 0;
        int right = l1.length;
        int res = 0;

        while (left <= right) {
            boolean match = false;
            long EXP = 1;
            int mid = (left + right) / 2;
            for (int i = 0; i < mid - 1; ++i)
                EXP *= BASE;
            long[] arr = new long[l1.length - mid + 1];
            long temp = 0;

            for (int i = 0; i < l1.length; ++i) {
                if (i >= mid)
                    temp -= l1[i - mid] * EXP;
                temp = temp * BASE + l1[i];
                if (i >= mid - 1)
                    arr[i - mid + 1] = temp;
            }

            Arrays.sort(arr);
            temp = 0;

            for (int i = 0; i < l2.length; ++i) {
                if (i >= mid)
                    temp -= l2[i - mid] * EXP;
                temp = temp * BASE + l2[i];

                if (i >= mid - 1) {
                    int left_in = 0;
                    int right_in = arr.length - 1;
                    while (left_in <= right_in) {
                        int mid_in = left_in + (right_in - left_in) / 2;
                        if (arr[mid_in] == temp) {
                            match = true;
                            break;
                        }
                        else if (arr[mid_in] < temp)
                            left_in = mid_in + 1;
                        else
                            right_in = mid_in - 1;
                    }
                    if (match)
                        break;
                }
            }

            if (match) {
                res = mid;
                left = mid + 1;
            }
            else
                right = mid - 1;
        }
        in.close();
        System.out.println(res);
    }
}