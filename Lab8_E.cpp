#include <iostream>
#include <vector>
#include <queue>
#define max_size 200001

using namespace std;

struct vertex {
    int val;
    int incoming_degree;
    vector<int> outgoing;
};

void rootfix(vertex* heap[max_size], int heap_last_index);
void swap(vertex*& a, vertex*& b);
void push(vertex* heap[max_size], int heap_last_index, vertex*& in);
vertex* pop(vertex* heap[max_size], int heap_last_index);
inline int choose_larger_index(vertex* heap[max_size], int left);
inline int left(int i);
inline int parent(int i);

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int testcase_number;
    int vertex_number;
    int edge_number;
    int i;
    int j;
    int output[max_size];
    vertex* map[max_size];
    vertex* temp;
    priority_queue<int> q;
    cin >> testcase_number;
    while (testcase_number > 0) {
        --testcase_number;
        i = 1;
        j = 0;
        cin >> vertex_number >> edge_number;

        while (i <= vertex_number) {    // Initialize each struct.
            map[i] = new vertex;
            map[i]->val = i;
            map[i]->incoming_degree = 0;
            ++i;
        }

        while (edge_number > 0) {   // Initialize edges.
            --edge_number;
            cin >> i >> j;
            ++map[i]->incoming_degree;
            map[j]->outgoing.push_back(i);
        }

        i = 1;
        j = 0;  // Size of heap.

        while (i <= vertex_number) {
            if (!map[i]->incoming_degree) {
                q.push(i);
            }
            ++i;
        }

        i = 0;  // Dynamically update the heap.
        j = 1;

        while (!q.empty()) {
            i = q.top();
            q.pop();
            temp = map[i];
            for (int iter : temp->outgoing) {
                if (!map[iter]->incoming_degree) {
                    continue;
                }
                --map[iter]->incoming_degree;
                if (!map[iter]->incoming_degree) {
                    q.push(iter);
                }
            }
            output[vertex_number - j] = temp->val;
            ++j;
        }

        i = 0;  // Print the result.
        while (i < vertex_number) {
            cout << output[i] << ' ';
            ++i;
        }
        cout << endl;

        i = 1;
        while (i <= vertex_number) {
            delete(map[i]);
            ++i;
        }
    }
    return 0;
}

void rootfix(vertex* heap[max_size], int heap_last_index) {
    int larger_index;
    int heap_index = heap_last_index;
    int temp_index;
    while (heap_index > -1) {
        temp_index = heap_index;
        while (temp_index < heap_last_index) {
            if (left(temp_index) > heap_last_index) {
                break;
            }
            else if (left(temp_index) == heap_last_index) {
                if (heap[temp_index]->val < heap[left(temp_index)]->val) {
                    swap(heap[temp_index], heap[left(temp_index)]);
                }
                break;
            }
            else {
                larger_index = choose_larger_index(heap, left(temp_index));
                if (heap[temp_index] < heap[larger_index]) {
                    swap(heap[temp_index], heap[larger_index]);
                    temp_index = larger_index;
                }
                else {
                    break;
                }
            }
        }
        --heap_index;
    }
}

void swap(vertex*& a, vertex*& b) {
    vertex* temp = a;
    a = b;
    b = temp;
}

void push(vertex* heap[max_size], int heap_last_index, vertex*& in) {
    ++heap_last_index;
    heap[heap_last_index] = in;
    while (heap_last_index) {
        if (heap[heap_last_index]->val > heap[parent(heap_last_index)]->val) {
            swap(heap[heap_last_index], heap[parent(heap_last_index)]);
            heap_last_index = parent(heap_last_index);
        }
        else {
            break;
        }
    }
}

vertex* pop(vertex* heap[max_size], int heap_last_index) {
    vertex* temp = heap[0];
    heap[0] = heap[heap_last_index];
    int heap_index = 0;
    int larger_index;
    --heap_last_index;
    while (heap_index < heap_last_index) {
        if (left(heap_index) > heap_last_index) {
            break;
        }
        else if (left(heap_index) == heap_last_index) {
            if (heap[heap_index]->val < heap[heap_last_index]->val) {
                swap(heap[heap_index], heap[heap_last_index]);
            }
            break;
        }
        else {
            larger_index = choose_larger_index(heap, left(heap_index));
            if (heap[heap_index] < heap[larger_index]) {
                swap(heap[heap_index], heap[larger_index]);
                heap_index = larger_index;
            }
            else {
                break;
            }
        }
    }
    return temp;
}

inline int choose_larger_index(vertex* heap[max_size], int left) {
    return heap[left]->val > heap[left + 1]->val ? left : left + 1;
}

inline int left(int i) {
    return 2 * i + 1;
}

inline int parent(int i) {
    return (i - 1) / 2;
}