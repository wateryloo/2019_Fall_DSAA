import java.util.Scanner;

public class Lab1_C {
    public static void main(String[] args) {
        Scanner in = new Scanner(System.in);
        int n = in.nextInt();
        int m = in.nextInt();
        if (n == 0 || n == 1)
            System.out.print(1 % m);
        else if (n == 2)
            System.out.print(2 % m);
        else if (n == 3) {
            if (m <= 720)
                System.out.print(0);
            else {
                long res = 1;
                for (long i = 2; i <= 720; ++i) {
                    res *= i;
                    res = res % m;
                }
                System.out.print(res);
            }
        }
        else
            System.out.print(0);
        in.close();
    }
}