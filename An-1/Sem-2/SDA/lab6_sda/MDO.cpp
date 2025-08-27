#include "IteratorMDO.h"
#include "MDO.h"
#include <iostream>
#include <vector>

#include <exception>
using namespace std;

MDO::MDO(Relatie r) {
    rad = nullptr;
    rel = r;
    numar_perechi = 0;

}
//O(1)

void MDO::distruge_rec(NodABC* p) {
    if (p) {
        distruge_rec(p->st);
        distruge_rec(p->dr);
        delete p;
    }
}
//O(n)

void MDO::adauga(TCheie c, TValoare v) {
    bool adaugat = false;
    rad = adauga_rec(rad, c, v, adaugat);
    if (adaugat)
        numar_perechi++;
}

MDO::NodABC* MDO::adauga_rec(NodABC* p, TCheie c, TValoare v, bool& adaugat) {
    if (p == nullptr) {
        adaugat = true;
        return new NodABC(c, v);
    }
    if (rel(c, p->cheie)) {
        p->st = adauga_rec(p->st, c, v, adaugat);
    } else {
        p->dr = adauga_rec(p->dr, c, v, adaugat);
    }
    return p;
}
//O(log n)

vector<TValoare> MDO::cauta(TCheie c) const {
    vector<TValoare> valori_gasite;
    cauta_rec(rad, c, valori_gasite);
    return valori_gasite;
}
//O(log n + m)


void MDO::cauta_rec(NodABC* p, TCheie c, vector<TValoare>& valori_gasite) const {
    if (p == nullptr) return;
    if (p->cheie == c)
        valori_gasite.push_back(p->valoare);

    cauta_rec(p->st, c, valori_gasite);
    cauta_rec(p->dr, c, valori_gasite);
}


bool MDO::sterge(TCheie c, TValoare v) {
    bool sters = false;
    rad = sterge_rec(rad, c, v, sters);
    if (sters)
        numar_perechi--;
    return sters;
}

MDO::NodABC* MDO::sterge_rec(NodABC* p, TCheie c, TValoare v, bool& sters) {
    if (p == nullptr) return nullptr;

    if (p->cheie == c && p->valoare == v) {
        sters = true;
        // Ștergere nod
        if (p->st == nullptr) {
            NodABC* dreapta = p->dr;
            delete p;
            return dreapta;
        } else if (p->dr == nullptr) {
            NodABC* stanga = p->st;
            delete p;
            return stanga;
        } else {
            // nod cu 2 copii: găsește maximul din subarborele stâng
            NodABC* maxSt = maxim(p->st);
            p->cheie = maxSt->cheie;
            p->valoare = maxSt->valoare;
            p->st = sterge_rec(p->st, maxSt->cheie, maxSt->valoare, sters);
            return p;
        }
    }

    if (rel(c, p->cheie)) {
        p->st = sterge_rec(p->st, c, v, sters);
    } else {
        p->dr = sterge_rec(p->dr, c, v, sters);
    }
    return p;
}
//O(log n + m)


MDO::NodABC* MDO::maxim(NodABC* p) const {
    while (p && p->dr)
        p = p->dr;
    return p;
}
//O(log n)
int MDO::dim() const {
    return numar_perechi;
}
//O(1)
bool MDO::vid() const {
    return rad == nullptr;
}
//O(1)
IteratorMDO MDO::iterator() const {
    return IteratorMDO(*this);
}
//O(1)
MDO::~MDO() {
    distruge_rec(rad);
}
//O(1)

MDO::NodABC* MDO::sterge_nod(NodABC* nod) {
    if (nod == nullptr)
        return nullptr;

    // Cazuri de stergere:
    if (nod->st == nullptr) {
        NodABC* temp = nod->dr;
        delete nod;
        return temp;
    }
    else if (nod->dr == nullptr) {
        NodABC* temp = nod->st;
        delete nod;
        return temp;
    }
    else {
        // Nod cu doi copii - gaseste succesorul
        NodABC* succParent = nod;
        NodABC* succ = nod->dr;
        while (succ->st != nullptr) {
            succParent = succ;
            succ = succ->st;
        }

        // Copiaza datele succesorului in nodul curent
        nod->cheie = succ->cheie;
        nod->valoare = succ->valoare;

        // Sterge succesorul
        if (succParent != nod)
            succParent->st = sterge_nod(succ);
        else
            succParent->dr = sterge_nod(succ);

        return nod;
    }
}


void MDO::filtreaza(Conditie cond) {
    rad = filtreaza_rec(rad, cond);
}

MDO::NodABC* MDO::filtreaza_rec(NodABC* p, Conditie cond) {
    if (p == nullptr)
        return nullptr;

    // Apel recursiv pe subarborii stang si drept
    p->st = filtreaza_rec(p->st, cond);
    p->dr = filtreaza_rec(p->dr, cond);

    // Verificam valoarea din nodul curent
    if (!cond(p->valoare)) {
        // Stergem nodul deoarece valoarea nu respecta conditia
        numar_perechi--;
        return sterge_nod(p);
    }

    return p;
}

//AverageCase:O(n)
//BestCase:O(n)
//WorstCase:O(n)


// functie filtreaza_rec(M,nod p, conditie cond)
//     daca p este null atunci
//         returneaza null
//
//
//     p.st = filtreaza_rec(p.st, cond)
//     p.dr = filtreaza_rec(p.dr, cond)
//
//     daca cond(p.valoare) este falsa atunci
//         decrementam numar_perechi
//         return sterge_nod(p)
//
//     return p