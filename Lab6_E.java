import java.util.ArrayList;
        import java.util.Scanner;

public class Lab6_E {
    private static int red_count;
    private static int blue_count;
    private static ArrayList<Integer>[] nodes;
    private static int[] nodes_color;
    private static int res;

    public static void main(String[] args) {
        Scanner in = new Scanner(System.in);
        int testcase_number = in.nextInt();
        while (testcase_number-- > 0) {
            res = 0;
            int node_number = in.nextInt();
            if (node_number == 1) {
                System.out.println(0);
                continue;
            }
            red_count = 0;
            blue_count = 0;
            nodes = new ArrayList[node_number + 1];
            nodes_color = new int[node_number + 1];
            for (int i = 0; i <= node_number; ++i)
                nodes[i] = new ArrayList<Integer>();
            for (int i = 0; i < node_number - 1; ++i) {
                int temp1 = in.nextInt();
                int temp2 = in.nextInt();
                nodes[temp1].add(temp2);
                nodes[temp2].add(temp1);
            }
            for (int i = 1; i <= node_number; ++i) {
                int temp = in.nextInt();
                if (temp == 1)
                    ++red_count;
                else if (temp == 2)
                    ++blue_count;
                nodes_color[i] = temp;
            }
            int[] color_count = {0, 0};
            helper(-1, 1, color_count);
            System.out.println(res);
        }
    }

    private static void helper(int parent, int self, int[] color_count) {
        int size = nodes[self].size();
        int red_increment = 0;
        int blue_increment = 0;
        for (int i = 0; i < size; ++i) {
            int[] temp_color_count = color_count.clone();
            if (nodes[self].get(i) == parent)
                continue;
            helper(self, nodes[self].get(i), temp_color_count);
            red_increment += temp_color_count[0] - color_count[0];
            blue_increment += temp_color_count[1] - color_count[1];
        }
        color_count[0] += red_increment;
        color_count[1] += blue_increment;
        if (nodes_color[self] != 0)
            ++color_count[nodes_color[self] - 1];
        if (color_count[0] == red_count && color_count[1] == 0)
            ++res;
        else if (color_count[0] == 0 && color_count[1] == blue_count)
            ++res;
    }
}