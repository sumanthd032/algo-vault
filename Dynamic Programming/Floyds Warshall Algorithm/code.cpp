#include <iostream>
#include <vector>
using namespace std;

const int INF = 1e9;  // A large value to represent infinity

void floydWarshall(vector<vector<int>>& dist, int n) {
    for (int k = 0; k < n; k++) {           // Intermediate vertex
        for (int i = 0; i < n; i++) {       // Source vertex
            for (int j = 0; j < n; j++) {   // Destination vertex
                if (dist[i][k] != INF && dist[k][j] != INF &&
                    dist[i][k] + dist[k][j] < dist[i][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                }
            }
        }
    }
}

int main() {
    int n;
    cout << "Enter number of vertices: ";
    cin >> n;

    vector<vector<int>> dist(n, vector<int>(n));
    cout << "Enter adjacency matrix (use " << INF << " for no direct edge):\n";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> dist[i][j];
            if (i != j && dist[i][j] == 0) {
                dist[i][j] = INF;  // No edge
            }
        }
    }

    floydWarshall(dist, n);

    cout << "\nShortest distances between every pair of vertices:\n";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (dist[i][j] == INF)
                cout << "INF ";
            else
                cout << dist[i][j] << " ";
        }
        cout << "\n";
    }

    return 0;
}
