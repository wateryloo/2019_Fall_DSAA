#include <iostream>

int main() {
    int testcase_number;
    int city_number;
    int road_number;
    int from;
    int to;
    int i;
    scanf(" %d", &testcase_number);
    while (testcase_number-- > 0) {
        i = 0;
        scanf(" %d %d", &city_number, &road_number);
        int* adjacent_matrix = new int[city_number * city_number];
        while (road_number-- > 0) {
            scanf(" %d %d", &from, &to);
            ++adjacent_matrix[(from - 1) * city_number + (to - 1)];
        }
        while (i < city_number) {
            while (road_number < city_number) {
                printf("%d ", adjacent_matrix[i * city_number + road_number]);
                ++road_number;
            }
            printf("\n");
            ++i;
        }
        delete[] adjacent_matrix;
    }
    return 0;
}