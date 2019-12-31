#include <iostream>
#include <vector>
#include <stack>

#define MAX_SIZE 200001

using namespace std;

struct vertex {
    bool visited;
    vector<int> incoming;
    vector<int> outgoing;

    vertex() {
        this->visited = false;
    }
};

int main() {
    int vertex_number;
    int edge_number;
    int i;
    int j;
    int k = 0;
    int sequence[MAX_SIZE];
    stack<int> s;
    vertex* vertices[MAX_SIZE]{nullptr};
    scanf(" %d %d", &vertex_number, &edge_number);

    i = 0;
    while (i++ < vertex_number) {
        vertices[i] = new vertex();
    }

    while (edge_number-- > 0) {
        scanf(" %d %d", &i, &j);
        if (i == j) {
            continue;
        }
        vertices[i]->outgoing.push_back(j);
        vertices[j]->incoming.push_back(i);
    }

    if (vertex_number == 1) {
        printf("Bravo\n");
        return 0;
    }

    s.push(1);
    vertices[1]->visited = true;
    while (!s.empty()) {
        i = s.top();
        if (vertices[i]->incoming.empty()) {
            ++k;
            sequence[vertex_number - k] = i;
            s.pop();
            continue;
        }
        while (!vertices[i]->incoming.empty()) {
            j = vertices[i]->incoming.back();
            vertices[i]->incoming.pop_back();
            if (!vertices[j]->visited) {
                s.push(j);
                vertices[j]->visited = true;
                break;
            }
        }
    }

    if (k != vertex_number) {
        printf("ovarB\n");
        return 0;
    }

    i = 0;
    while (i++ < vertex_number) {
        vertices[i]->visited = false;
    }

    s.push(sequence[0]);
    vertices[sequence[0]]->visited = true;
    while (!s.empty()) {
        i = s.top();
        if (vertices[i]->outgoing.empty()) {
            s.pop();
            --k;
            continue;
        }
        while (!vertices[i]->outgoing.empty()) {
            j = vertices[i]->outgoing.back();
            vertices[i]->outgoing.pop_back();
            if (!vertices[j]->visited) {
                s.push(j);
                vertices[j]->visited = true;
                break;
            }
        }
    }

    if (k) {
        printf("ovarB\n");
    }
    else {
        printf("Bravo\n");
    }
    return 0;
}