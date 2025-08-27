#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <cstring>
#include <climits>

using namespace std;

const int NMAX = 1005;

int capacity[NMAX][NMAX]; // capacitatea între noduri
int flow[NMAX][NMAX];     // fluxul curent între noduri
vector<int> adj[NMAX];    // lista de adiacență
int parent[NMAX];         // părinții din BFS pentru a reconstrui drumul

// BFS pentru a găsi un drum de creștere din sursă în destinație
bool bfs(int src, int dest, int N) {
    memset(parent, -1, sizeof(parent));
    queue<int> q;
    q.push(src);
    parent[src] = src;

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        for (int v : adj[u]) {
            if (parent[v] == -1 && capacity[u][v] > flow[u][v]) {
                parent[v] = u;
                if (v == dest) return true;
                q.push(v);
            }
        }
    }

    return false;
}

// Algoritmul Edmonds-Karp pentru flux maxim
int maxFlow(int src, int dest, int N) {
    int total_flow = 0;

    while (bfs(src, dest, N)) {
        int curr_flow = INT_MAX;

        // determină fluxul minim de pe drumul găsit
        for (int v = dest; v != src; v = parent[v]) {
            int u = parent[v];
            curr_flow = min(curr_flow, capacity[u][v] - flow[u][v]);
        }

        // actualizează fluxurile pe drum
        for (int v = dest; v != src; v = parent[v]) {
            int u = parent[v];
            flow[u][v] += curr_flow;
            flow[v][u] -= curr_flow;
        }

        total_flow += curr_flow;
    }

    return total_flow;
}

int main() {
    ifstream fin("../input.txt");
    ofstream fout("../output.txt");

    int N, M;
    fin >> N >> M;

    for (int i = 0; i < M; ++i) {
        int x, y, c;
        fin >> x >> y >> c;

        // transformăm în indexare de la 0
        --x; --y;

        capacity[x][y] += c;
        adj[x].push_back(y);
        adj[y].push_back(x); // pentru graful rezidual
    }

    int flux = maxFlow(0, N - 1, N);

    fout << flux << ".000\n"; // conform cerinței
    return 0;
}




//
// O retea de transport este un graf orientat in care fiecare muchie are asociata o capacitate si o anumita
// cantitate de flux. Fluxul primit de fiecare muchie trebuie sa fie mai mic sau egal decat capacitatea acesteia.
// De asemenea, pentru fiecare nod, fluxul care intra in nod trebuie sa fie egal cu cantitatea de flux care iese
// din nod. Cu alte cuvinte, suma fluxurilor asociate muchiilor care intra intr-un nod trebuie sa fie egala cu
// suma fluxurilor asociate muchiilor care ies din nod, exceptie facand nodurile speciale S si D, denumite
// sursa, respectiv, destinatie. Din nodul sursa poate doar iesi flux, in timp ce in nodul destinatie poate doar
// intra flux. Valoarea fluxului unei astfel retele este egal cu suma fluxului care iese din sursa sau cu suma
// fluxului care intra in destinatie (cele doua fluxuri sunt egale).
// Dandu-se o retea de transport, in care initial fluxul pe fiecare muchie este 0, sa se calculeze fluxul maxim
// care poate fi trimis prin aceasta retea. Fisierul de intrare „input.in” va contine pe prima linie 2 numere, N si
// M, reprezentand numarul de noduri si numarul de muchii din retea. Pe fiecare din urmatoarele M linii, se
// vor afla cate 3 numere naturale, X, Y si C, cu semnificatia ca exista o muchie care porneste de la nodul X,
// ajunge in nodul Y si are capacitatea C. In fisierul de iesire „output.out” se va afla un singur numar F,
// reprezentand fluxul maxim ce poate fi trimis prin retea.






