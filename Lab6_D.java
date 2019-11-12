import java.util.ArrayList;
        import java.util.Arrays;
        import java.util.Scanner;

public class Lab6_D {
    public static void main(String[] args) {
        Scanner in = new Scanner(System.in);
        int testcase_number = in.nextInt();
        while (testcase_number-- > 0) {
            long total = 0;
            int stick_number = in.nextInt();
            long[] sticks_temp = new long[stick_number];
            for (int i = 0; i < stick_number; ++i)
                sticks_temp[i] = in.nextLong();
            Arrays.sort(sticks_temp);
            ArrayList<Long> sticks = new ArrayList<>();
            for (int i = 0; i < stick_number; ++i)
                sticks.add(sticks_temp[i]);
            while (sticks.size() > 1) {
                long temp = sticks.remove(0) + sticks.remove(0);
                total += temp;
                int temp_size = sticks.size();
                if (temp_size == 0 || temp_size == 1)
                    sticks.add(temp);
                else {
                    for (int i = 0; i < temp_size; ++i)
                        if (temp < sticks.get(i)) {
                            sticks.add(i, temp);
                            break;
                        }
                    if (sticks.size() == temp_size)
                        sticks.add(temp_size, temp);
                }
            }
            System.out.println(total);
        }
        in.close();
    }
}