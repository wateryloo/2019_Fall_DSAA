import java.util.ArrayList;
import java.util.Scanner;

public class Lab6_B {
    public static void main(String[] args) {
        Scanner in = new Scanner(System.in);
        int testcases = in.nextInt();
        while (testcases-- > 0) {
            int nodes = in.nextInt();
            ArrayList<Integer>[] adjacent_list = new ArrayList[nodes + 1];
            for (int i = 0; i <= nodes; ++i)
                adjacent_list[i] = new ArrayList<>();
            int[] res = new int[nodes + 1];
            for (int i = 1; i < nodes; ++i) {
                int temp1 = in.nextInt();
                int temp2 = in.nextInt();
                adjacent_list[temp1].add(temp2);
                adjacent_list[temp2].add(temp1);
            }
            traverse(-1, 1, 0, adjacent_list, res);
            for (int i = 1; i <= nodes; ++i)
                System.out.print(res[i] + " ");
            System.out.println();
        }
    }

    private static void traverse(int from, int parent, int depth, ArrayList<Integer>[] adjacent_list, int[] res) {
        res[parent] = depth;
        int size = adjacent_list[parent].size();
        for (int i = 0; i < size; ++i) {
            if (adjacent_list[parent].get(i) == from)
                continue;
            traverse(parent, adjacent_list[parent].get(i), depth + 1, adjacent_list, res);
        }
    }
}