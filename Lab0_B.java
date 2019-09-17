import java.util.ArrayList;
import java.util.Scanner;

public class Lab0_B {
    private final static String s = "123456789";
    private final static int ROW = 0;
    private final static int COL = 1;

    public static void main(String[] args) {
        Scanner in = new Scanner(System.in);
        String[][] grid = new String[9][9];
        ArrayList<Integer[]> coordinates = new ArrayList<>();
        for (int i = 0; i < 9; ++i) {
            if (i == 3 || i == 6)
                in.nextLine();
            String inputString = in.nextLine();
            inputString = inputString.substring(0, 6) + inputString.substring(8, 14)
                        + inputString.substring(16, 22);
            grid[i] = inputString.split(" ");
            int xCount = 0;
            int sum = 0;
            int[] coordinate = {0, 0};
            for (int j = 0; j < 9; ++j) {
                if (grid[i][j].equals("x")) {
                    ++xCount;
                    coordinate[0] = i;
                    coordinate[1] = j;
                }
            }
            if (xCount == 1) {
                for (int j = 0; j < 9; ++j) {
                    if (!grid[i][j].equals("x"))
                        sum += Integer.parseInt(grid[i][j]);
                }
                grid[coordinate[ROW]][coordinate[COL]] = Integer.toString(45 - sum);
            }
        }

        for (int rowNum = 0; rowNum < 9; ++rowNum) {
            for (int colNum = 0; colNum < 9; ++colNum) {
                if (grid[rowNum][colNum].equals("x")) {
                    Integer[] coordinate = new Integer[2];
                    coordinates.add(coordinate);
                    coordinate[ROW] = rowNum;
                    coordinate[COL] = colNum;
                }
            }
        }

        for (int i = 0; i < coordinates.size(); ++i) {
            Integer[] coordinate = coordinates.get(i);
            int xCount = 0;
            int sum = 0;
            for (int colNum = 0; colNum < 9; ++colNum) {
                String temp = grid[coordinate[ROW]][colNum];
                if (temp.equals("x"))
                    ++xCount;
                else
                    sum += Integer.parseInt(temp);
            }
            if (xCount == 1) {
                grid[coordinate[ROW]][coordinate[COL]] = Integer.toString(45 - sum);
                coordinates.remove(i);
                i = -1;
                continue;
            }

            xCount = 0;
            sum = 0;
            for (int rowNum = 0; rowNum < 9; ++rowNum) {
                String temp = grid[rowNum][coordinate[COL]];
                if (temp.equals("x"))
                    ++xCount;
                else
                    sum += Integer.parseInt(temp);
            }
            if (xCount == 1) {
                grid[coordinate[ROW]][coordinate[COL]] = Integer.toString(45 - sum);
                coordinates.remove(i);
                i = -1;
                continue;
            }

            xCount = 0;
            sum = 0;
            int startRowNum = coordinate[ROW] - coordinate[ROW] % 3;
            int startColNum = coordinate[COL] - coordinate[COL] % 3;
            for (int rowNum = startRowNum; rowNum < startRowNum + 3; ++rowNum) {
                for (int colNum = startColNum; colNum < startColNum + 3; ++colNum) {
                    String temp = grid[rowNum][colNum];
                    if (temp.equals("x"))
                        ++xCount;
                    else
                        sum += Integer.parseInt(temp);
                }
            }
            if (xCount == 1) {
                grid[coordinate[ROW]][coordinate[COL]] = Integer.toString(45 - sum);
                coordinates.remove(i);
                i = -1;
            }
        }

        if (coordinates.size() <= 0) {
            for (int row = 0; row < 9; ++row) {
                if (row == 3 || row == 6) {
                    System.out.println();
                }
                for (int col = 0; col < 9; ++col) {
                    if (col == 2 || col == 5) System.out.printf("%s | ", grid[row][col]);
                    else if (col == 8) {
                        if (row != 8)
                            System.out.printf("%s |\n", grid[row][col]);
                        else {
                            System.out.printf("%s |", grid[row][col]);
                        }
                    }
                    else System.out.printf("%s ", grid[row][col]);
                }
            }
        }
        else
            System.out.print("The test data is incorrect!");
        in.close();
    }
}
