#pragma once
#include<vector>
#include<utility>

using namespace std;

typedef int TCheie;
typedef int TValoare;

typedef std::pair<TCheie, TValoare> TElem;

#define NULL_TVALOARE -1
#define NULL_TELEM std::pair<int, int>(-1, -1)

class IteratorMD;

struct NodValoare {
    TValoare valoare;
    NodValoare* urm;
    NodValoare* ant;

    NodValoare(TValoare v) : valoare(v), urm(nullptr), ant(nullptr) {}
};

struct NodCheie {
    TCheie cheie;
    NodValoare* primVal;
    NodValoare* ultimVal;
    NodCheie* urm;
    NodCheie* ant;
    NodCheie(TCheie c) : cheie(c), primVal(nullptr), ultimVal(nullptr), urm(nullptr), ant(nullptr) {}
};


class MD
{
    friend class IteratorMD;

private:
    /* aici e reprezentarea */

    NodCheie* prim;
    NodCheie* ultim;
    int nrElem;


public:
    // constructorul implicit al MultiDictionarului
    MD();

    // adauga o pereche (cheie, valoare) in MD
    void adauga(TCheie c, TValoare v);

    //cauta o cheie si returneaza vectorul de valori asociate
    vector<TValoare> cauta(TCheie c) const;

    //sterge o cheie si o valoare
    //returneaza adevarat daca s-a gasit cheia si valoarea de sters
    bool sterge(TCheie c, TValoare v);

    //returneaza numarul de perechi (cheie, valoare) din MD
    int dim() const;

    //verifica daca MultiDictionarul e vid
    bool vid() const;

    // se returneaza iterator pe MD
    IteratorMD iterator() const;

    void goleste();

    // destructorul MultiDictionarului
    ~MD();



};

