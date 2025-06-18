#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#define NO_OF_CHARS 256
using namespace std;

// Preprocess bad character heuristic table
void badCharHeuristic(const string& str, int size, int badchar[NO_OF_CHARS]) {
    for (int i = 0; i < NO_OF_CHARS; i++)
        badchar[i] = -1;
    for (int i = 0; i < size; i++)
        badchar[(int)str[i]] = i;
}

// Boyer-Moore search function
void boyerMooreSearch(const string& txt, const string& pat) {
    int m = pat.size();
    int n = txt.size();

    int badchar[NO_OF_CHARS];
    badCharHeuristic(pat, m, badchar);

    int s = 0;  // shift of the pattern with respect to text
    while (s <= (n - m)) {
        int j = m - 1;

        // Keep reducing index j of pattern while characters of pattern and text are matching at this shift s
        while (j >= 0 && pat[j] == txt[s + j])
            j--;

        // If the pattern is present at current shift, print the position
        if (j < 0) {
            cout << "Pattern found at index " << s << endl;
            s += (s + m < n) ? m - badchar[txt[s + m]] : 1;
        }
        else {
            s += max(1, j - badchar[txt[s + j]]);
        }
    }
}

int main() {
    string text, pattern;
    cout << "Enter text: ";
    getline(cin, text);
    cout << "Enter pattern: ";
    getline(cin, pattern);

    boyerMooreSearch(text, pattern);

    return 0;
}
