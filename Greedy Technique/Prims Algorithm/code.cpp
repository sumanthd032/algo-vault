#include <iostream>
#include <climits>
using namespace std;

#define MAX 100
#define INF 9999

void primAlgorithm(int n, int cost[MAX][MAX]) {
    int near[MAX];
    int t[MAX][2];     // To store MST edges
    int mincost = 0;
    int mark[MAX] = {0};

    // Step 1: Find the minimum edge
    int min = INF, u = -1, v = -1;
    for (int i = 1; i <= n; i++) {
        for (int j = i + 1; j <= n; j++) {
            if (cost[i][j] < min) {
                min = cost[i][j];
                u = i;
                v = j;
            }
        }
    }

    t[0][0] = u;
    t[0][1] = v;
    mincost += cost[u][v];

    // Initialize near array
    for (int i = 1; i <= n; i++) {
        if (cost[i][u] < cost[i][v])
            near[i] = u;
        else
            near[i] = v;
    }

    near[u] = near[v] = 0;

    // Repeat for remaining n-2 edges
    for (int i = 1; i < n - 1; i++) {
        int min = INF;
        int k = -1;

        for (int j = 1; j <= n; j++) {
            if (near[j] != 0 && cost[j][near[j]] < min) {
                min = cost[j][near[j]];
                k = j;
            }
        }

        t[i][0] = k;
        t[i][1] = near[k];
        mincost += cost[k][near[k]];
        near[k] = 0;

        for (int j = 1; j <= n; j++) {
            if (near[j] != 0 && cost[j][near[j]] > cost[j][k]) {
                near[j] = k;
            }
        }
    }

    // Output MST
    cout << "Edges in the MST:\n";
    for (int i = 0; i < n - 1; i++) {
        cout << t[i][0] << " - " << t[i][1] << "\n";
    }
    cout << "Minimum cost = " << mincost << "\n";
}

int main() {
    int n;

    cout << "Enter number of vertices: ";
    cin >> n;

    int cost[MAX][MAX];
    cout << "Enter cost matrix (use 9999 for no direct edge):\n";

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            cin >> cost[i][j];
        }
    }

    primAlgorithm(n, cost);
    return 0;
}
