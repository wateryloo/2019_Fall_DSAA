#include <iostream>
#include <vector>
#include <climits>
 
using namespace std;
 
struct vertex {
    int index;
    int distance;
    bool popped;
    vector<int> outgoing;
    vector<int> weight;
 
    explicit vertex(int index) {
        this->index = index;
        this->distance = INT_MAX;
        this->popped = false;
    }
};
 
inline int parent(int i);
inline int left(int i);
inline int right(int i);
void min_heapify(int size, vertex* heap[5000], int index);
void build_min_heap(int size, vertex* heap[5000]);
void swap(vertex*& a, vertex*& b);
void decrease_key(int size, vertex* heap[5000], int index, int val);
vertex* pop(int size, vertex* heap[5000]);
 
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int vertex_number;
    int edge_number;
    int i;
    int j;
    int k;
    int l;
    vertex* vertices[5000];
    vertex* heap[5000];
    vertex* temp;
    cin >> vertex_number >> edge_number;
    i = 0;
    while (i < vertex_number) {
        vertices[i] = new vertex(i);
        heap[i] = vertices[i];
        ++i;
    }
    i = 0;
    while (i < edge_number) {
        cin >> j >> k >> l;
        --j;
        --k;
        vertices[j]->outgoing.push_back(k);
        vertices[k]->outgoing.push_back(j);
        vertices[j]->weight.push_back(l);
        vertices[k]->weight.push_back(l);
        ++i;
    }
 
    // i and j are from and to.
    cin >> i >> j;
    --i;
    --j;
 
    vertices[i]->distance = 0;
    build_min_heap(vertex_number, heap);
 
    while (vertex_number > 0) {
        temp = pop(vertex_number, heap);
        --vertex_number;
        temp->popped = true;
        k = 0;
        while (k < temp->outgoing.size()) {
            if (vertices[temp->outgoing[k]]->popped) {
                ++k;
                continue;
            }
 
            l = temp->distance + temp->weight[k];
            if (l < vertices[temp->outgoing[k]]->distance) {
                decrease_key(vertex_number, heap, vertices[temp->outgoing[k]]->index, l);
            }
            ++k;
        }
    }
 
    if (vertices[j]->distance == INT_MAX) {
        printf("-1\n");
    }
    else {
        printf("%d\n", vertices[j]->distance);
    }
    return 0;
}
 
void min_heapify(const int size, vertex* heap[5000], const int index) {
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
 
void build_min_heap(int size, vertex* heap[5000]) {
    int i = parent(size);
    while (i > -1) {
        min_heapify(size, heap, i);
        --i;
    }
}
 
void swap(vertex*& a, vertex*& b) {
    vertex* i = a;
    a = b;
    b = i;
    int t = a->index;
    a->index = b->index;
    b->index = t;
}
 
void decrease_key(int size, vertex* heap[5000], int index, int val) {
    if (index >= size) {
        return;
    }
    if (val >= heap[index]->distance) {
        return;
    }
    heap[index]->distance = val;
    while (index > 0 && heap[parent(index)]->distance > heap[index]->distance) {
        swap(heap[parent(index)], heap[index]);
        index = parent(index);
    }
}
 
inline int parent(int i) {
    if (i > 0) {
        return (i - 1) / 2;
    }
    return -1;
}
 
inline int left(int i) {
    if (i < 0) {
        return -1;
    }
    return 2 * i + 1;
}
 
inline int right(int i) {
    if (i < 0) {
        return -1;
    }
    return 2 * i + 2;
}
 
vertex* pop(int size, vertex* heap[5000]) {
    vertex* res = heap[0];
    heap[0] = heap[size - 1];
    heap[0]->index = 0;
    --size;
    min_heapify(size, heap, 0);
    return res;
}