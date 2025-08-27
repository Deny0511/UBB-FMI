//nota 5

// Se da un graf conex neorientat G cu N noduri si M muchii, fiecare muchie avand asociat un cost. Se cere sa
// se determine un subgraf care cuprinde toate nodurile si o parte din muchii, astfel incat subgraful
// determinat sa aiba structura de arbore si suma costurilor muchiilor care il formeaza sa fie minim posibila.
// Subgraful cu proprietatile de mai sus se va numi arbore partial de cost minim pentru graful dat. Fisierul de
// intrare apm.in va contine pe prima linie numerele N si M, separate printr-un spatiu. Pe urmatoarele M linii
// se vor gasi muchiile grafului sub forma X Y C, cu semnificatia ca exista muchie neorientata intre X si Y de
// cost C. Fisierul de iesire apm.out va contine pe prima linie costul arborelui partial de cost minim. Pe a doua
// linie se va gasi numarul de muchii din arborele partial selectat. Fiecare din urmatoarele linii, pana la
// sfarsitul fisierului de iesire, va contine cate doua numere naturale, capetele unei muchii ce apartine
// arborelui solutie. Muchiile pot fi afisate in orice ordine. Daca sunt mai multe solutii corecte se poate afisa
// oricare.


#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

// Structură pentru o muchie: două noduri și costul
struct Edge {
    int u, v, cost;

    // Comparator pentru sortarea muchiilor în ordinea crescătoare a costului
    bool operator<(const Edge& other) const {
        return cost < other.cost;
    }
};

const int NMAX = 200005;
int parent[NMAX], rang[NMAX];

// Reprezentare disjunctă (DSU) - căutare cu compresie
int find(int x) {
    if (parent[x] != x)
        parent[x] = find(parent[x]);
    return parent[x];
}

// Unire cu rang (DSU)
void unite(int x, int y) {
    x = find(x);
    y = find(y);
    if (rang[x] < rang[y]) {
        parent[x] = y;
    } else if (rang[x] > rang[y]) {
        parent[y] = x;
    } else {
        parent[y] = x;
        rang[x]++;
    }
}

int main() {
    ifstream fin("../input.txt");
    ofstream fout("../output.txt");

    int n, m;
    fin >> n >> m;

    vector<Edge> edges(m);
    for (int i = 0; i < m; ++i) {
        fin >> edges[i].u >> edges[i].v >> edges[i].cost;
    }

    // Sortăm muchiile după cost
    sort(edges.begin(), edges.end());

    // Inițializăm DSU
    for (int i = 1; i <= n; ++i) {
        parent[i] = i;
        rang[i] = 0;
    }

    vector<Edge> mst_edges;  // muchiile arborelui minim
    long long total_cost = 0;

    // Kruskal: adăugăm muchii în arbore atâta timp cât nu formează cicluri
    for (const auto& edge : edges) {
        if (find(edge.u) != find(edge.v)) {
            unite(edge.u, edge.v);
            mst_edges.push_back(edge);
            total_cost += edge.cost;

            // Dacă avem deja n - 1 muchii, ne putem opri
            if ((int)mst_edges.size() == n - 1)
                break;
        }
    }

    // Scriem rezultatul în fișier
    fout << total_cost << '\n';
    fout << mst_edges.size() << '\n';
    for (const auto& edge : mst_edges) {
        fout << edge.v << " " << edge.u << '\n';
    }

    return 0;
}
