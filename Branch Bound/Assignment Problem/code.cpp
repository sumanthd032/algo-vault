#include <iostream>
#include <vector>
#include <queue>
#include <climits>
using namespace std;

const int INF = INT_MAX;

struct Node {
    vector<vector<int>> reducedMatrix;
    vector<bool> assigned;
    int cost;
    int workerID;
    int taskID;
    int level;
};

struct compare {
    bool operator()(const Node& a, const Node& b) {
        return a.cost > b.cost;
    }
};

int reduceMatrix(vector<vector<int>>& matrix, int n) {
    int reduction = 0;

    // Row reduction
    for (int i = 0; i < n; i++) {
        int rowMin = INF;
        for (int j = 0; j < n; j++)
            rowMin = min(rowMin, matrix[i][j]);

        if (rowMin != INF && rowMin != 0) {
            reduction += rowMin;
            for (int j = 0; j < n; j++)
                if (matrix[i][j] != INF)
                    matrix[i][j] -= rowMin;
        }
    }

    // Column reduction
    for (int j = 0; j < n; j++) {
        int colMin = INF;
        for (int i = 0; i < n; i++)
            colMin = min(colMin, matrix[i][j]);

        if (colMin != INF && colMin != 0) {
            reduction += colMin;
            for (int i = 0; i < n; i++)
                if (matrix[i][j] != INF)
                    matrix[i][j] -= colMin;
        }
    }

    return reduction;
}

Node* createNode(vector<vector<int>> parentMatrix, vector<bool> assigned, int level, int i, int j, int n) {
    Node* node = new Node;
    node->reducedMatrix = parentMatrix;
    node->assigned = assigned;
    node->workerID = i;
    node->taskID = j;
    node->level = level;

    // Set assigned tasks/rows and columns to INF
    for (int x = 0; x < n; x++) {
        node->reducedMatrix[i][x] = INF;
        node->reducedMatrix[x][j] = INF;
    }

    node->reducedMatrix[j][i] = INF; // prevent cycle
    node->assigned[j] = true;

    return node;
}

int solveBranchAndBound(vector<vector<int>>& costMatrix, int n) {
    priority_queue<Node*, vector<Node*>, compare> pq;

    vector<bool> assigned(n, false);
    Node* root = new Node;
    root->reducedMatrix = costMatrix;
    root->assigned = assigned;
    root->level = 0;
    root->workerID = -1;
    root->taskID = -1;

    root->cost = reduceMatrix(root->reducedMatrix, n);
    pq.push(root);

    while (!pq.empty()) {
        Node* minNode = pq.top(); pq.pop();
        int i = minNode->level;

        if (i == n) {
            return minNode->cost;
        }

        for (int j = 0; j < n; j++) {
            if (!minNode->assigned[j]) {
                Node* child = createNode(minNode->reducedMatrix, minNode->assigned, i + 1, i, j, n);
                child->cost = minNode->cost + costMatrix[i][j] + reduceMatrix(child->reducedMatrix, n);
                pq.push(child);
            }
        }
    }

    return -1;
}

int main() {
    int n;
    cout << "Enter number of tasks/workers: ";
    cin >> n;

    vector<vector<int>> costMatrix(n, vector<int>(n));
    cout << "Enter the cost matrix:\n";
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            cin >> costMatrix[i][j];

    int minCost = solveBranchAndBound(costMatrix, n);
    cout << "Minimum assignment cost: " << minCost << endl;

    return 0;
}
