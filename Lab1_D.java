import java.util.Scanner;

public class Lab1_D {
    public static void main(String[] args) {

        /*
        * Read length of array and target number.
        * */
        Scanner in = new Scanner(System.in);
        int length = in.nextInt();
        in.nextLine();
        long target = in.nextLong();
        in.nextLine();

        /*
        * Read the array as a string.
        * */
        String inputS = in.nextLine();

        /*
        * Condition that target == 0 but the string does not contain 0
        * */
        if (target == 0 && !inputS.contains("0")) {
            System.out.println(0);
            return;
        }

        String[] inputSArray = inputS.split(" ");

        /*
        * Condition that target < 0 but the smallest number in array is not a negative number.
        * */
        if (target < 0 && inputS.charAt(0) != '-') {
            System.out.println(0);
            return;
        }

        /*
        * Parse string array to a long array, and record the first position and last position of 0.
        * */
        long[] array = new long[length];
        int firstIndexOfZero = -1;
        int lastIndexOfZero = -1;
        int firstIndexOfPositive = -1;
        int lastIndexOfNegative = -1;
        for (int i = 0; i < length; ++i) {
            array[i] = Long.parseLong(inputSArray[i]);
            if (array[i] == 0) {
                lastIndexOfZero = i;
                if (firstIndexOfZero == -1)
                    firstIndexOfZero = i;
            }
            if (array[i] > 0 && firstIndexOfPositive == -1)
                firstIndexOfPositive = i;
            if (array[i] < 0)
                lastIndexOfNegative = i;
        }

        if (target < 0 && array[0] >= 0) {
            System.out.println(0);
            return;
        }

        /*
        * Start to use binary search to count the result.
        * Condition that target < 0, the first operand must be negative and the second operand must be positive.
        * Therefore, the outer loop ends at the index of first nonnegative number,
        * and the first left of binary search is the first index of positive number.
        * */
        if (target < 0) {

            /*
            * Eliminate the condition that there is only nonpositive numbers.
            * */
            if (array[array.length - 1] <= 0) {
                System.out.println(0);
                return;
            }

            /*
            * Binary search. There must be at least one positive number and one negative number.
            * */
            long res = 0;
            long prev = array[0];
            int loopEnd = firstIndexOfZero == -1 ? firstIndexOfPositive : firstIndexOfZero;
            for (int i = 0; i < loopEnd; ++i) {

                /*
                * Avoid repeat.
                * */
                if (i != 0 && array[i] == prev) {
//                    prev = array[i];
                    continue;
                }

//                if (array[i] == 0)
//                    continue;

                /*
                * Ensure that array[i] is a factor of target.
                * */
                if (target % array[i] != 0)
                    continue;

                boolean incre = false;
                int left = firstIndexOfPositive;
                int right = length - 1;
                int mid = left + (right - left) / 2;
                while (left < right - 1) {
                    mid = left + (right - left) / 2;
                    if (array[mid] == target / array[i]) {
                        incre = true;
                        ++res;
                        break;
                    }
                    if (array[mid] < target / array[i])
                        left = mid;
                    else
                        right = mid;
                }
                if (!incre) {
                    if (array[left] == target / array[i] ||
                        array[mid] == target / array[i] ||
                        array[right] == target / array[i])
                        ++res;
                }
                prev = array[i];
            }
            System.out.println(res);
        }

        /*
        * Condition that target is 0.
        * This condition is kind of simple. It is just like a condensed array, with attention to 0 * 0.
        * */
        else if (target == 0) {
            long res = inputS.contains("0 0") ? 1 : 0;
            long prev = array[0];
            for (int i = 0; i < length; ++i) {
                if (array[i] != 0 && (i == 0 || array[i] != prev)) {
                    ++res;
                    prev = array[i];
                }
            }
            System.out.println(res);
        }

        /*
        * Condition that target > 0.
        * This is the most complicated condition.
        * */
        else {
            long res = 0;
            long prev = array[0];
            int loopEnd = lastIndexOfNegative - 1;
            for (int i = 0; i < loopEnd; ++i) {

                if (i != 0 && array[i] == prev) {
//                    prev = array[i];
                    continue;
                }

                if (target % array[i] != 0)
                    continue;

                boolean incre = false;
                int left = i + 1;
                int right = lastIndexOfNegative;
                int mid = left + (right - left) / 2;
                while (left < right - 1) {
                    mid = left + (right - left) / 2;
                    if (array[mid] == target / array[i]) {
                        incre = true;
                        ++res;
                        break;
                    }
                    if (array[mid] < target / array[i])
                        left = mid;
                    else
                        right = mid;
                }
                if (!incre) {
                    if (array[left] == target / array[i] ||
                            array[mid] == target / array[i] ||
                            array[right] == target / array[i])
                        ++res;
                }
                prev = array[i];
            }

            if (firstIndexOfPositive != -1) {
                prev = array[firstIndexOfPositive];
                for (int i = firstIndexOfPositive; i < length - 1; ++i) {

                    if (i != firstIndexOfPositive && array[i] == prev) {
//                    prev = array[i];
                        continue;
                    }

                    if (target % array[i] != 0)
                        continue;

                    boolean incre = false;
                    int left = i + 1;
                    int right = length - 1;
                    int mid = left + (right - left) / 2;
                    while (left < right - 1) {
                        mid = left + (right - left) / 2;
                        if (array[mid] == target / array[i]) {
                            incre = true;
                            ++res;
                            break;
                        }
                        if (array[mid] < target / array[i])
                            left = mid;
                        else
                            right = mid;
                    }
                    if (!incre) {
                        if (array[left] == target / array[i] ||
                                array[mid] == target / array[i] ||
                                array[right] == target / array[i])
                            ++res;
                    }
                    prev = array[i];
                }
            }

            System.out.print(res);
        }
    }
}