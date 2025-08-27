#pragma once

#include <vector>

typedef int TCheie;
typedef int TValoare;


#include <utility>
typedef  bool (*Conditie)(TValoare);
typedef std::pair<TCheie, TValoare> TElem;
typedef bool(*Conditie)(TValoare);
using namespace std;

class IteratorMDO;

typedef bool(*Relatie)(TCheie, TCheie);

class MDO {
    friend class IteratorMDO;
private:
    /* aici e reprezentarea */

    struct NodVal {
        TElem elem;
        NodVal(TElem e) : elem(e) {}
    };

    struct NodABC {
        TCheie cheie;
        TValoare valoare;
        NodABC* st;
        NodABC* dr;

        NodABC(TCheie c, TValoare v) : cheie(c), valoare(v), st(nullptr), dr(nullptr) {}
    };

    NodABC* rad;
    Relatie rel;
    int numar_perechi;

    // functii auxiliare private
    void distruge_rec(NodABC* p);
    NodABC* adauga_rec(NodABC* p, TCheie c, TValoare v, bool& adaugat);
    NodABC* sterge_rec(NodABC* p, TCheie c, TValoare v, bool& sters);
    void cauta_rec(NodABC* p, TCheie c, vector<TValoare>& valori_gasite) const;
    NodABC* maxim(NodABC* p) const;
    NodABC* sterge_nod(NodABC* p);


    NodABC* filtreaza_rec(NodABC* p, Conditie cond);



public:
    void filtreaza(Conditie cond);
    // constructorul implicit al MultiDictionarului Ordonat
    MDO(Relatie r);

    // adauga o pereche (cheie, valoare) in MDO
    void adauga(TCheie c, TValoare v);

    //cauta o cheie si returneaza vectorul de valori asociate
    vector<TValoare> cauta(TCheie c) const;

    //sterge o cheie si o valoare
    //returneaza adevarat daca s-a gasit cheia si valoarea de sters
    bool sterge(TCheie c, TValoare v);

    //returneaza numarul de perechi (cheie, valoare) din MDO
    int dim() const;

    //verifica daca MultiDictionarul Ordonat e vid
    bool vid() const;

    // se returneaza iterator pe MDO
    // iteratorul va returna perechile in ordine in raport cu relatia de ordine
    IteratorMDO iterator() const;

    // destructorul
    ~MDO();

};
