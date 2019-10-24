#include <iostream>

int main() {
    const int CAPACITY = 2000000;
    const int SIZE = CAPACITY + 1;
    int width, input, max = 0, front = 0, rear = 0, count = 0, input_index = 0, output_index = 0;
    int queue[2000001] = {0};
    int index_queue[2000001] = {0};
    scanf(" %d", &width);

    while (input_index < width - 1) {
        scanf(" %d", &input);
        if (input_index) {
            for (int i = front; i % SIZE != rear; ++i) {
                if (queue[i] <= input) {
                    rear = i;
                    break;
                }
            }
            queue[rear] = input;
            index_queue[rear++] = input_index;
        }
        else
            queue[rear++] = input;
        ++input_index;
    }

    while (true) {
        scanf(" %d", &input);
        if (input == -1) {
            break;
        }

        for (int i = front; i % SIZE != rear; i = (i + 1) % SIZE) {
            if (queue[i] <= input) {
                rear = i;
                break;
            }
        }

        queue[rear] = input;
        index_queue[rear] = input_index;
        rear = (rear + 1) % SIZE;

        ++output_index;
        max = max ^ queue[front];
        if (output_index > index_queue[front])
            front = (front + 1) % SIZE;
        ++input_index;
    }

    printf("%d", max);
    return 0;
}