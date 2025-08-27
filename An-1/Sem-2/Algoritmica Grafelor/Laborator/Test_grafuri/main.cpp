
#include <iostream>
#include <fstream>

using namespace std;

const int MAX_V = 10;
const int MAX_M = 20;

int inc[MAX_V + 1][MAX_M + 1];
int muchii[MAX_M + 1][2];
int m;

int main() {
    ifstream fin("C:/Users/urdad/Test_grafuri/fisier.txt");

    fin >> m;

    for (int i = 1; i <= m; i++) {
        int x, y;
        fin >> x >> y;
        muchii[i][0] = x;
        muchii[i][1] = y;

        inc[x][i] = 1;
        inc[y][i] = 1;
    }

    cout << "Matricea de incidenta:\n";
    for (int i = 1; i <= MAX_V; i++) {
        for (int j = 1; j <= m; j++) {
            cout << inc[i][j] << " ";
        }
        cout << endl;
    }

    return 0;
}
