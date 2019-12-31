#include <iostream>
#include <vector>
#include <stack>
#include <climits>

using namespace std;

typedef long long lld;

struct vertex {
    bool visited;
    lld x;
    lld y;
    lld radius{};
    lld cost{};
    lld scc_id;
    vector<lld> outgoing;
    vector<lld> incoming;
    vector<lld> outgoing_1;

    vertex(lld x, lld y) {
        this->visited = false;
        this->x = x;
        this->y = y;
        this->scc_id = -1;
    }
};

bool check(vertex* (&vertices)[1000], lld i, lld j);

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    lld vertex_number;
    lld i;
    lld j;
    lld k;
    lld l;
    lld m = 0;
    lld sequence[1000];
    lld scc_id = 0;
    lld scc_cost[1000];
    vertex* vertices[1000]{nullptr};
    stack<lld> s;

    cin >> vertex_number;

    i = 0;
    while (i < vertex_number) {
        cin >> j >> k;
        vertices[i] = new vertex(j, k);
        cin >> vertices[i]->radius;
        cin >> vertices[i]->cost;
        ++i;
    }

    i = 0;
    while (i < vertex_number) {
        j = 0;
        while (j < vertex_number) {
            if (i == j) {
                ++j;
                continue;
            }
            if (check(vertices, i, j)) {
                vertices[i]->outgoing.push_back(j);
                vertices[i]->outgoing_1.push_back(j);
                vertices[j]->incoming.push_back(i);
            }
            ++j;
        }
        ++i;
    }

    i = 0;
    k = 0;
    while (i < vertex_number) {
        if (vertices[i]->visited) {
            ++i;
            continue;
        }
        s.push(i);
        vertices[i]->visited = true;
        while (!s.empty()) {
            j = s.top();
            if (vertices[j]->incoming.empty()) {
                ++k;
                sequence[vertex_number - k] = j;
                s.pop();
                continue;
            }
            while (!vertices[j]->incoming.empty()) {
                l = vertices[j]->incoming.back();
                vertices[j]->incoming.pop_back();
                if (!vertices[l]->visited) {
                    s.push(l);
                    vertices[l]->visited = true;
                    break;
                }
            }
        }
        ++i;
    }

    i = 0;
    while (i < vertex_number) {
        vertices[i]->visited = false;
        ++i;
    }

    i = 0;
    while (i < vertex_number) {
        if (vertices[sequence[i]]->visited) {
            ++i;
            continue;
        }
        l = LONG_LONG_MAX;
        s.push(sequence[i]);
        vertices[sequence[i]]->visited = true;
        while (!s.empty()) {
            j = s.top();
            if (vertices[j]->outgoing.empty()) {
                l = l <= vertices[j]->cost ? l : vertices[j]->cost;
                vertices[j]->scc_id = scc_id;
                s.pop();
                continue;
            }
            while (!vertices[j]->outgoing.empty()) {
                k = vertices[j]->outgoing.back();
                vertices[j]->outgoing.pop_back();
                if (!vertices[k]->visited) {
                    s.push(k);
                    vertices[k]->visited = true;
                    break;
                }
            }
        }
        scc_cost[scc_id] = l;
        ++scc_id;
        ++i;
    }

    i = 0;
    while (i < vertex_number) {
        for (auto iter : vertices[i]->outgoing_1) {
            if (i == iter) {
                continue;
            }
            if (vertices[i]->scc_id == vertices[iter]->scc_id) {
                continue;
            }
            scc_cost[vertices[iter]->scc_id] = 0;
        }
        ++i;
    }

    i = 0;
    while (i < scc_id) {
        m += scc_cost[i];
        ++i;
    }

    cout << m << endl;

    return 0;
}

bool check(vertex* (&vertices)[1000], lld i, lld j) {
    return vertices[i]->radius * vertices[i]->radius >=
           (vertices[i]->x - vertices[j]->x) *
           (vertices[i]->x - vertices[j]->x) +
           (vertices[i]->y - vertices[j]->y) *
           (vertices[i]->y - vertices[j]->y);
}