#include <iostream>
#include <fstream>

using namespace std;

const int MAX_N = 100;

int adj[MAX_N][MAX_N];
int visited[MAX_N];
int component[MAX_N];
int n, m;

void dfs(int node, int& count) {
    visited[node] = 1;
    component[count++] = node;
    for (int i = 1; i <= n; i++) {
        if (adj[node][i] && !visited[i]) {
            dfs(i, count);
        }
    }
}

int main() {
    ifstream fin("C:/Users/urdad/testgrafuri/fisier.txt");

    fin >> n >> m;

    for (int i = 0; i < m; i++) {
        int x, y;
        fin >> x >> y;
        adj[x][y] = 1;
        adj[y][x] = 1;
    }

    for (int i = 1; i <= n; i++) {
        if (!visited[i]) {
            int count = 0;
            dfs(i, count);

            cout << "[";
            for (int j = 0; j < count; j++) {
                cout << component[j];
                if (j < count - 1) cout << ", ";
            }
            cout << "]\n";
        }
    }

    return 0;
}