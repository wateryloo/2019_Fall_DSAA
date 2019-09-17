import java.util.Arrays;
import java.util.Scanner;

public class Lab1_F {
    public static void main(String[] args) {
        long[] powers = new long[27];
        powers[0] = 5;
        for (int i = 1; i < 27; ++i) {
            powers[i] = powers[i - 1] * (long)5;
        }
        System.out.println(Arrays.toString(powers));
        Scanner in = new Scanner(System.in);
        int count = in.nextInt();
        in.nextLine();
        while (count-- > 0) {
            long input = in.nextLong();
            long res = 0;
            long temp = 1;
            for (int i = 1; i < 27; ++i) {
                temp = temp * (long)5;
                if (temp > input)
                    break;
                res += input / temp;
            }
            System.out.printf("%d\n", res);
        }
        in.close();
    }
}