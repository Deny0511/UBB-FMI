#pragma once
#include <exception>

typedef int TElem;

#define NULL_TELEMENT 0
#define MAX 10007

struct Triplet {
    int linie, coloana;
    TElem valoare;
};
// Nod pentru lista inlantuita
class Nod {
private:
    Triplet elem;
    Nod* urm;
public:
    friend class Matrice;
    Nod(Triplet e, Nod* urm);
};

typedef Nod* PNod;


class IteratorMatrice;


class Matrice {

private:
    /* aici e reprezentarea */
    int nr_linii;
    int nr_coloane;
    PNod tabela[MAX]; // tabela de dispersie cu liste independente

    int hash(int i, int j) const;

public:

    // crează un iterator asupra tuturor elementelor din Matrice
    IteratorMatrice iterator() const;


    //constructor
    //se arunca exceptie daca nrLinii<=0 sau nrColoane<=0
    Matrice(int nrLinii, int nrColoane);


    //destructor
    ~Matrice(){};

    //returnare element de pe o linie si o coloana
    //se arunca exceptie daca (i,j) nu e pozitie valida in Matrice
    //indicii se considera incepand de la 0
    TElem element(int i, int j) const;


    // returnare numar linii
    int nrLinii() const;

    // returnare numar coloane
    int nrColoane() const;


    // modificare element de pe o linie si o coloana si returnarea vechii valori
    // se arunca exceptie daca (i,j) nu e o pozitie valida in Matrice
    TElem modifica(int i, int j, TElem);

    void redimensioneaza(int numarNouLinii, int numarNouColoane) ;


};




class IteratorMatrice {
private:
    const Matrice& mat;
    int linie_curenta;
    int coloana_curenta;

public:
    IteratorMatrice(const Matrice& m) : mat(m) {
        prim();
    }
    //O(1)

    void prim() {
        linie_curenta = 0;
        coloana_curenta = 0;
    }
    //O(1)

    void urmator() {
        if (!valid())
            throw std::exception();

        coloana_curenta++;
        if (coloana_curenta == mat.nrColoane()) {
            coloana_curenta = 0;
            linie_curenta++;
        }
    }
    //O(1)

    bool valid() const {
        return linie_curenta < mat.nrLinii();
    }
    //O(1)

    TElem element() const {
        if (!valid())
            throw std::exception();

        return mat.element(linie_curenta, coloana_curenta);
    }
    //O(n) caz nefavorabil, o(1) in rest
};


// clasa IteratorMatrice:
//     atribute private:
// mat: referinta constanta la Matrice
// linie_curenta: intreg
// coloana_curenta: intreg
//
// public:
// Constructor(m: Matrice):
//     mat <- m
//     prim()
//
// subalgoritm prim(it):
//
//     linie_curenta <- 0
//     coloana_curenta <- 0
//
// subalgoritm urmator():
//     dacă valid() = fals atunci
//         aruncă excepție
//
//     coloana_curenta <- coloana_curenta + 1
//
//     daca coloana_curenta = mat.nrColoane() atunci
//         coloana_curenta<- 0
//         linie_curenta <- linie_curenta + 1
//
// subalgoritm valid() returneaza boolean:
//     returnează (linie_curenta < mat.nrLinii())
//
// subalgoritm element() returnează TElem:
//     dacă valid() = fals atunci
//         aruncă excepție
//
//     returneaza mat.element(linie_curenta, coloana_curenta)
