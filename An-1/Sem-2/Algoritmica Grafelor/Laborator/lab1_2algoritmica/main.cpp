#include <iostream>
#include <fstream>

using namespace std;

#define INF 999999

int main() {
    int n, m[20][20] = {0}, x, y;
    ifstream fin("C:\\Users\\urdad\\lab1_2algoritmica\\text1.txt");

    fin >> n;

    int v[20] = {0};

    while (fin >> x >> y) {
        m[x][y] = 1;
        m[y][x] = 1;
        v[x]++;
        v[y]++;
    }

    fin.close();

    // a) Noduri izolate
    cout << "Nodurile izolate sunt: ";
    bool existaNodIzolat = false;
    for (int i = 1; i <= n; i++) {
        if (v[i] == 0) {
            cout << i << " ";
            existaNodIzolat = true;
        }
    }
    if (!existaNodIzolat) cout << "Nu sunt noduri izolate.";
    cout << endl;

    // b) graf regular
    bool regular = true;
    int gradInitial = v[1];

    for (int i = 2; i <= n; i++) {
        if (v[i] != gradInitial) {
            regular = false;
            break;
        }
    }

    if (regular)
        cout << "Graful este regular.\n";
    else
        cout << "Graful nu este regular.\n";

    // c) Matricea distantelor (Floyd-Warshall)
    int d[20][20];

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (m[i][j] != 0)
                d[i][j] = m[i][j];
            else if (i == j)
                d[i][j] = 0;
            else
                d[i][j] = INF;
        }
    }

    //  Floyd-Warshall
    for (int k = 1; k <= n; k++) {
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                if (d[i][k] != INF && d[k][j] != INF && d[i][k] + d[k][j] < d[i][j])
                    d[i][j] = d[i][k] + d[k][j];
            }
        }
    }

    cout << "Matricea distantelor:\n";
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (d[i][j] == INF)
                cout << "INF ";
            else
                cout << d[i][j] << " ";
        }
        cout << endl;
    }

    // d) Verificare graf conex
    bool conex = true;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (d[i][j] == INF) {
                conex = false;
                break;
            }
        }
        if (!conex) break;
    }

    if (conex)
        cout << "Graful este conex.\n";
    else
        cout << "Graful nu este conex.\n";

    return 0;
}
