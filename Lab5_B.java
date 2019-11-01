import java.util.Scanner;

public class Lab5_B {
    public static void main(String[] args) {
        Scanner in = new Scanner(System.in);
        int count;
        String s1;
        String s2;
        count = in.nextInt();
        in.nextLine();
        while (count-- > 0) {
            in.nextLine();
            s1 = in.nextLine();
            s2 = in.nextLine();
            if (s1.equals("*"))
                System.out.println("YES");
            else if (s1.equals(s2))
                System.out.println("YES");
            else {
                if (s1.contains("*")) {
                    if (s1.indexOf('*') == 0) {
                        if (s2.endsWith(s1.substring(1, s1.length())))
                            System.out.println("YES");
                        else
                            System.out.println("NO");
                    }
                    else if (s1.indexOf('*') == s1.length() - 1) {
                        if (s2.startsWith(s1.substring(0, s1.length() - 1)))
                            System.out.println("YES");
                        else
                            System.out.println("NO");
                    }
                    else {
                        String[] fix = s1.split("\\*");
                        if (s2.startsWith(fix[0]) && s2.endsWith(fix[1]) && fix[0].length() + fix[1].length() <= s2.length())
                            System.out.println("YES");
                        else
                            System.out.println("NO");
                    }
                }
                else
                    System.out.println("NO");
            }
        }
    }
}