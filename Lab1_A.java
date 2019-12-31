import java.util.Scanner;
 
/*
 *Line 14 from https://www.quora.com/How-do-I-find-the-sum-of-1-2-2-3-3-4-n
 */
 
public class Lab1_A {
    public static void main(String[] args) {
        Scanner in = new Scanner(System.in);
        int count = in.nextInt();
        in.nextLine();
        while (count-- > 0) {
            long n = in.nextLong();
            long res = n * (n + 1) / 2 * (n + 2) / 3;
            System.out.print(res);
            if (count > 0)
                System.out.println();
        }
    }
}