import java.util.Scanner;
 
public class Lab0_A {
    public static void main(String[] args) {
        Scanner in = new Scanner(System.in);
        int count = in.nextInt();
        in.nextLine();
        while (count-- > 0) {
            String s = in.nextLine();
            s = in.nextLine();
            System.out.println(s.charAt(2));
            in.nextLine();
            if (count != 0) {
                in.nextLine();
            }
        }
        in.close();
    }
}