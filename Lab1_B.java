/*
* The template of binary search is from leetcode.
* */

import java.util.Scanner;

public class Lab1_B {
    public static void main(String[] args) {
        Scanner in = new Scanner(System.in);
        int days = in.nextInt();
        in.nextLine();
        int kinds = in.nextInt();
        in.nextLine();
        int money[] = new int[days];
        int price[] = new int[kinds];
        for (int i = 0; i < days; ++i) {
            money[i] = in.nextInt();
        }
        in.nextLine();
        for (int i = 0; i < kinds; ++i) {
            price[i] = in.nextInt();
        }
        int left;
        int right;
        for (int i = 0; i < days; ++i) {
            boolean hasPrint = false;
            left = 0;
            right = kinds - 1;
            while (left + 1 < right) {
                int mid = left + (right - left) / 2;
                if (price[mid] == money[i]) {
                    System.out.println("Meow");
                    hasPrint = true;
                    break;
                }
                else if (price[mid] < money[i])
                    left = mid;
                else
                    right = mid;
            }
            if (hasPrint)
                continue;
            if (price[left] == money[i] || price[right] == money[i])
                System.out.println("Meow");
            else if (price[right] < money[i])
                System.out.println(money[i] - price[right]);
            else if (price[left] < money[i])
                System.out.println(money[i] - price[left]);
            else
                System.out.println(money[i]);
        }
    }
}
