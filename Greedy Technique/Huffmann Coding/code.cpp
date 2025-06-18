#include <iostream>
#include <queue>
#include <vector>
#include <unordered_map>
using namespace std;

struct Node {
    char ch;
    int freq;
    Node *left, *right;

    Node(char c, int f) {
        ch = c;
        freq = f;
        left = right = nullptr;
    }
};

// Custom comparator for min-heap
struct Compare {
    bool operator()(Node* a, Node* b) {
        return a->freq > b->freq;
    }
};

// Recursive function to generate Huffman codes
void generateCodes(Node* root, string code, unordered_map<char, string>& huffmanCode) {
    if (!root) return;

    if (!root->left && !root->right) {
        huffmanCode[root->ch] = code;
    }

    generateCodes(root->left, code + "0", huffmanCode);
    generateCodes(root->right, code + "1", huffmanCode);
}

void huffmanCoding(vector<char> characters, vector<int> frequencies) {
    priority_queue<Node*, vector<Node*>, Compare> pq;

    for (int i = 0; i < characters.size(); i++) {
        pq.push(new Node(characters[i], frequencies[i]));
    }

    while (pq.size() > 1) {
        Node* left = pq.top(); pq.pop();
        Node* right = pq.top(); pq.pop();

        Node* parent = new Node('\0', left->freq + right->freq);
        parent->left = left;
        parent->right = right;

        pq.push(parent);
    }

    Node* root = pq.top();
    unordered_map<char, string> huffmanCode;
    generateCodes(root, "", huffmanCode);

    cout << "Huffman Codes:\n";
    for (auto pair : huffmanCode) {
        cout << pair.first << ": " << pair.second << "\n";
    }
}

int main() {
    int n;
    cout << "Enter number of characters: ";
    cin >> n;

    vector<char> characters(n);
    vector<int> frequencies(n);

    cout << "Enter characters:\n";
    for (int i = 0; i < n; i++) {
        cin >> characters[i];
    }

    cout << "Enter corresponding frequencies:\n";
    for (int i = 0; i < n; i++) {
        cin >> frequencies[i];
    }

    huffmanCoding(characters, frequencies);
    return 0;
}
