// Sa consideram urmatoarea problema: Avem o retea de conducte prin care poate curge petrol. Fiecare
// conducta are o capacitate ce determina cantitatea maxima de petrol ce trece prin conducta respectiva intr-o
// unitate de timp. Considerand ca avem o sursa de unde se pompeaza petrolul si o destinatie unde dorim sa
// ajunga petrolul, care este debitul maxim de petrol (cantitatea de petrol pe unitatea de timp) ce poate ajunge
// de la sursa la destinatie folosind reteaua de conducte existenta?
// Fișierul de intrare conține pe prima linie 2 numere separate prin spațiu V E unde V reprezintă numărul de
// vârfuri ale grafului iar E reprezintă numărul de arce ale grafului.
// Următoarele E linii conțin câte 3 numere separate prin spațiu, reprezentând câte un arc: X Y C. X este nodul
//sursă al arcului, Y este nodul destinație, iar C este capacitatea arcului. Indexarea vârfurilor se face de la 0.
//Vârful sursă este 0, iar vârful destinație este (V - 1).


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

    int V, E;
    fin >> V >> E;

    vector<vector<Edge>> adj(V);

    // Functie pentru adaugarea muchiilor cu arc invers
    auto addEdge = [&](int u, int v, int cap) {
        adj[u].push_back({v, (int)adj[v].size(), cap});
        adj[v].push_back({u, (int)adj[u].size() - 1, 0});
    };

    for (int i = 0; i < E; i++) {
        int X, Y, C;
        fin >> X >> Y >> C;
        addEdge(X, Y, C);
    }

    int s = 0, t = V - 1;
    int max_flow = 0;

    while (true) {
        vector<int> parent(V, -1);
        vector<int> parentEdge(V, -1);
        queue<int> q;
        q.push(s);
        parent[s] = s;

        // BFS pentru gasirea unui drum de crestere
        while (!q.empty() && parent[t] == -1) {
            int u = q.front();
            q.pop();
            for (int i = 0; i < (int)adj[u].size(); i++) {
                Edge &e = adj[u][i];
                if (parent[e.to] == -1 && e.capacity > 0) {
                    parent[e.to] = u;
                    parentEdge[e.to] = i;
                    q.push(e.to);
                    if (e.to == t)
                        break;
                }
            }
        }

        if (parent[t] == -1) {
            // Nu mai exista drum de crestere
            break;
        }

        // Gasim capacitatea minima pe drum
        int path_flow = INT_MAX;
        for (int v = t; v != s; v = parent[v]) {
            int u = parent[v];
            int idx = parentEdge[v];
            path_flow = min(path_flow, adj[u][idx].capacity);
        }

        // Actualizam capacitatile
        for (int v = t; v != s; v = parent[v]) {
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
