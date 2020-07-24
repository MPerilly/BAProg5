#include <iostream>
#include <vector>
#include <string>
#include <utility>
using namespace std;

size_t num_nodes;
size_t num_edges;
vector<size_t> colors;
vector<vector<size_t>> adj_list;
vector<size_t> indegree;
size_t r0 = SIZE_MAX;

vector<size_t> split(const string &str);
void topsort(const size_t &y);

int main() {
    // Parsing input:
    string raw_inp;
    getline(cin, raw_inp);
    vector<size_t> split_inp = split(raw_inp);

    num_nodes = split_inp[0];
    num_edges = split_inp[1];

    // Initialize adjacency list:
    colors = vector<size_t>(num_nodes, 0);
    indegree = vector<size_t>(num_nodes, 0);
    adj_list = vector<vector<size_t>>(num_nodes);

    // Form Adj List from verts:
    for (size_t i = 0; i < num_edges; ++i) {
        getline(cin, raw_inp);
        split_inp = split(raw_inp);
        if (indegree[split_inp[0] - 1] == 0) r0 = split_inp[0] - 1;
        adj_list[split_inp[0] - 1].push_back(split_inp[1] - 1);
        ++indegree[split_inp[1] - 1];
    }
    topsort(r0);
    return 0;
}
vector<size_t> split(const string &str) {
    size_t space = str.find(" ");
    if (space == string::npos) return vector<size_t>();
    string s1 = str.substr(0, space);
    string s2 = str.substr(space, str.length() - 1);
    vector<size_t> split_ints(2);
    split_ints[0] = stoull(s1);
    split_ints[1] = stoull(s2);
    return split_ints;
}


void topsort(const size_t &y) {
    colors[y] = 1;
    size_t r = y;
    for (size_t i = 0; i < num_nodes; ++i){
        cout << r + 1 << ' ';
        for (size_t j = 0; j < adj_list[r].size(); ++j){
            if (indegree[adj_list[r][j]] > 0){
                --indegree[adj_list[r][j]];
            }
            else r = adj_list[r][j];
            if (r == y) cout << 'nope';
        }
    }
    colors[y] = 2;
}