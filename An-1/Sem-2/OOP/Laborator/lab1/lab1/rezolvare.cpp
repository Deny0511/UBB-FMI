#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>

using namespace std;

// Citirea matricei de adiacență dintr-un fișier
void citeste_matricea_din_fisier(const string& nume_fisier, int matrice[100][100], int& n) {
    ifstream fisier(nume_fisier);
    fisier >> n;

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            fisier >> matrice[i][j];
        }
    }
}

// a. Determinarea nodurilor izolate
void noduri_izolate(const int matrice[100][100], int n) {
    cout << "Noduri izolate: ";
    bool existaIzolat = false;
    for (int i = 0; i < n; ++i) {
        bool izolat = true;
        for (int j = 0; j < n; ++j) {
            if (matrice[i][j] == 1) { // Dacă există o conexiune (1) cu alt nod
                izolat = false;
                break;
            }
        }
        if (izolat) {
            cout << i << " "; // Afișăm nodul izolat
            existaIzolat = true;
        }
    }
    if (!existaIzolat) {
        cout << "Nu sunt noduri izolate.";
    }
    cout << endl;
}


// b. Determinarea dacă graful este regulat
bool este_regular(const int matrice[100][100], int n) {
    int grad = -1;

    for (int i = 0; i < n; ++i) {
        int grad_nod = 0;
        for (int j = 0; j < n; ++j) {
            if (matrice[i][j] == 1) {
                grad_nod++;
            }
        }
        if (grad == -1) {
            grad = grad_nod;
        }
        else if (grad_nod != grad) {
            return false;
        }
    }
    return true;
}

// c. Determinarea matricei distanțelor (Floyd-Warshall)
void matricea_distantelor(const int matrice[100][100], int dist[100][100], int n) {
    // Inițializăm matricea distanțelor
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (i == j) {
                dist[i][j] = 0;
            }
            else if (matrice[i][j] == 1) {
                dist[i][j] = 1;
            }
            else {
                dist[i][j] = 999999;  // Nu există drum între noduri
            }
        }
    }

    // Aplicăm algoritmul Floyd-Warshall
    for (int k = 0; k < n; ++k) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (dist[i][j] > dist[i][k] + dist[k][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                }
            }
        }
    }
}

// d. Determinarea dacă graful este conex
void dfs(int nod, bool vizitat[100], const int matrice[100][100], int n) {
    vizitat[nod] = true;
    for (int i = 0; i < n; ++i) {
        if (matrice[nod][i] == 1 && !vizitat[i]) {
            dfs(i, vizitat, matrice, n);
        }
    }
}

bool este_conex(const int matrice[100][100], int n) {
    bool vizitat[100] = { false };

    // Pornim DFS de la primul nod
    dfs(0, vizitat, matrice, n);

    // Verificăm dacă toate nodurile au fost vizitate
    for (int i = 0; i < n; ++i) {
        if (!vizitat[i]) {
            return false;
        }
    }
    return true;
}

int main() {
    int matrice[100][100];
    int dist[100][100];
    int n;

    string nume_fisier = "fisier.txt";  // Specifică fișierul de intrare
    citeste_matricea_din_fisier(nume_fisier, matrice, n);

    // a. Noduri izolate
    noduri_izolate(matrice, n);

    // b. Verificăm dacă graful este regulat
    if (este_regular(matrice, n)) {
        cout << "Graful este regulat.\n";
    }
    else {
        cout << "Graful nu este regulat.\n";
    }

    // c. Matr. distanțelor
    matricea_distantelor(matrice, dist, n);
    cout << "Matricea distantelor:\n";
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (dist[i][j] == 999999) {
                cout << "0 " ;
            }
            else {
                cout << dist[i][j] << " ";
            }
        }
        cout << endl;
    }

    // d. Verificăm dacă graful este conex
    if (este_conex(matrice, n)) {
        cout << "Graful este conex.\n";
    }
    else {
        cout << "Graful nu este conex.\n";
    }

    return 0;
}
