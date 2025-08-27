#include "IteratorMultime.h"
#include "Multime.h"
#include <iostream>

IteratorMultime::IteratorMultime(const Multime& m) : multime(m){
    /* de adaugat */
    current = multime.prim;
}
//O(1)

void IteratorMultime::prim() {
    /* de adaugat */
    current = multime.prim;
}
//O(1)

void IteratorMultime::urmator() {
    /* de adaugat */
    if (valid()) {
        current = multime.urmator[current];  // Folosim tabloul urmator[] pentru a obține următorul index
    } else {
        throw std::out_of_range("Iteratorul nu este valid");
    }
}
//O(1)


TElem IteratorMultime::element() const {
    /* de adaugat */
    if (valid()) {
        return multime.elemente[current];  // Returnăm elementul din tabloul elemente[] la indexul curent
    } else {
        throw std::out_of_range("Iteratorul nu este valid");
    }

}
//O(1)

bool IteratorMultime::valid() const {
    /* de adaugat */
    return current != -1;  // -1 semnifică că am ajuns la sfârșit
}
//O(1)




void IteratorMultime::anterior() {
    if (!valid()) {
        throw std::out_of_range("Iterator invalid: nu se poate merge la anterior.");
    }

    if (current == multime.prim) {
        current = -1;
    } else {
        int prev = multime.prim;
        while (multime.urmator[prev] != current) {
            prev = multime.urmator[prev];
        }
        current = prev;
    }
}


/*
 *Subalgoritm anterior()
 *pre:curent != -1  {iterator valid}
 *
 *Daca curent = prim atunci
 *  curent ← -1  {iterator devine nevalid}
 *altfel
 *  prev ← prim
 *  CatTimp urmator[prev] != curent executa
 *      prev ← urmator[prev]
 *  SfCatTimp
 *  curent ← prev
 * SfSubalgoritm
 */


//BestCase:O(1)
//AverageCase:O(n)
//WorstCase:O(n)

