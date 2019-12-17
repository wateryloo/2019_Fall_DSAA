#include <iostream>
#include <vector>
 
#define max_number_of_vertex 2000
 
using namespace std;
 
struct vertex {
    int val;
    bool visited;
    vector<int> outgoing;
 
    vertex(int val) {
        this->val = val;
        visited = false;
    }
};
 
int helper(vertex* (&table)[max_number_of_vertex], vertex* &start);
 
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int testcase_number;
    int vertex_number;
    int i;
    int j;
    int vertices[max_number_of_vertex][3];
    vertex* table[max_number_of_vertex];
    bool has_incoming[max_number_of_vertex];
    cin >> testcase_number;
    while (testcase_number > 0) {
        --testcase_number;
        i = 0;
        cin >> vertex_number;
        while (i < vertex_number) {
            has_incoming[i] = false;
            cin >> vertices[i][0] >> vertices[i][1] >> vertices[i][2];
            table[i] = new vertex(vertices[i][2]);
            ++i;
        }
        i = 0;
 
        while (i < vertex_number) { // Build the map.
            j = 0;
            while (j < vertex_number) {
                if ((vertices[i][0] > vertices[j][0] && vertices[i][1] > vertices[j][1]) ||
                    (vertices[i][0] > vertices[j][1] && vertices[i][1] > vertices[j][0])) {
                    table[i]->outgoing.push_back(j);
                    has_incoming[j] = true;
                }
                ++j;
            }
            ++i;
        }
 
        i = 0;
        j = 0;
        while (i < vertex_number) {
            if (!has_incoming[i]) {
                j = j > helper(table, table[i]) ? j : helper(table, table[i]);
            }
            ++i;
        }
        cout << j << endl;
    }
    return 0;
}
 
int helper(vertex* (&table)[max_number_of_vertex], vertex* &start) {
    if (start->visited || start->outgoing.empty()) {
        return start->val;
    }
    int max = 0;
    int temp = 0;
    for (int iter : start->outgoing) {
        temp = helper(table, table[iter]);
        max = max > temp ? max : temp;
    }
    start->visited = true;
    start->val += max;
    return start->val;
}