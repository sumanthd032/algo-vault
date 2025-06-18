#include <iostream>
#include <vector>
using namespace std;

void sumOfSubsets(vector<int>& set, vector<int>& subset, int index, int currentSum, int targetSum) {
    if (currentSum == targetSum) {
        cout << "{ ";
        for (int num : subset)
            cout << num << " ";
        cout << "}" << endl;
        return;
    }

    for (int i = index; i < set.size(); i++) {
        if (currentSum + set[i] <= targetSum) {
            subset.push_back(set[i]);
            sumOfSubsets(set, subset, i + 1, currentSum + set[i], targetSum);
            subset.pop_back();  // backtrack
        }
    }
}

int main() {
    int n, target;
    cout << "Enter number of elements in the set: ";
    cin >> n;

    vector<int> set(n);
    cout << "Enter the elements of the set:\n";
    for (int i = 0; i < n; i++)
        cin >> set[i];

    cout << "Enter the target sum: ";
    cin >> target;

    vector<int> subset;
    cout << "Subsets with sum " << target << ":\n";
    sumOfSubsets(set, subset, 0, 0, target);

    return 0;
}
