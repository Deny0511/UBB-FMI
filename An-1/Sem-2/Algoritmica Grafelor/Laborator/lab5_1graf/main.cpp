// Algoritmul Edmonds-Karp
#include <limits.h>
#include <string.h>
#include <fstream>
#include <iostream>
#include <queue>
using namespace std;

// BFS
bool bfs(vector<vector<int>>& rgraf, int sursa, int destinatie, vector<int>& parinte, int V) {

    vector<bool> vizitat(V, 0);

    queue<int> queue;
    queue.push(sursa);
    vizitat[sursa] = true;
    parinte[sursa] = -1;

    while (!queue.empty()) {
        int u = queue.front();
        queue.pop();

        for (int v = 0; v < V; v++) {
            if (vizitat[v] == false && rgraf[u][v] > 0) {
                queue.push(v);
                parinte[v] = u;
                vizitat[v] = true;
            }
        }
    }

    return (vizitat[destinatie] == true);
}

// Algoritmul Edmonds-Karp
int edmondsKarp(vector<vector<int>>& graf, int sursa, int destinatie, int V) {
    int u, v;

    vector<vector<int>> rgraf(V);

    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            rgraf[i].push_back(0);
        }
    }

    for (u = 0; u < V; u++)
        for (v = 0; v < V; v++)
            rgraf[u][v] = graf[u][v];

    vector<int> parinte(V);

    int flux_maxim = 0;

    // updatam valorile reziduale
    while (bfs(rgraf, sursa, destinatie, parinte, V)) {
        int flux = INT_MAX;
        for (v = destinatie; v != sursa; v = parinte[v]) {
            u = parinte[v];
            flux = min(flux, rgraf[u][v]);
        }

        for (v = destinatie; v != sursa; v = parinte[v]) {
            u = parinte[v];
            rgraf[u][v] -= flux;
            rgraf[v][u] += flux;
        }

        // adaugam
        flux_maxim += flux;

    }

    return flux_maxim;
}
ifstream fin("../input.txt");
int main() {
    int V, E, x, y, c;
    fin >> V;
    cout << "Numarul de varfuri este: ";
    cout << V << endl;
    fin >> E;
    cout << "Numarul de arce este: ";
    cout << E << endl;

    vector<vector<int>> graf(V);
    // populam graful
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            graf[i].push_back(0);
        }
    }

    cout << "Datele de intrare (nod sursa, nod destinatie, capacitate) sunt: " << endl;
    for (int i = 0; i < E; i++) {
        fin >> x >> y >> c;
        graf[x][y] = c;
        cout << x << " " << y << " " << c << endl;
    }

    cout << "Fluxul maxim este: " << edmondsKarp(graf, 0, V - 1, V) << endl;
}