#include <iostream>
#include <vector>
using namespace std;

bool isSafe(vector<vector<int>>& board, int row, int col, int n) {
    // Check column
    for (int i = 0; i < row; i++)
        if (board[i][col])
            return false;

    // Check upper-left diagonal
    for (int i = row - 1, j = col - 1; i >= 0 && j >= 0; i--, j--)
        if (board[i][j])
            return false;

    // Check upper-right diagonal
    for (int i = row - 1, j = col + 1; i >= 0 && j < n; i--, j++)
        if (board[i][j])
            return false;

    return true;
}

bool solveNQueens(vector<vector<int>>& board, int row, int n) {
    if (row == n) {
        // Print one of the solutions
        for (const auto& r : board) {
            for (int cell : r)
                cout << (cell ? "Q " : ". ");
            cout << endl;
        }
        cout << endl;
        return true;  // Change to false to print all solutions
    }

    for (int col = 0; col < n; col++) {
        if (isSafe(board, row, col, n)) {
            board[row][col] = 1;
            if (solveNQueens(board, row + 1, n))
                return true;
            board[row][col] = 0;  // Backtrack
        }
    }

    return false;
}

int main() {
    int n;
    cout << "Enter number of queens: ";
    cin >> n;

    vector<vector<int>> board(n, vector<int>(n, 0));
    if (!solveNQueens(board, 0, n)) {
        cout << "No solution exists for " << n << " queens.\n";
    }

    return 0;
}
