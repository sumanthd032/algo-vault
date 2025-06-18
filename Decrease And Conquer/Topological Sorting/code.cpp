#include <iostream>
#include <vector>
#include <stack>
using namespace std;

void dfs(int node, const vector<vector<int>>& adj, vector<bool>& visited, stack<int>& st) {
    visited[node] = true;
    for (int neighbor : adj[node]) {
        if (!visited[neighbor]) {
            dfs(neighbor, adj, visited, st);
        }
    }
    st.push(node);
}

void topologicalSort(int vertices, const vector<vector<int>>& adj) {
    vector<bool> visited(vertices, false);
    stack<int> st;

    for (int i = 0; i < vertices; i++) {
        if (!visited[i]) {
            dfs(i, adj, visited, st);
        }
    }

    cout << "Topological Sort Order: ";
    while (!st.empty()) {
        cout << st.top() << " ";
        st.pop();
    }
    cout << endl;
}

int main() {
    int vertices, edges;
    cout << "Enter number of vertices and edges: ";
    cin >> vertices >> edges;

    vector<vector<int>> adj(vertices);
    cout << "Enter directed edges (u v) format (0-indexed):\n";
    for (int i = 0; i < edges; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
    }

    topologicalSort(vertices, adj);

    return 0;
}
