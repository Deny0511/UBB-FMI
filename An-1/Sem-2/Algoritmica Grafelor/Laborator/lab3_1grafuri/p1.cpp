#include<iostream>
#include<fstream>
#include <climits>
using namespace std;

int n, m, x;
int mat[1001][1001], dist[1001];
bool sptSet[1001];

int minDistance()
{
    int min = INT_MAX, min_index = -1;
    for (int i = 0; i < n; i++)
    {
        if (!sptSet[i] && dist[i] < min)
        {
            min = dist[i];
            min_index = i;
        }
    }
    return min_index;
}

void dijkstra(int src)
{
    for (int i = 0; i < n; i++)
    {
        dist[i] = INT_MAX;
        sptSet[i] = false;
    }
    dist[src] = 0;

    for (int i = 0; i < n - 1; i++)
    {
        int u = minDistance();
        sptSet[u] = true;

        for (int v = 0; v < n; v++)
        {
            if (!sptSet[v] && mat[u][v] && dist[u] != INT_MAX && dist[u] + mat[u][v] < dist[v])
            {
                dist[v] = dist[u] + mat[u][v];
            }
        }
    }
}

int main(int argc, char* argv[])
{
    ifstream fin(argv[1]);
    ofstream fout(argv[2]);


    fin >> n >> m >> x;

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            mat[i][j] = 0;
        }
    }

    int a, b, s;
    while (fin >> a >> b >> s)
    {
        mat[a][b] = s;
    }

    dijkstra(x);

    for (int i = 0; i < n; i++)
    {
        if (dist[i] == INT_MAX)
        {
            fout << "INF ";
        }
        else
        {
            fout << dist[i] << " ";
        }
    }
    fout << endl;

    fin.close();
    fout.close();
    return 0;
}
