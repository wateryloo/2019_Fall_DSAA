#include <iostream>

#define ll long long

ll generate_data(ll second, ll seed);
void heap_add(ll* heap, int heap_index, ll number);
void min_heapify_at_head(ll* heap, int heap_size);
inline void swap(ll& a, ll& b);

int main() {
    ll second = 0;
    ll total_second;
    int heap_capacity;
    int heap_size = 0;
    ll seed;
    ll data;
    scanf(" %lld %d %lld", &total_second, &heap_capacity, &seed);
    ll* heap = new ll[heap_capacity]();
    while (second < total_second) {
        second = second + 1;
        data = generate_data(second, seed);
        if (heap_size < heap_capacity) {
            heap_add(heap, heap_size, data);
            ++heap_size;
        }
        else if (data > heap[0]) {
            heap[0] = data;
            min_heapify_at_head(heap, heap_capacity);
        }
        if (second % 100 == 0) {
            seed = heap[0];
            printf("%lld ", seed);
        }
    }
    return 0;
}

ll generate_data(ll second, ll last_ans) {
    ll function_input = second + last_ans;
    ll function_output = function_input;
    while (function_input > 0LL) {
        function_output += function_input % 10LL;
        function_input = function_input / 10LL;
    }
    return function_output;
}

void heap_add(ll* heap, int heap_index, ll number) {
    heap[heap_index] = number;
    while (heap_index > 0) {
        if (heap[heap_index] < heap[(heap_index - 1) / 2]) {
            swap(heap[heap_index], heap[(heap_index - 1) / 2]);
            heap_index = (heap_index - 1) / 2;
        }
        else {
            break;
        }
    }
}

void min_heapify_at_head(ll* heap, int heap_size) {
    int heap_index = 0;
    while (true) {
        if (heap_index * 2 + 1 > heap_size - 1) {
            break;
        }
        else if (heap_index * 2 + 2 > heap_size - 1) {
            if (heap[heap_index] > heap[heap_index * 2 + 1]) {
                swap(heap[heap_index], heap[heap_size - 1]);
            }
            break;
        }
        else {
            int min_index = heap_index * 2 + 1;
            if (heap[min_index] > heap[min_index + 1]) {
                ++min_index;
            }
            if (heap[heap_index] > heap[min_index]) {
                swap(heap[heap_index], heap[min_index]);
                heap_index = min_index;
            }
            else {
                break;
            }
        }
    }
}

inline void swap(ll& a, ll& b) {
    ll temp = a;
    a = b;
    b = temp;
}