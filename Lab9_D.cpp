#include <iostream>
#include <vector>

#define index(i, j) i * col_num + j + 1

using namespace std;

typedef long long lld;

struct vertex {
    lld distance;
    lld val;
    lld index;
    bool in_mst;
    vector<lld> row;
    vector<lld> col;
    vector<lld> weight;

    vertex() {
        this->distance = 0;
        this->in_mst = false;
    }
};

inline lld parent(lld i);
inline lld left(lld i);
inline lld right(lld i);
void swap(vertex*& a, vertex*& b);
vertex* pop(lld size, vertex* heap[50001]);
void min_heapify(lld size, vertex* heap[50001], lld index);
void decrease_key(lld size, vertex* heap[50001], lld index, lld val);

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    lld row_num;
    lld col_num;
    lld i;
    lld j;
    lld k;
    lld l;
    lld res = 0;
    vertex* vertices[50001]{nullptr};
    vertex* heap[50001]{nullptr};
    vertex* temp;
    cin >> row_num >> col_num;

    i = 0;
    while (i < row_num) {
        j = 0;
        while (j < col_num) {
            vertices[index(i, j)] = new vertex();
            cin >> vertices[index(i, j)]->val;
            vertices[index(i, j)]->index = index(i, j);
            heap[index(i, j)] = vertices[index(i, j)];
            ++j;
        }
        ++i;
    }

    i = 0;
    while (i < row_num) {
        j = 0;
        while (j < col_num) {
            if (i > 0) {
                vertices[index(i, j)]->row.push_back(i - 1);
                vertices[index(i, j)]->col.push_back(j);
                vertices[index(i, j)]->weight.push_back(-1LL *
                vertices[index(i, j)]->val * vertices[index((i - 1), j)]->val);
            }
            if (i < row_num - 1) {
                vertices[index(i, j)]->row.push_back(i + 1);
                vertices[index(i, j)]->col.push_back(j);
                vertices[index(i, j)]->weight.push_back(-1LL *
                vertices[index(i, j)]->val * vertices[index((i + 1), j)]->val);
            }
            if (j > 0) {
                vertices[index(i, j)]->row.push_back(i);
                vertices[index(i, j)]->col.push_back(j - 1);
                vertices[index(i, j)]->weight.push_back(-1LL *
                vertices[index(i, j)]->val * vertices[index(i, (j - 1))]->val);
            }
            if (j < col_num - 1) {
                vertices[index(i, j)]->row.push_back(i);
                vertices[index(i, j)]->col.push_back(j + 1);
                vertices[index(i, j)]->weight.push_back(-1LL *
                vertices[index(i, j)]->val * vertices[index(i, (j + 1))]->val);
            }
            ++j;
        }
        ++i;
    }

    i = col_num * row_num;
    while (i > 0) {
        temp = pop(i, heap);
        if (i == col_num * row_num) {
            temp->distance = 0;
        }
        res += (lld)temp->distance;
        --i;
        temp->in_mst = true;
        while (!temp->row.empty()) {
            j = temp->row.back();
            temp->row.pop_back();
            k = temp->col.back();
            temp->col.pop_back();
            l = temp->weight.back();
            temp->weight.pop_back();
            if (vertices[index(j, k)]->in_mst) {
                continue;
            }
            decrease_key(i, heap, vertices[index(j, k)]->index, l);
        }
    }

    cout << -res << endl;

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

vertex* pop(lld size, vertex* heap[50001]) {
    vertex* res = heap[1];
    heap[1] = heap[size];
    heap[1]->index = 1;
    --size;
    min_heapify(size, heap, 1);
    return res;
}

void min_heapify(lld size, vertex* heap[50001], lld index) {
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

void decrease_key(lld size, vertex* heap[50001], lld index, lld val) {
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