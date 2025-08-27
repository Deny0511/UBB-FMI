#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <cstring>
using namespace std;

int main() {
    ifstream fin("../input.txt");
    ofstream fout("../output.txt");

    int N, M, E;
    fin >> N >> M >> E;

    int source = 0;
    int sink = N + M + 1;
    int size = sink + 1;

    vector<vector<int>> capacity(size, vector<int>(size, 0));
    vector<vector<int>> adj(size);

    for (int i = 0; i < E; ++i) {
        int u, v;
        fin >> u >> v;
        v += N;

        capacity[u][v] = 1;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    for (int u = 1; u <= N; ++u) {
        capacity[source][u] = 1;
        adj[source].push_back(u);
        adj[u].push_back(source);
    }

    for (int v = 1; v <= M; ++v) {
        int node = N + v;
        capacity[node][sink] = 1;
        adj[node].push_back(sink);
        adj[sink].push_back(node);
    }

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
