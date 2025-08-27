#include <iostream>
#include <fstream>
using namespace std;

const int NMAX = 101;
int mat[NMAX][NMAX];  // Matricea de adiacență
int vizitat[NMAX];     // Vector de vizitare

void dfs(int varf, int n) {
    cout << varf << " ";
    vizitat[varf] = 1;

    for (int i = 1; i <= n; i++) {
        if (mat[varf][i] == 1 && vizitat[i] == 0) {
            dfs(i, n);  // Apel recursiv pentru nodurile neexplorate
        }
    }
}

int main() {
    ifstream fin("C:/Users/urdad/lab2_5grafuri/citire.txt");
    if (!fin) {
        cerr << "Eroare: Nu s-a putut deschide fisierul graf.in!\n";
        return 1;
    }

    int n, m, x, y;
    fin >> n >> m; // Citire număr de noduri și muchii

    // Citirea muchiilor
    for (int i = 1; i <= m; i++) {
        fin >> x >> y;
        mat[x][y] = 1; // Graf orientat
        // mat[y][x] = 1;  // Dacă graful e neorientat, decomentează această linie
    }

    fin.close(); // Închidem fișierul după citire

    // Parcurgerea DFS pentru fiecare componentă conexă
    cout << "Padurea descoperita de DFS:\n";
    for (int i = 1; i <= n; i++) {
        if (!vizitat[i]) {  // Dacă nodul nu a fost vizitat, începe DFS de la el
            dfs(i, n);
            cout << '\n';
        }
    }

    return 0;
}