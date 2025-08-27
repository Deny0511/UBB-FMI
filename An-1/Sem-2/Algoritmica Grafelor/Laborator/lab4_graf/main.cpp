#include <iostream>
#include <fstream>

using namespace std;

ifstream f("../input.txt");
ofstream fout("../output.txt");

int fii[100], t[100], k[100], nr = 0;

void codarePrufer(int k[], int fii[], int t[], int n, int& nr)
{
    int copie = 0;
    bool gasit = false;
    while (!gasit)
    {
        for (int i = 0; i < n; i++) {
            gasit = true;
            if (fii[i] == 0)
            {
                gasit = false;
                copie = i;
                fii[i]--;

                if (t[i] != -1)
                    fii[t[i]]--;
                k[nr++] = t[copie];
                break;
            }
        }
    }
}

int main() {
    int n, x;
    f >> n;

    for (int i = 0; i < n; i++)
        fii[i] = 0;

    for (int i = 0; i < n; i++)
    {
        f >> x;
        t[i] = x;
        if (t[i] != -1)
            fii[t[i]]++;
    }

    codarePrufer(k, fii, t, n, nr);

    fout << nr - 1 << "\n";
    for (int i = 0; i < nr - 1; i++)
        fout << k[i] << " ";

    f.close();
    fout.close();
    return 0;
}
