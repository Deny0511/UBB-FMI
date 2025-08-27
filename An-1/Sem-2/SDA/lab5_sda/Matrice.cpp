#include "Matrice.h"

#include <exception>
#include <cmath>

using namespace std;

Nod::Nod(Triplet e, Nod* urm) {
    this->elem = e;
    this->urm = urm;
}
//O(1)

Matrice::Matrice(int nrLinii, int nrColoane) {
    if (nrLinii <= 0 || nrColoane <= 0)
        throw exception();

    this->nr_linii = nrLinii;
    this->nr_coloane = nrColoane;

    for (int i = 0; i < MAX; i++)
        tabela[i] = nullptr;
}
//Θ(1)



int Matrice::nrLinii() const{

	return nr_linii;
}
//Θ(1)

int Matrice::nrColoane() const{

	return nr_coloane;
}
//Θ(1)

int Matrice::hash(int i, int j) const {
    return abs(i * nr_coloane + j) % MAX;
}

TElem Matrice::element(int i, int j) const{

    if (i < 0 || i >= nr_linii || j < 0 || j >= nr_coloane)
        throw exception();

    int poz = hash(i, j);
    PNod p = tabela[poz];
    while (p != nullptr) {
        if (p->elem.linie == i && p->elem.coloana == j)
            return p->elem.valoare;
        p = p->urm;
    }
    return NULL_TELEMENT;
}
//O(1)


TElem Matrice::modifica(int i, int j, TElem val) {
    if (i < 0 || i >= nr_linii || j < 0 || j >= nr_coloane)
        throw exception();

    int poz = hash(i, j);
    PNod p = tabela[poz], ant = nullptr;
    while (p != nullptr) {
        if (p->elem.linie == i && p->elem.coloana == j) {
            TElem vechi = p->elem.valoare;
            if (val == NULL_TELEMENT) {
                // Ștergem nodul
                if (ant == nullptr)
                    tabela[poz] = p->urm;
                else
                    ant->urm = p->urm;
                delete p;
            } else {
                p->elem.valoare = val;
            }
            return vechi;
        }
        ant = p;
        p = p->urm;
    }

    if (val != NULL_TELEMENT) {
        Triplet nou = { i, j, val };
        tabela[poz] = new Nod(nou, tabela[poz]);
    }
    return NULL_TELEMENT;
}
//O(1)


IteratorMatrice Matrice::iterator() const {
    return IteratorMatrice(*this);
}

//O(1)


















