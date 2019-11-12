import java.util.Scanner;

public class Lab6_C {
    static int[] preorder;
    static int[] inorder;

    public static void main(String[] args) {
        Scanner in = new Scanner(System.in);
        int testcase_number = in.nextInt();
        while (testcase_number-- > 0) {
            int node_number = in.nextInt();
            preorder = new int[node_number];
            inorder = new int[node_number];
            for (int i = 0; i < node_number; ++i)
                preorder[i] = in.nextInt();
            for (int i = 0; i < node_number; ++i)
                inorder[i] = in.nextInt();
            helper(0, 0, node_number - 1);
            System.out.println();
        }
    }

    private static void helper(int pre_start, int in_start, int in_end) {
        if (in_start == in_end) {
            System.out.print(inorder[in_end] + " ");
            return;
        }
        int temp = preorder[pre_start];
        int start_index = in_start;
        while (inorder[start_index] != temp)
            ++start_index;
        if (start_index != in_start)
            helper(pre_start + 1, in_start, start_index - 1);
        if (start_index != in_end)
            helper(pre_start + 1 + start_index - in_start, start_index + 1, in_end);
        System.out.print(inorder[start_index] + " ");
    }
}