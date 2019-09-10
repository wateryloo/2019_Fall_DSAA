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

        /*
        * Add coordinates.
        * */
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


//    private static String[][] grid;
//    private static ArrayList<Integer[]> coordinates;
//    public static void main(String[] args) {
//        grid = new String[9][9];
//        coordinates = new ArrayList<>();
//        Scanner in = new Scanner(System.in);
//        for (int i = 0; i < 9; ++i) {
//            if (i == 3 || i == 6) {
//                in.nextLine();
//            }
//            String s = in.nextLine();
//            s = s.substring(0, 6) + s.substring(8, 14) + s.substring(16, 22);
//            grid[i] = s.split(" ");
//            for (int col = 0; col < 9; ++col) {
//                if (grid[i][col].equals("x")) {
//                    Integer[] temp = {i, col};
//                    coordinates.add(temp);
//                }
//            }
//        }
//        boolean isPossible = fillSudoku();
//        if (isPossible) {
//            for (int row = 0; row < 9; ++row) {
//                if (row == 3 || row == 6) {
//                    System.out.println();
//                }
//                for (int col = 0; col < 9; ++col) {
//                    if (col == 2 || col == 5) System.out.printf("%s | ", grid[row][col]);
//                    else if (col == 8) {
//                        if (row != 8)
//                            System.out.printf("%s |\n", grid[row][col]);
//                        else {
//                            System.out.printf("%s |", grid[row][col]);
//                        }
//                    }
//                    else System.out.printf("%s ", grid[row][col]);
//                }
//            }
//        }
//        else System.out.println("impossible");
//    }
//
//    private static boolean fillSudoku() {
//        boolean valid = true;
//        for (int i = 0; i < coordinates.size(); ++i) {
//            Integer[] coordinate = coordinates.get(i);
//            for (int row_num = 0; row_num < 9; ++row_num) {
//                if (row_num == coordinate[0]) {
//                    if (coordinate[0] != 8)
//                        continue;
//                    else {
//                        valid = true;
//                        break;
//                    }
//                }
//                if (grid[row_num][coordinate[1]].equals("x")) {
//                    valid = false;
//                    break;
//                }
//            }
//            if (valid) {
//                int sum = 0;
//                for (int row_num = 0; row_num < 9; ++row_num) {
//                    if (row_num == coordinate[0]) continue;
//                    sum += Integer.parseInt(grid[row_num][coordinate[1]]);
//                }
//                grid[coordinate[0]][coordinate[1]] = Integer.toString(45 - sum);
//                coordinates.remove(i);
//                i = -1;
//                continue;
//            }
//
//            if (!valid) {
//                for (int col_num = 0; col_num < 9; ++col_num) {
//                    if (col_num == coordinate[1]) {
//                        if (coordinate[1] != 8)
//                            continue;
//                        else {
//                            valid = true;
//                            break;
//                        }
//                    }
//                    if (grid[coordinate[0]][col_num].equals("x")) break;
//                    if (col_num == 8) {
//                        valid = true;
//                        break;
//                    }
//                }
//            }
//            if (valid) {
//                int sum = 0;
//                for (int col_num = 0; col_num < 9; ++col_num) {
//                    if (col_num == coordinate[1]) continue;
//                    sum += Integer.parseInt(grid[coordinate[0]][col_num]);
//                }
//                grid[coordinate[0]][coordinate[1]] = Integer.toString(45 - sum);
//                coordinates.remove(i);
//                i = -1;
//                continue;
//            }
//
//            if (!valid) {
//                int start_row_num = coordinate[0] - coordinate[0] % 3;
//                int start_col_num = coordinate[1] - coordinate[1] % 3;
//                OUT:for (int row_num = start_row_num; row_num < start_row_num + 3; ++row_num) {
//                    for (int col_num = start_col_num; col_num < start_col_num + 3; ++col_num) {
//                        if (row_num == coordinate[0] && col_num == coordinate[1]) {
//                            if (!(row_num == start_row_num + 2 && col_num == start_col_num + 2))
//                                continue;
//                            else {
//                                valid = true;
//                                break OUT;
//                            }
//                        }
//                        if (grid[row_num][col_num].equals("x")) {
//                            break OUT;
//                        }
//                        if (row_num == start_row_num + 2 && col_num == start_col_num + 2) {
//                            valid = true;
//                            break OUT;
//                        }
//                    }
//                }
//            }
//            if (valid) {
//                int sum = 0;
//                int start_row_num = coordinate[0] - coordinate[0] % 3;
//                int start_col_num = coordinate[1] - coordinate[1] % 3;
//                for (int row_num = start_row_num; row_num < start_row_num + 3; ++row_num) {
//                    for (int col_num = start_col_num; col_num < start_col_num + 3; ++col_num) {
//                        if (row_num == coordinate[0] && col_num == coordinate[1]) continue;
//                        else sum += Integer.parseInt(grid[row_num][col_num]);
//                    }
//                }
//                grid[coordinate[0]][coordinate[1]] = Integer.toString(45 - sum);
//                coordinates.remove(i);
//                i = -1;
//                continue;
//            }
//        }
//        return coordinates.size() == 0;
//    }
}
