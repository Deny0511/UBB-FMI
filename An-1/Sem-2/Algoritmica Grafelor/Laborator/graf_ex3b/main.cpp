// Sa consideram urmatoarea problema: Se dă un graf neorientat bipartit G = (V = (L, R), E). Un cuplaj în G
// este o submulţime de muchii M astfel încât pentru toate vârfurile v din V, există cel mult o muchie în M
// incidentă în v. Un cuplaj maxim este un cuplaj de cardinalitate maximă. Dându-se un graf neorientat
// bipartit G să se determine un cuplaj maxim.
// Fişierul de intrare conţine pe prima linie trei numere naturale N, M şi E, unde N reprezintă cardinalul
// mulţimii L iar M cardinalul mulţimii R. Pe următoarele E linii se vor afla câte două numere naturale,
// separate între ele printr-un spaţiu, u şi v, cu semnificaţia că există muchie de la nodul u din L la nodul v din
// R. În fişierul de ieşire veţi afişa pe prima linie un singur număr reprezentând cuplajul maxim.
// Hint: Se introduc 2 noduri virtuale, SURSA cu index 0, respectiv DESTINATIA cu index N+M+1. Se adauga
// muchii de capacitate 1 intre SURSA si toate nodurile din L, muchii de capacitate 1 intre toate nodurile din R
// si DESTINATIE, si nu in ultimul rand, muchii de capacitate 1 intre nodurile din L si nodurile din R,
// conform fisierului de intrare. Se determina fluxul maxim in aceasta retea de transport. Pentru usurinta
// reprezentarii, cand cititi o muchie (x, y) din fisierul de intrare, aceasta devine in reteaua noastra (x, y + N).


#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include <fstream>

using namespace std;

struct Edge {
    int to, rev;
    int capacity;
};

int main() {
    ifstream fin("../input.txt");
    if (!fin.is_open()) {
        cerr << "Nu pot deschide fisierul input.in\n";
        return 1;
    }
    ofstream fout("../output.txt");
    if (!fout.is_open()) {
        cerr << "Nu pot deschide fisierul output.out\n";
        return 1;
    }

    int N, M, E;
    fin >> N >> M >> E;

    int S = 0;
    int T = N + M + 1;

    vector<vector<Edge>> adj(T + 1);

    auto addEdge = [&](int u, int v, int cap) {
        adj[u].push_back({v, (int)adj[v].size(), cap});
        adj[v].push_back({u, (int)adj[u].size() - 1, 0});
    };

    // Muchii de la sursa la L
    for (int i = 1; i <= N; i++) {
        addEdge(S, i, 1);
    }

    // Muchii de la R la destinatie
    for (int i = 1; i <= M; i++) {
        addEdge(N + i, T, 1);
    }

    // Muchii intre L si R conform input-ului
    for (int i = 0; i < E; i++) {
        int u, v;
        fin >> u >> v;
        addEdge(u, N + v, 1);
    }

    int max_flow = 0;
    while (true) {
        vector<int> parent(T + 1, -1);
        vector<int> parentEdge(T + 1, -1);
        queue<int> q;
        q.push(S);
        parent[S] = S;

        // BFS pentru drum de crestere
        while (!q.empty() && parent[T] == -1) {
            int u = q.front();
            q.pop();
            for (int i = 0; i < (int)adj[u].size(); i++) {
                Edge &e = adj[u][i];
                if (parent[e.to] == -1 && e.capacity > 0) {
                    parent[e.to] = u;
                    parentEdge[e.to] = i;
                    q.push(e.to);
                    if (e.to == T)
                        break;
                }
            }
        }

        if (parent[T] == -1)
            break;

        int path_flow = INT_MAX;
        for (int v = T; v != S; v = parent[v]) {
            int u = parent[v];
            int idx = parentEdge[v];
            path_flow = min(path_flow, adj[u][idx].capacity);
        }

        for (int v = T; v != S; v = parent[v]) {
            int u = parent[v];
            int idx = parentEdge[v];
            adj[u][idx].capacity -= path_flow;
            adj[v][adj[u][idx].rev].capacity += path_flow;
        }

        max_flow += path_flow;
    }

    fout << max_flow << "\n";

    fin.close();
    fout.close();

    return 0;
}


