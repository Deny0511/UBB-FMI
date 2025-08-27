// Algoritmul pompare-preflux
#include <vector>
#include <iostream>
#include <fstream>
using namespace std;

struct Muchie
{
    // Retinem fluxul si capacitate
    int flux, capacitate;

    // o muchie se afla intre varfurile x si y
    int x, y;

    Muchie(int flux, int capacitate, int x, int y)
    {
        this->flux = flux;
        this->capacitate = capacitate;
        this->x = x;
        this->y = y;
    }
};

// reprezentarea unui nod
struct Varf
{
    // contine inaltimea varfului si excesul de flux
    int inaltime, exces_flux;

    Varf(int inaltime, int exces_flux)
    {
        this->inaltime = inaltime;
        this->exces_flux = exces_flux;
    }
};

// reprezentarea retelei de fluxuri
class Graf
{
    int V;    // numarul de varfuri
    vector<Varf> varf;
    vector<Muchie> muchie;

    // Functie de impingere a excesului de flux din varful u
    bool impinge(int u);

    // Functie relabel
    void relabel(int u);

    // Functie ce initializeaza prefluxul
    void preflux(int s);

    // Function ce inverseaza fluxul unei muchii
    void updateFluxInversMuchie(int i, int flux);

public:
    Graf(int V);  // Constructor

    // Functie ce adauga muchie
    void adaugaMuchie(int u, int v, int w);

    // returneaza fluxul maxim de la s la t
    int getMaxflux(int s, int t);
};

Graf::Graf(int V)
{
    this->V = V;

    // toate varfurile sunt initializate cu inaltime si exces 0
    for (int i = 0; i < V; i++)
        varf.push_back(Varf(0, 0));
}

void Graf::adaugaMuchie(int u, int v, int capacitate)
{
    // fluxul este initializat cu 0 pentru toate muchiile
    muchie.push_back(Muchie(0, capacitate, u, v));
}

void Graf::preflux(int s)
{
    // inaltime_sursa = numarul de varfuri V
    // inaltime_restul = 0
    varf[s].inaltime = varf.size();

    for (int i = 0; i < muchie.size(); i++)
    {
        // daca muchia curenta pleaca din sursa
        if (muchie[i].x == s)
        {
            // fluxul este egal cu capacitatea
            muchie[i].flux = muchie[i].capacitate;

            // initializam excesul de flux pentru nodul y
            varf[muchie[i].y].exces_flux += muchie[i].flux;

            // adaugam o muchie de la y la s in graful residual cu capacitate = 0
            muchie.push_back(Muchie(-muchie[i].flux, 0, muchie[i].y, s));
        }
    }
}

// returneaza indexul varfului cu exces de flux
int excesFluxVarf(vector<Varf>& varf)
{
    for (int i = 1; i < varf.size() - 1; i++)
        if (varf[i].exces_flux > 0)
            return i;

    // -1 daca nu exista un astfel de varf
    return -1;
}

// Update flux invers pentru fluxul adaugat pe a i-a muchie
void Graf::updateFluxInversMuchie(int i, int flux)
{
    int u = muchie[i].y, v = muchie[i].x;

    for (int j = 0; j < muchie.size(); j++)
    {
        if (muchie[j].y == v && muchie[j].x == u)
        {
            muchie[j].flux -= flux;
            return;
        }
    }

    // adaugam muchia inversa in graful rezidual
    Muchie m = Muchie(0, flux, u, v);
    muchie.push_back(m);
}

// Impingem fluxul din varful cu exces u
bool Graf::impinge(int u)
{
    // Traversam prin toate muchiile sa gasim adiacentul lui u prin care fluxul sa poata fi impins
    for (int i = 0; i < muchie.size(); i++)
    {
        // Verificam daca varful din muchia curenta este acelasi cu varful cu excess
        if (muchie[i].x == u)
        {
            // daca fluxul este egal cu capacitatea, nu mai putem impinge
            if (muchie[i].flux == muchie[i].capacitate)
                continue;

            // impingerea este posibila doar daca inaltimea adiacentului este mai mica decat inaltimea varfului cu exces
            if (varf[u].inaltime > varf[muchie[i].y].inaltime)
            {
                // fluxul de impins este egal cu minimul dintre fluxul ramas pe muchie si excesul de flux
                int flux = min(muchie[i].capacitate - muchie[i].flux,
                    varf[u].exces_flux);

                // Reducem excesul de flux din varful cu exces
                varf[u].exces_flux -= flux;

                // Marim excesul de flux din adiacent
                varf[muchie[i].y].exces_flux += flux;

                // adaugam flux residual cu capacitate 0 si flux negativ
                muchie[i].flux += flux;

                updateFluxInversMuchie(i, flux);

                return true;
            }
        }
    }
    return false;
}

// functie de relabel
void Graf::relabel(int u)
{
    // Initializam inaltimea minima a adiacentului
    int mh = INT_MAX;

    // Gasim adiacentul cu inaltime minima
    for (int i = 0; i < muchie.size(); i++)
    {
        if (muchie[i].x == u)
        {
            // daca fluxul este egal cu capacitate continuam
            if (muchie[i].flux == muchie[i].capacitate)
                continue;

            // Update la inaltimea minima
            if (varf[muchie[i].y].inaltime < mh)
            {
                mh = varf[muchie[i].y].inaltime;

                // update la inaltimea lui u
                varf[u].inaltime = mh + 1;
            }
        }
    }
}

// functie principala de printarea a fluxului maxim din graf
int Graf::getMaxflux(int s, int t)
{
    preflux(s);

    // facem loop pana niciun varf nu are exces
    while (excesFluxVarf(varf) != -1)
    {
        int u = excesFluxVarf(varf);
        if (!impinge(u))
            relabel(u);
    }

    // varf.back() returneaza ultimul varf, al carui exces_flux este fluxul maxim
    return varf.back().exces_flux;
}

// main
ifstream fin("../in.txt");
int main()
{
    int V, E, x, y, c;
    fin >> V;
    cout << "Numarul de varfuri este: ";
    cout << V << "." << endl;
    fin >> E;
    cout << "Numarul de arce este: ";
    cout << E << "." << endl;

    Graf g(V);

    cout << "Datele de intrare (nod sursa, nod destinatie, capacitate) sunt: " << endl;
    for (int i = 0; i < E; i++) {
        fin >> x >> y >> c;
        g.adaugaMuchie(x, y, c);
        cout << x << " " << y << " " << c << endl;
    }

    int s = 0, t = V-1;

    cout << "Fluxul maxim este: " << g.getMaxflux(s, t) << ".";
    return 0;
}