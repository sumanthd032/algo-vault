#include <iostream>
#include <climits>
using namespace std;

#define MAX 100
#define INF 9999

void dijkstra(int n, int cost[MAX][MAX], int v, int dist[MAX]) {
    int s[MAX] = {0};

    // Initialize distance array
    for (int i = 1; i <= n; i++) {
        dist[i] = cost[v][i];
    }

    s[v] = 1;
    dist[v] = 0;

    for (int num = 2; num <= n - 1; num++) {
        int u = -1;
        int minDist = INF;

        // Find the vertex with the minimum distance
        for (int i = 1; i <= n; i++) {
            if (s[i] == 0 && dist[i] < minDist) {
                minDist = dist[i];
                u = i;
            }
        }

        if (u == -1) break; // No reachable unvisited vertex

        s[u] = 1;

        // Update distances of neighbors
        for (int w = 1; w <= n; w++) {
            if (s[w] == 0 && dist[u] + cost[u][w] < dist[w]) {
                dist[w] = dist[u] + cost[u][w];
            }
        }
    }
}

int main() {
    int n, source;
    int cost[MAX][MAX], dist[MAX];

    cout << "Enter number of vertices: ";
    cin >> n;

    cout << "Enter cost matrix (9999 for no edge):\n";
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            cin >> cost[i][j];
        }
    }

    cout << "Enter source vertex (1 to " << n << "): ";
    cin >> source;

    dijkstra(n, cost, source, dist);

    cout << "Shortest distances from vertex " << source << ":\n";
    for (int i = 1; i <= n; i++) {
        cout << "To vertex " << i << ": " << dist[i] << endl;
    }

    return 0;
}
