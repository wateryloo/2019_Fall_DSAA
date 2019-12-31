#include <iostream>
#include <vector>
#include <climits>
#define index(i, j) (i) * vertex_num + (j) + 1

using namespace std;

typedef long long lld;

lld vertex_num;

struct vertex {
    lld index;
    lld activate_num;
    lld distance;
    bool popped;
    vector<lld>* outgoing;
    vector<lld>* weight;
    vector<lld>* portal;

    vertex(lld& i, lld& j) {
        this->index = index(i, j);
        this->activate_num = i;
        this->distance =LONG_LONG_MAX;
        this->popped = false;
    }
};

inline lld parent(lld i);
inline lld left(lld i);
inline lld right(lld i);
void swap(vertex*& a, vertex*& b);
vertex* pop(lld size, vertex* heap[550001]);
void min_heapify(lld size, vertex* heap[550001], lld index);
void decrease_key(lld size, vertex* heap[550001], lld index, lld val);



int main() {
    lld edge_num;
    lld port_num;
    lld activate_num;
    lld i;
    lld j;
    lld k;
    lld l;
    lld m;
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> vertex_num >> edge_num >> port_num >> activate_num;
    vertex* vertices[550001]{nullptr};
    vertex* heap[550001]{nullptr};
    vertex* temp;
    vector<lld> edges[50001];
    vector<lld> weight[50001];
    vector<lld> portal[50001];

    i = 0;
    while (i <= activate_num) {
        j = 0;
        while (j < vertex_num) {
            vertices[index(i, j)] = new vertex(i, j);
            heap[index(i, j)] = vertices[index(i, j)];
            vertices[index(i, j)]->outgoing = &edges[j + 1];
            vertices[index(i, j)]->weight = &weight[j + 1];
            vertices[index(i, j)]->portal = &portal[j + 1];
            ++j;
        }
        ++i;
    }

    i = 0;
    while (i < edge_num) {
        cin >> j >> k >> l;
        edges[j].push_back(k);
        weight[j].push_back(l);
        ++i;
    }

    i = 0;
    while (i < port_num) {
        cin >> j >> k;
        portal[j].push_back(k);
        ++i;
    }

    cin >> i >> j;

    m = vertex_num * (activate_num + 1);
    decrease_key(m, heap, index(0, i - 1), 0);
    while (m > 0) {
        temp = pop(m, heap);
        temp->popped = true;
        --m;

        k = 0;
        while (k < temp->outgoing->size()) {
            l = (*temp->outgoing)[k];
            if (vertices[index(temp->activate_num, l - 1)]->popped) {
                ++k;
                continue;
            }
            if (vertices[index(temp->activate_num, l - 1)]->distance
            > temp->distance + (*temp->weight)[k]) {
                decrease_key(m, heap, vertices[index(temp->activate_num, l - 1)]->index,
                        temp->distance + (*temp->weight)[k]);
                ++k;
                continue;
            }
            ++k;
        }

        k = 0;
        if (temp->activate_num < activate_num) {
            while (k < temp->portal->size()) {
                l = (*temp->portal)[k];
                if (vertices[index(temp->activate_num + 1, l - 1)]->popped) {
                    ++k;
                    continue;
                }
                if (vertices[index(temp->activate_num + 1, l - 1)]->distance > 
                temp->distance) {
                    decrease_key(m, heap,
                            vertices[index(temp->activate_num + 1, l - 1)]->index, 
                            temp->distance);
                    ++k;
                    continue;
                }
                ++k;
            }
        }
    }

    i = 0;
    k = LONG_LONG_MAX;
    while (i <= activate_num) {
        k = k <= vertices[index(i, j - 1)]->distance ? k :
                vertices[index(i, j - 1)]->distance;
        ++i;
    }

    cout << k << endl;
    return 0;
}

inline lld parent(lld i) {
    if (i > 1) {
        return i  / 2;
    }
    return 0;
}

inline lld left(lld i) {
    if (i < 1) {
        return -1;
    }
    return 2 * i;
}

inline lld right(lld i) {
    if (i < 1) {
        return -1;
    }
    return 2 * i + 1;
}

void swap(vertex*& a, vertex*& b) {
    vertex* i = a;
    a = b;
    b = i;
    lld t = a->index;
    a->index = b->index;
    b->index = t;
}

vertex* pop(lld size, vertex* heap[550001]) {
    vertex* res = heap[1];
    heap[1] = heap[size];
    heap[1]->index = 1;
    --size;
    min_heapify(size, heap, 1);
    return res;
}

void min_heapify(lld size, vertex* heap[550001], lld index) {
    lld l = left(index);
    lld r = right(index);
    lld smallest = index;
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

void decrease_key(lld size, vertex* heap[550001], lld index, lld val) {
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