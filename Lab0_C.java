import java.util.ArrayList;
import java.util.Collections;
import java.util.Comparator;
import java.util.Scanner;

public class Lab0_C {
    public static void main(String[] args) {
        Scanner in = new Scanner(System.in);
        int count = in.nextInt();
        in.nextLine();
        while (count-- > 0) {
            String[] inputArray = in.nextLine().split(" ");
            ArrayList<Mahjong> mahjongArrayList = new ArrayList<>();
            for (String s : inputArray) {
                mahjongArrayList.add(new Mahjong(s));
            }
            Collections.sort(mahjongArrayList, new Comparator<Mahjong>() {
                @Override
                public int compare(Mahjong o1, Mahjong o2) {
                    if (o1.val < o2.val)
                        return 1;
                    if (o1.val > o2.val)
                        return -1;
                    return 0;
                }
            });
            for (int i = 0; i < mahjongArrayList.size(); ++i) {
                System.out.print(mahjongArrayList.get(i).name);
                if (i != mahjongArrayList.size() - 1)
                    System.out.print(" ");
            }
            if (count != 0)
                System.out.println();
        }
    }

    private static class Mahjong {
        private String name;
        private int val = -1;
        private Mahjong(String name) {
            this.name = name;
            switch (this.name) {
                case "Z" :
                    this.val = 0;
                    break;
                case "F" :
                    this.val = 1;
                    break;
                case "B" :
                    this.val = 2;
                    break;
                case "N" :
                    this.val = 3;
                    break;
                case "W" :
                    this.val = 4;
                    break;
                case "S" :
                    this.val = 5;
                    break;
                case "E" :
                    this.val = 6;
                    break;
                default :
                    break;
            }
            if (this.name.matches("Y[0-9]")) {
                this.val = 7 + 9 - Integer.parseInt(name.substring(1, 2));
            }
            else if (this.name.matches("T[0-9]")) {
                this.val = 17 + 9 - Integer.parseInt(name.substring(1, 2));
            }
            else if (this.name.matches("W[0-9]") && this.name.length() > 1) {
                this.val = 27 + 9 - Integer.parseInt(name.substring(1, 2));
            }
        }
    }
}
