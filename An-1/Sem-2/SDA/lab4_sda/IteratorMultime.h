#pragma once
#include "Multime.h"

class Multime;
typedef int TElem;

class IteratorMultime
{
    friend class Multime;
private:

    //constructorul primeste o referinta catre Container
    //iteratorul va referi primul element din container
    IteratorMultime(const Multime& m);

    //contine o referinta catre containerul pe care il itereaza
    const Multime& multime;
    /* aici e reprezentarea  specifica a iteratorului */
    int current;  // Folosim un index în loc de un pointer

public:

    //reseteaza pozitia iteratorului la inceputul containerului
    void prim();

    //muta iteratorul in container
    // arunca exceptie daca iteratorul nu e valid
    void urmator();

    //verifica daca iteratorul e valid (indica un element al containerului)
    bool valid() const;

    void anterior();

    //returneaza valoarea elementului din container referit de iterator
    //arunca exceptie daca iteratorul nu e valid
    TElem element() const;
};
