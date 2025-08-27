#include <iostream>
#include <fstream>
#include <queue>
#include <unordered_map>
#include <vector>
#include <algorithm>

using namespace std;

struct Node {
    char ch;
    int freq;
    Node* left;
    Node* right;

    Node(char ch, int freq, Node* left = nullptr, Node* right = nullptr)
        : ch(ch), freq(freq), left(left), right(right) {}
};

// Comparator pentru heap: întâi după frecvență, apoi după minimul ASCII din subarbore
struct Compare {
    bool operator()(const Node* a, const Node* b) const {
        if (a->freq != b->freq)
            return a->freq > b->freq;

        char minA = getMinChar(a);
        char minB = getMinChar(b);
        return minA > minB;
    }

    static char getMinChar(const Node* node) {
        if (!node->left && !node->right) return node->ch;
        char minLeft = node->left ? getMinChar(node->left) : 127;
        char minRight = node->right ? getMinChar(node->right) : 127;
        return min(minLeft, minRight);
    }
};

void generateCodes(Node* root, string code,
                   unordered_map<char, string>& huffmanCode) {
    if (!root->left && !root->right) {
        huffmanCode[root->ch] = code;
        return;
    }
    if (root->left) generateCodes(root->left, code + "0", huffmanCode);
    if (root->right) generateCodes(root->right, code + "1", huffmanCode);
}

int main() {
    ifstream fin("../input.txt");
    ofstream fout("../output.txt");

    string text;
    getline(fin, text);

    unordered_map<char, int> freq;
    for (char c : text) {
        freq[c]++;
    }

    priority_queue<Node*, vector<Node*>, Compare> pq;
    for (auto& [ch, f] : freq) {
        pq.push(new Node(ch, f));
    }

    while (pq.size() > 1) {
        Node* left = pq.top(); pq.pop();
        Node* right = pq.top(); pq.pop();
        pq.push(new Node(0, left->freq + right->freq, left, right));
    }

    Node* root = pq.top();

    unordered_map<char, string> huffmanCode;
    generateCodes(root, "", huffmanCode);

    vector<pair<char, int>> alphabet(freq.begin(), freq.end());
    sort(alphabet.begin(), alphabet.end());

    fout << alphabet.size() << '\n';
    for (auto& [ch, f] : alphabet) {
        fout << ch << ' ' << f << '\n';
    }

    for (char c : text) {
        fout << huffmanCode[c];
    }
    fout << '\n';

    return 0;
}
