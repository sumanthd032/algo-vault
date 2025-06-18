#include <iostream>
using namespace std;

int binomialCoeff(int n, int k) {
    int C[n+1][k+1];

    // Calculate value of Binomial Coefficient in bottom up manner
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= min(i, k); j++) {
            // Base Cases
            if (j == 0 || j == i)
                C[i][j] = 1;
            else
                // Use previously computed values
                C[i][j] = C[i-1][j-1] + C[i-1][j];
        }
    }

    return C[n][k];
}

int main() {
    int n, k;
    cout << "Enter n and k: ";
    cin >> n >> k;

    cout << "Binomial Coefficient C(" << n << ", " << k << ") = " << binomialCoeff(n, k) << endl;
    return 0;
}
