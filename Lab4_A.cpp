#include <iostream>

#define SIZE 20000001

int main() {
    int* queue = new int[SIZE];
    int operation_number, front = 0, rear = 0;
    char operation;
    scanf(" %d", &operation_number);
    while (operation_number-- > 0) {
        scanf(" %c", &operation);
        if (operation == 'E') {
            scanf(" %d", &queue[rear]);
            rear = (rear + 1) % SIZE;
        }
        else if (operation == 'D')
            front = (front + 1) % SIZE;
        else 
            printf("%d\n", queue[front]);
    }
    if (front < rear) {
        while (front < rear) 
            printf("%d ", queue[front++]);
    }
    else {
        while (front < rear + SIZE)
            printf("%d ", queue[front++ % SIZE]);
    }
    delete[] queue;
    return 0;
}