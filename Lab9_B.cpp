#include <iostream>
#include <vector>
#include <climits>

using namespace std;

struct vertex {
    int index;
    bool in_mst;
    int distance;
    vector<int> edges;
    vector<int> weight;

    explicit vertex(int& index) {
        this->index = index;
        this->in_mst = false;
        this->distance = INT_MAX;
    }
};

inline int parent(int i);
inline int left(int i);
inline int right(int i);
void swap(vertex*& a, vertex*& b);
vertex* pop(int size, vertex* heap[1001]);
void min_heapify(int size, vertex* heap[1001], int index);
void decrease_key(int size, vertex* heap[1001], int index, int val);

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int VERTEX_NUMBER;
    int EDGE_NUMBER;
    int i;
    int j;
    int k;
    int l;
    int res = 0;
    vertex* temp;
    vertex* heap[1001];
    vertex* vertices[1001];
    cin >> VERTEX_NUMBER >> EDGE_NUMBER;

    i = 0;
    while (i++ < VERTEX_NUMBER) {
        vertices[i] = new vertex(i);
        heap[i] = vertices[i];
    }

    i = 0;
    while (i++ < EDGE_NUMBER) {
        cin >> j >> k >> l;
        vertices[j]->edges.push_back(k);
        vertices[j]->weight.push_back(l);
        vertices[k]->edges.push_back(j);
        vertices[k]->weight.push_back(l);
    }

    // j is size of heap.
    j = VERTEX_NUMBER;
    while (j > 0) {
        temp = pop(j, heap);
        if (j == VERTEX_NUMBER) {
            temp->distance = 0;
        }
        res += temp->distance;
        --j;
        temp->in_mst = true;
        while (!temp->edges.empty()) {
            k = temp->edges.back();
            temp->edges.pop_back();
            l = temp->weight.back();
            temp->weight.pop_back();
            if (vertices[k]->in_mst) {
                continue;
            }
            decrease_key(j, heap, vertices[k]->index, l);
        }
    }

    cout << res << endl;

    return 0;
}

inline int parent(int i) {
    if (i > 1) {
        return i  / 2;
    }
    return 0;
}

inline int left(int i) {
    if (i < 1) {
        return -1;
    }
    return 2 * i;
}

inline int right(int i) {
    if (i < 1) {
        return -1;
    }
    return 2 * i + 1;
}

void swap(vertex*& a, vertex*& b) {
    vertex* i = a;
    a = b;
    b = i;
    int t = a->index;
    a->index = b->index;
    b->index = t;
}

vertex* pop(int size, vertex* heap[1001]) {
    vertex* res = heap[1];
    heap[1] = heap[size];
    heap[1]->index = 1;
    --size;
    min_heapify(size, heap, 1);
    return res;
}

void min_heapify(int size, vertex* heap[1001], int index) {
    int l = left(index);
    int r = right(index);
    int smallest = index;
    if (l < size && heap[l]->distance < heap[smallest]->distance) {
        smallest = l;
    }
    if (r < size && heap[r]->distance < heap[smallest]->distance) {
        smallest = r;
    }
    if (smallest != index) {
        swap(heap[index], heap[smallest]);
        min_heapify(size, heap, smallest);
    }
}

void decrease_key(int size, vertex* heap[1001], int index, int val) {
    if (index > size) {
        return;
    }
    if (val >= heap[index]->distance) {
        return;
    }
    heap[index]->distance = val;
    while (index > 1 && heap[parent(index)]->distance > heap[index]->distance) {
        swap(heap[parent(index)], heap[index]);
        index = parent(index);
    }
}