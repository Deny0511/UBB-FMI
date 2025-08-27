
//Sa consideram urmatoarea problema: Avem o multime de N orase in plan, date prin coordonatele lor X
//respectiv Y. Dorim sa proiectam o retea de drumuri astfel incat sa existe intotdeauna un traseu din orice
//oras de plecare A si orice alt oras de sosire B. Dupa cum bine stim, asfaltul ii scump, deci am dori sa
//minimizam costurile de constructie. Mai exact, acest cost este egal cu distanta in linie dreapta dintre
//pozitiile celor doua orase. In faza de proiectare sunt luate in considerare toate posibilitatile de a lega 2
//orase, toate muchiile posibile fiind valide (mai exact numarul lor este N*(N-1)/2).



#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <iomanip>
#include <fstream>

using namespace std;

struct Edge {
    int u, v;
    double cost;
};

int N;
vector<pair<int, int>> coords;
vector<Edge> edges;

vector<int> parent, rnk;

int find(int x) {
    if (parent[x] != x)
        parent[x] = find(parent[x]);
    return parent[x];
}

void unite(int x, int y) {
    x = find(x);
    y = find(y);
    if (x == y)
        return;
    if (rnk[x] < rnk[y])
        parent[x] = y;
    else {
        parent[y] = x;
        if (rnk[x] == rnk[y])
            rnk[x]++;
    }
}

double distance(int i, int j) {
    int dx = coords[i].first - coords[j].first;
    int dy = coords[i].second - coords[j].second;
    return sqrt(dx * dx + dy * dy);
}

int main() {
    ifstream fin("../input.txt");
    if (!fin.is_open()) {
        cerr << "Nu am putut deschide fisierul input.txt\n";
        return 1;
    }

    ofstream fout("../output.txt");
    if (!fout.is_open()) {
        cerr << "Nu am putut deschide fisierul output.txt\n";
        return 1;
    }

    fin >> N;
    coords.resize(N);
    for (int i = 0; i < N; i++) {
        fin >> coords[i].first >> coords[i].second;
    }

    // Construim toate muchiile posibile
    for (int i = 0; i < N; i++) {
        for (int j = i + 1; j < N; j++) {
            edges.push_back({i, j, distance(i, j)});
        }
    }

    // Sortam muchiile crescator dupa cost
    sort(edges.begin(), edges.end(), [](Edge a, Edge b) {
        return a.cost < b.cost;
    });

    // Initializam DSU
    parent.resize(N);
    rnk.resize(N, 0);
    for (int i = 0; i < N; i++)
        parent[i] = i;

    double totalCost = 0;
    for (const auto& e : edges) {
        if (find(e.u) != find(e.v)) {
            unite(e.u, e.v);
            totalCost += e.cost;
        }
    }

    fout << fixed << setprecision(3) << totalCost << "\n";

    fin.close();
    fout.close();

    return 0;
}
