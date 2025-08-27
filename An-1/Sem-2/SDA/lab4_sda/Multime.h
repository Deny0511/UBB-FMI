#pragma once

#define NULL_TELEM -1
typedef int TElem;

class IteratorMultime;

class Multime {
    friend class IteratorMultime;

private:
    /* aici e reprezentarea */
    TElem* elemente;  // Tablou dinamic
    int* urmator;     // Tablou dinamic pentru legaturile urmatorului element
    int prim;         // Indexul primului element din lista (-1 daca lista este goala)
    int dimensiune;   // Numarul de elemente din multime
    int capacitate;   // Capacitatea maxima a tabloului


public:
    //constructorul implicit
    Multime();

    //adauga un element in multime
    //returneaza adevarat daca elementul a fost adaugat (nu exista deja in multime)
    bool adauga(TElem e);

    //sterge un element din multime
    //returneaza adevarat daca elementul a existat si a fost sters
    bool sterge(TElem e);

    //verifica daca un element se afla in multime
    bool cauta(TElem elem) const;


    //intoarce numarul de elemente din multime;
    int dim() const;

    //verifica daca multimea e vida;
    bool vida() const;

    //returneaza un iterator pe multime
    IteratorMultime iterator() const;

    void reuniune(const Multime& b);


    // destructorul multimii
    ~Multime();
};




