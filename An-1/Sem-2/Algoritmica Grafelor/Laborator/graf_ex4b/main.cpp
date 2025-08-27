#include <iostream>
#include <fstream>
#include <queue>
#include <unordered_map>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

// Structură pentru un nod din arborele Huffman
struct Node {
    char ch;         // caracterul reprezentat (doar pentru frunze)
    int freq;        // frecvența caracterului sau suma frecvențelor în subarbore
    Node* left;      // copilul stâng
    Node* right;     // copilul drept

    // Constructor pentru frunze
    Node(char ch, int freq) : ch(ch), freq(freq), left(nullptr), right(nullptr) {}

    // Constructor pentru noduri interne (fără caracter explicit)
    Node(Node* l, Node* r) : ch(min(l->ch, r->ch)), freq(l->freq + r->freq), left(l), right(r) {}
};

// Comparator pentru coada de priorități Huffman
struct Compare {
    bool operator()(Node* a, Node* b) {
        // Dacă au aceeași frecvență, alegem caracterul cu cod ASCII mai mic
        if (a->freq == b->freq)
            return a->ch > b->ch;
        return a->freq > b->freq; // altfel, alegem cel cu frecvență mai mică
    }
};

// Funcție recursivă pentru construirea codurilor Huffman
void build_codes(Node* node, const string& code, unordered_map<char, string>& huff_codes) {
    if (!node->left && !node->right) {
        // Este frunză ⇒ are caracter asociat ⇒ salvăm codul Huffman
        huff_codes[node->ch] = code;
        return;
    }
    // Parcurgere recursivă în preordine: 0 stânga, 1 dreapta
    if (node->left) build_codes(node->left, code + "0", huff_codes);
    if (node->right) build_codes(node->right, code + "1", huff_codes);
}

// Eliberarea memoriei ocupate de arborele Huffman
void delete_tree(Node* node) {
    if (!node) return;
    delete_tree(node->left);
    delete_tree(node->right);
    delete node;
}

int main() {
    ifstream fin("../input.txt");
    ofstream fout("../output.txt");

    // Citim tot conținutul fișierului de intrare într-un singur string
    string text;
    getline(fin, text, '\0');

    // Calculăm frecvența fiecărui caracter
    unordered_map<char, int> freq;
    for (char ch : text) {
        freq[ch]++;
    }

    // Construim coada de priorități Huffman
    priority_queue<Node*, vector<Node*>, Compare> pq;
    for (auto& [ch, f] : freq) {
        pq.push(new Node(ch, f));  // fiecare caracter devine o frunză
    }

    // Construim arborele Huffman
    while (pq.size() > 1) {
        Node* a = pq.top(); pq.pop();  // primul nod cu prioritate minimă
        Node* b = pq.top(); pq.pop();  // al doilea nod cu prioritate minimă
        pq.push(new Node(a, b));       // combinăm cele două noduri într-un nod intern
    }

    Node* root = pq.top();  // rădăcina arborelui

    // Construim codurile Huffman pentru fiecare caracter
    unordered_map<char, string> huff_codes;
    build_codes(root, "", huff_codes);  // începem cu codul gol ""

    // Codificăm textul original
    string encoded;
    for (char ch : text) {
        encoded += huff_codes[ch];
    }

    // Extragem alfabetul și îl sortăm lexicografic
    vector<char> alphabet;
    for (auto& [ch, _] : freq) {
        alphabet.push_back(ch);
    }
    sort(alphabet.begin(), alphabet.end());

    // Scriem în fișierul de ieșire alfabetul și frecvențele
    fout << alphabet.size() << '\n';   // prima linie: numărul de caractere din alfabet
    for (char ch : alphabet) {
        fout << ch << " " << freq[ch] << '\n';  // caracter și frecvență
    }

    // Scriem codul binar al textului
    fout << encoded << '\n';

    // ---------------- DECODARE ----------------

    // Decodificăm textul binar folosind arborele Huffman
    string decoded;
    Node* curr = root;
    for (char bit : encoded) {
        // Avansăm în arbore în funcție de bitul curent
        curr = (bit == '0') ? curr->left : curr->right;

        // Dacă am ajuns la frunză, adăugăm caracterul în textul decodat
        if (!curr->left && !curr->right) {
            decoded += curr->ch;
            curr = root; // revenim la rădăcină pentru următorul caracter
        }
    }

    // Scriem în fișierul de ieșire textul decodat
    fout << decoded << '\n';

    // Eliberăm memoria alocată pentru arbore
    delete_tree(root);

    return 0;
}
