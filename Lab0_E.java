import java.util.Scanner;

public class Lab0_E {
    public static void main(String[] args){
        Scanner in = new Scanner(System.in);
        int count = in.nextInt();
        in.nextLine();
        while (count-- > 0) {
            String input = in.nextLine();
            if (input.charAt(0) == '(')
                coordinateToNumber(input);
            else
                numberToCoordinate(Long.parseLong(input));
            if (count > 0)
                System.out.println();
        }
    }

    private static void coordinateToNumber(String coordinateString){   // 0 for y, 1 for x.
        String[] temp = coordinateString.substring(1, coordinateString.length() - 1).split(",");
        long[] coordinate = new long[2];
        coordinate[0] = Long.parseLong(temp[0]);
        coordinate[1] = Long.parseLong(temp[1]);
        long level = (long)Math.ceil(Math.log(Math.max(coordinate[0], coordinate[1])) / Math.log(2));
        long yMax = pow(2, level);
        long xMax = yMax;
        long yMin = 1;
        long xMin = 1;
        long totalNum = pow(4, level);
        long res = totalNum;
        while (totalNum > 1) {
            totalNum = totalNum / 4;
            if (coordinate[0] > yMin + (yMax - yMin) / 2) {
                if (coordinate[1] > xMin + (xMax - xMin) / 2) {
                    res -= totalNum;
                    yMin += (yMax - yMin) / 2 + 1;
                    xMin += (xMax - xMin) / 2 + 1;
                }
                else {
                    res -= 2 * totalNum;
                    yMin += (yMax - yMin) / 2 + 1;
                    xMax = xMin + (xMax - xMin) / 2;
                }
            }
            else {
                if (coordinate[1] > xMin + (xMax - xMin) / 2) {
                    yMax = yMin + (yMax - yMin) / 2;
                    xMin += (xMax - xMin) / 2 + 1;
                }
                else {
                    res -= 3 * totalNum;
                    yMax = yMin + (yMax - yMin) / 2;
                    xMax = xMin + (xMax - xMin) / 2;
                }
            }
        }
        System.out.print(res);
    }

    private static void numberToCoordinate(long number) {
        if (number == 1) {
            System.out.print("(1,1)");
            return;
        }
        long loScale = 1;
        long hiScale = (long)Math.pow(2, (long)Math.ceil(Math.log(number) / Math.log(4)));
        if (loScale == hiScale) {
            System.out.printf("(%d,%d)", 1, hiScale);
            return;
        }
        String operations = "";
        long temp = number - 1;
        while (temp / 4 >= 1) {
            operations = Long.toString(temp % 4) + operations;
            temp = temp / 4;
        }
        operations = temp % 4 + operations;
        long[] coordinate = {hiScale,hiScale};
        long yLefNum = loScale;
        long yRigNum = hiScale;
        long xLefNum = loScale;
        long xRigNum = hiScale;
        for (int i = 0; i < operations.length(); ++i) {
            if (operations.substring(i, i + 1).equals("0")) {
                yRigNum = yLefNum + (yRigNum - yLefNum) / 2;
                xRigNum = xLefNum + (xRigNum - xLefNum) / 2;
            }
            else if (operations.substring(i, i + 1).equals("1")) {
                yLefNum = yLefNum + (yRigNum - yLefNum) / 2 + 1;
                xRigNum = xLefNum + (xRigNum - xLefNum) / 2;
            }
            else if (operations.substring(i, i + 1).equals("2")) {
                yLefNum = yLefNum + (yRigNum - yLefNum) / 2 + 1;
                xLefNum = xLefNum + (xRigNum - xLefNum) / 2 + 1;
            }
            else {
                yRigNum = yLefNum + (yRigNum - yLefNum) / 2;
                xLefNum = xLefNum + (xRigNum - xLefNum) / 2 + 1;
            }
        }
        coordinate[0] = yLefNum;
        coordinate[1] = xLefNum;
        System.out.printf("(%d,%d)", coordinate[0], coordinate[1]);
    }

    private static long pow(long base, long exp) {
        if (exp == 0)
            return 1;
        return base * pow(base, exp - 1);
    }
}
