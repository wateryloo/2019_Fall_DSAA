/*
* Life is so hard.
* */

import java.util.Scanner;

public class Lab0_D {
    public static void main(String[] args) {
        Scanner in = new Scanner(System.in);
        int count = in.nextInt();
        in.nextLine();
        while (count-- > 0) {
            long input = in.nextLong();
            if (count > 0)
                in.nextLine();
            String inputString = Long.toString(input);
            if (inputString.length() == 1) {
                System.out.print(input + 1);
                if (count > 0)
                    System.out.println();
                continue;
            }
            else if (inputString.length() == 2) {
                int res = 10 + (int)input / 11;
                System.out.print(res);
                if (count > 0)
                    System.out.println();
                continue;
            }
            int length = inputString.length();
            long res = 0;
            for (int i = 0; i < length - 1; ++i) {
                res += 9 * pow(10, i / 2);
                if (i == 0)
                    ++res;
            }
            if (length > 2) {
                long temp = Long.parseLong(inputString.substring(0, 1)) - 1;
                res += temp * pow(10, (length - 1) / 2);
            }
            res += helper(inputString);
            System.out.print(res);
            if (count > 0)
                System.out.println();
        }
        in.close();
    }

    private static long pow(long base, int power) {
        if (power == 0)
            return 1;
        else
            return base * pow(base, power - 1);
    }

    private static long helper(String inputString) {
        int res = 0;
        long input = Long.parseLong(inputString);
        int subStringLength = inputString.length() - 2;
        int effectiveLength = (subStringLength + 1) / 2;
        long max = pow(10, effectiveLength);
        long temp = 0;
        long base = input / pow(10, (int)Math.log10(input));
        base += base * pow(10, (int)Math.log10(input));
        if (input < base)
            return 0;
        while (temp < max) {
            String tempS = Long.toString(temp);
            String lString = "";
            String rString = "";
            for (int i = 0; i < tempS.length(); ++i)
                rString += tempS.charAt(tempS.length() - 1 - i);
            while (rString.length() < effectiveLength)
                rString = rString + "0";
            for (int i = 0; i < rString.length() - 1; ++i)
                lString += rString.charAt(rString.length() - 1 - i);
            if (subStringLength % 2 == 0)
                lString += rString.charAt(0);
            String resString = lString + rString;
            long l = Long.parseLong(resString) * 10;
            l += base;
            if (l <= input) {
                ++res;
                ++temp;
            }
            else
                break;
        }
        return res;
    }
}