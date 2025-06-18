#include <iostream>
#include <vector>
using namespace std;

void dfs(int node, const vector<vector<int>>& adj, vector<bool>& visited) {
    visited[node] = true;
    cout << node << " ";

    for (int neighbor : adj[node]) {
        if (!visited[neighbor]) {
            dfs(neighbor, adj, visited);
        }
    }
}

int main() {
    int vertices, edges;
    cout << "Enter number of vertices and edges: ";
    cin >> vertices >> edges;

    vector<vector<int>> adj(vertices);
    cout << "Enter edges (u v) format (0-indexed):\n";
    for (int i = 0; i < edges; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u); // Comment this line for directed graph
    }

    vector<bool> visited(vertices, false);
    int start;
    cout << "Enter starting node: ";
    cin >> start;

    cout << "DFS traversal starting from node " << start << ": ";
    dfs(start, adj, visited);
    cout << endl;

    return 0;
}
