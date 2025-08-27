//ex nota 10


// Sa consideram urmatoarea problema: Avem o retea de conducte prin care poate curge petrol. Fiecare
// conducta are o capacitate ce determina cantitatea maxima de petrol ce trece prin conducta respectiva intr-o
// unitate de timp. Considerand ca avem o sursa de unde se pompeaza petrolul si o destinatie unde dorim sa
// ajunga petrolul, care este debitul maxim de petrol (cantitatea de petrol pe unitatea de timp) ce poate ajunge
// de la sursa la destinatie folosind reteaua de conducte existenta?
// Fișierul de intrare conține pe prima linie 2 numere separate prin spațiu V E unde V reprezintă numărul de
// vârfuri ale grafului iar E reprezintă numărul de arce ale grafului.
// Următoarele E linii conțin câte 3 numere separate prin spațiu, reprezentând câte un arc: X Y C. X este nodul
// sursă al arcului, Y este nodul destinație, iar C este capacitatea arcului. Indexarea vârfurilor se face de la 0.
// Vârful sursă este 0, iar vârful destinație este (V - 1).





#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <climits>
#include <cstring>

using namespace std;

const int NMAX = 1005; // Număr maxim de noduri (se poate ajusta)
int capacity[NMAX][NMAX]; // Capacitățile conductelor
int flow[NMAX][NMAX];     // Fluxul curent prin fiecare conductă
vector<int> adj[NMAX];    // Lista de adiacență pentru graf
int parent[NMAX];         // Vector pentru a reconstrui drumul de creștere

// BFS pentru a găsi un drum de creștere din sursă în destinație
bool bfs(int src, int dest, int V) {
    memset(parent, -1, sizeof(parent));
    queue<int> q;
    q.push(src);
    parent[src] = src;

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        for (int v : adj[u]) {
            // Dacă v nu a fost vizitat și mai există capacitate reziduală
            if (parent[v] == -1 && capacity[u][v] > flow[u][v]) {
                parent[v] = u;
                if (v == dest)
                    return true;
                q.push(v);
            }
        }
    }
    return false;
}

int maxFlow(int src, int dest, int V) {
    int total_flow = 0;

    // Cât timp există un drum de creștere
    while (bfs(src, dest, V)) {
        // Găsim fluxul minim pe drumul de creștere găsit
        int curr_flow = INT_MAX;
        for (int v = dest; v != src; v = parent[v]) {
            int u = parent[v];
            curr_flow = min(curr_flow, capacity[u][v] - flow[u][v]);
        }

        // Actualizăm fluxurile de-a lungul drumului
        for (int v = dest; v != src; v = parent[v]) {
            int u = parent[v];
            flow[u][v] += curr_flow;
            flow[v][u] -= curr_flow; // flux invers pentru graful rezidual
        }

        total_flow += curr_flow;
    }

    return total_flow;
}

int main() {
    ifstream fin("../input.txt");
    ofstream fout("../output.txt");

    int V, E;
    fin >> V >> E;

    for (int i = 0; i < E; ++i) {
        int u, v, c;
        fin >> u >> v >> c;

        // Adăugăm arcul în graf
        capacity[u][v] += c; // Dacă există mai multe arce u->v, le cumulăm
        adj[u].push_back(v);
        adj[v].push_back(u); // Adăugăm și invers pentru fluxuri reziduale
    }

    int result = maxFlow(0, V - 1, V); // sursă = 0, destinație = V - 1
    fout << result << '\n';

    return 0;
}

















































#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <cstring>
using namespace std;

int main() {
    ifstream fin("input.txt");
    ofstream fout("output.txt");

    int N, M, E;
    fin >> N >> M >> E;

    int source = 0;
    int sink = N + M + 1;
    int size = sink + 1;

    vector<vector<int>> capacity(size, vector<int>(size, 0));
    vector<vector<int>> adj(size);

    // Citire muchii
    for (int i = 0; i < E; ++i) {
        int u, v;
        fin >> u >> v;
        v += N; // offset pentru nodurile din R

        capacity[u][v] = 1;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    // Conectăm sursa la L
    for (int u = 1; u <= N; ++u) {
        capacity[source][u] = 1;
        adj[source].push_back(u);
        adj[u].push_back(source);
    }

    // Conectăm R la destinație
    for (int v = 1; v <= M; ++v) {
        int node = N + v;
        capacity[node][sink] = 1;
        adj[node].push_back(sink);
        adj[sink].push_back(node);
    }

    // Algoritmul Edmonds-Karp
    int max_flow = 0;
    vector<int> parent(size);

    while (true) {
        fill(parent.begin(), parent.end(), -1);
        queue<int> q;
        q.push(source);
        parent[source] = -2;

        while (!q.empty()) {
            int u = q.front();
            q.pop();
            for (int v : adj[u]) {
                if (parent[v] == -1 && capacity[u][v] > 0) {
                    parent[v] = u;
                    if (v == sink) break;
                    q.push(v);
                }
            }
        }

        if (parent[sink] == -1)
            break;

        // Drum găsit -> augmentăm fluxul
        int v = sink;
        while (v != source) {
            int u = parent[v];
            capacity[u][v] -= 1;
            capacity[v][u] += 1;
            v = u;
        }

        max_flow += 1;
    }

    fout << max_flow << '\n';

    return 0;
}
