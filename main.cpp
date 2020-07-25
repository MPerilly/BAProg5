#include <iostream>
#include <algorithm>
#include <queue>
#include <vector>
#include <string>
#include <utility>
using namespace std;

size_t num_nodes;
size_t num_edges;
size_t num_visited;
vector<size_t> topsort_buf;
vector<vector<size_t>> adj_list;
vector<int> indegree;
std::priority_queue<size_t , std::vector<size_t>, greater<size_t>> mindex;


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
    indegree = vector<int>(num_nodes, 0);
    adj_list = vector<vector<size_t>>(num_nodes);

    // Form Adj List from verts:
    for (size_t i = 0; i < num_edges; ++i) {
        getline(cin, raw_inp);
        split_inp = split(raw_inp);
        adj_list[split_inp[0] - 1].push_back(split_inp[1] - 1);
        ++indegree[split_inp[1] - 1];
    }
    mindex = std::priority_queue<size_t , std::vector<size_t>, greater<size_t>>();
    topsort_buf = vector<size_t>();
    for (size_t i = 0; i < indegree.size(); ++i){
        if (indegree[i] == 0){
            mindex.push(i);
        }
    }
    while (!mindex.empty()){
        topsort(mindex.top());
        num_visited++;
    }
    if (num_visited != num_nodes) {
        cout << "-1";
        return 0;
    }
    for(size_t i = 0; i < num_nodes; ++i){
        cout << topsort_buf[i] + 1 << ' ';
    }

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
    topsort_buf.push_back(y);
    mindex.pop();
    for (size_t i = 0; i < adj_list[y].size(); ++i){
        if (--indegree[adj_list[y][i]] == 0){
            mindex.push(adj_list[y][i]);
        }
    }
}