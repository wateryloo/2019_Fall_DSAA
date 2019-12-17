#include <iostream>
#include <stack>

/*
 * 1 5 6 1 2 2 3 3 4 4 1 4 5 5 3
 * */

#define WHITE 0
#define GREY 1
#define BLACK 2

using std::stack;

struct vertex {
    int color;
    int val;
    int in_time;
    int out_time;
    int pi;

    explicit vertex(int val) {
        this->color = WHITE;
        this->val = val;
        this->in_time = 0;
        this->out_time = 0;
        this->pi = 0;
    }
};

int vertex_number;
int edge_number;
int global_time;
vertex* vertices[501];
int adjacency_matrix[501][501];
int edges[100000][2];

void dfs();
void dfs_visit(vertex* v);
inline bool is_backward_edge(int i);

int main() {
    int testcase_number;

    int i;
    int j;
    bool is_dag;
    stack<int> s_from;
    stack<int> s_to;
    scanf(" %d", &testcase_number);
    while (testcase_number-- > 0) {
        global_time = 0;
        is_dag = true;
        scanf(" %d %d", &vertex_number, &edge_number);
        i = 1;
        while (i <= vertex_number) {
            vertices[i] = new vertex(i);
            j = 1;
            while (j <= vertex_number) {
                adjacency_matrix[i][j] = 0;
                ++j;
            }
            ++i;
        }

        i = 0;
        while (i < edge_number) {
            scanf(" %d %d", &edges[i][0], &edges[i][1]);
            ++adjacency_matrix[edges[i][0]][edges[i][1]];
            ++i;
        }

        dfs();

        i = 0;
        while (i < edge_number) {
            is_dag = !is_backward_edge(i);
            if (!is_dag) {
                break;
            }
            ++i;
        }

        if (is_dag) {
            printf("Yes\n");
            continue;
        }

        j = edges[i][0];
        while (j != edges[i][1]) {
            s_from.push(vertices[j]->pi);
            s_to.push(j);
            j = vertices[j]->pi;
        }
        s_from.push(edges[i][0]);
        s_to.push(edges[i][1]);

        while (!s_from.empty()) {
            --adjacency_matrix[s_from.top()][s_to.top()];
            dfs();
            i = 0;
            while (i < edge_number) {
                if (adjacency_matrix[edges[i][0]][edges[i][1]]) {
                    is_dag = !is_backward_edge(i);
                    if (!is_dag) {
                        break;
                    }
                }
                ++i;
            }
            if (is_dag) {
                printf("Yes\n");
                while (!s_from.empty()) {
                    s_from.pop();
                    s_to.pop();
                }
            }
            else {
                ++adjacency_matrix[s_from.top()][s_to.top()];
                s_from.pop();
                s_to.pop();
            }
        }
        if (!is_dag) {
            printf("No\n");
        }

        while (!s_from.empty()) {
            s_from.pop();
        }
        while (!s_to.empty()) {
            s_to.pop();
        }
        i = 1;
        while (i <= vertex_number) {
            delete vertices[i];
            ++i;
        }
        i = 0;
        while (i < edge_number) {
            edges[i][0] = 0;
            edges[i][1] = 0;
            ++i;
        }
    }
    return 0;
}

void dfs() {
    vertex* v;
    int i = 1;
    while (i <= vertex_number) {
        v = vertices[i];
        v->color = WHITE;
        v->pi = 0;
        ++i;
    }
    global_time = 0;
    i = 1;
    while (i <= vertex_number) {
        v = vertices[i];
        if (v->color == WHITE) {
            dfs_visit(v);
        }
        ++i;
    }
}

void dfs_visit(vertex* v) {
    ++global_time;
    v->in_time = global_time;
    v->color = GREY;
    int i = 1;
    while (i <= vertex_number) {
        if (adjacency_matrix[v->val][i] && vertices[i]->color == WHITE) {
            vertices[i]->pi = v->val;
            dfs_visit(vertices[i]);
        }
        ++i;
    }
    v->color = BLACK;
    ++global_time;
    v->out_time = global_time;
}

inline bool is_backward_edge(int i) {
    return (vertices[edges[i][0]]->in_time >= vertices[edges[i][1]]->in_time) &&
            (vertices[edges[i][0]]->out_time <= vertices[edges[i][1]]->out_time);
}