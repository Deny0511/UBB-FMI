#include "Multime.h"
#include "IteratorMultime.h"

#include <iostream>

Multime::Multime() : prim(-1), dimensiune(0), capacitate(10) {
    elemente = new TElem[capacitate];  // Alocam memorie pentru 10 elemente initial
    urmator = new int[capacitate];     // Alocam memorie pentru legaturile urmatoare
    for (int i = 0; i < capacitate; i++) {
        urmator[i] = -1;  // Inițializam toate legaturile la -1 (nu exista urmator)
    }
}


bool Multime::adauga(TElem elem) {
    // Verificam dacă elementul exista deja
    if (cauta(elem)) {
        return false;  // Elementul deja exista în mulțime
    }

    // Verificam daca avem suficient loc în tablou
    if (dimensiune == capacitate) {
        capacitate *= 2;
        TElem* elementeNou = new TElem[capacitate];
        int* urmatorNou = new int[capacitate];

        // Copiem vechile date
        for (int i = 0; i < dimensiune; i++) {
            elementeNou[i] = elemente[i];
            urmatorNou[i] = urmator[i];
        }

        // Inițializam restul locurilor cu -1
        for (int i = dimensiune; i < capacitate; i++) {
            urmatorNou[i] = -1;
        }

        delete[] elemente;
        delete[] urmator;

        elemente = elementeNou;
        urmator = urmatorNou;
    }

    // Adaugam elementul la inceputul listei
    int nouIndex = dimensiune;
    elemente[nouIndex] = elem;
    urmator[nouIndex] = prim;  // Legam noul element de primul element existent
    prim = nouIndex;           // Actualizam primul element

    dimensiune++;
    return true;
}
//O(n)


bool Multime::sterge(TElem elem) {
    // Cautam elementul și il ștergem
    int prev = -1;
    int current = prim;

    while (current != -1 && elemente[current] != elem) {
        prev = current;
        current = urmator[current];
    }

    if (current == -1) {
        return false;  // Elementul nu a fost găsit
    }

    if (prev == -1) {
        // Dacă elementul de sters este primul
        prim = urmator[current];
    } else {
        urmator[prev] = urmator[current];  // Leaga elementul precedent de urmatorul
    }

    dimensiune--;
    return true;
}
//O(n)

bool Multime::cauta(TElem elem) const {
    int current = prim;
    while (current != -1) {
        if (elemente[current] == elem) {
            return true;
        }
        current = urmator[current];
    }
    return false;
}
//O(n)


int Multime::dim() const {
    /* de adaugat */
    return dimensiune;
}
//O(1)

bool Multime::vida() const {
    /* de adaugat */
    return prim == -1;
}
//O(1)

Multime::~Multime() {
    delete[] elemente;
    delete[] urmator;
}
//O(n)



void Multime::reuniune(const Multime& b) {
    IteratorMultime it = b.iterator();
    while (it.valid()) {
        this->adauga(it.element());
        it.urmator();
    }
}
/* Subalgoritm reuniune(b: Multime)

 pre:
   - b este o multime valida
   - this este o multime valida

 post:
   - dimensiunea lui this’ ≥ dimensiunea inițiala a lui this


     it : IteratorMultime
     elem : TElement

     it ← b.iterator()

     CatTimp it.valid() executa
         elem ← it.element()
         adauga(elem)
         it.urmator()
     SfCatTimp

 SfSubalgoritm
*/

/*
 * Best case: O(dim(b))

   Average case: O(dim(b))

    Worst case: O(dim(b) * dim(this))
 *

*/









IteratorMultime Multime::iterator() const {
    return IteratorMultime(*this);
}
//O(1)
