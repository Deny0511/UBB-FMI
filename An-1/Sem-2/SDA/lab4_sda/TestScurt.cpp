#include "TestScurt.h"
#include <assert.h>
#include "Multime.h"
#include "IteratorMultime.h"
#include <exception>
#include <stdexcept>


void testReuniune() {
    Multime a;
    a.adauga(1);
    a.adauga(2);
    a.adauga(3);

    Multime b;
    b.adauga(3);
    b.adauga(4);
    b.adauga(5);

    a.reuniune(b);

    // A ar trebui să conțină: 1, 2, 3, 4, 5
    assert(a.dim() == 5);
    assert(a.cauta(1));
    assert(a.cauta(2));
    assert(a.cauta(3));
    assert(a.cauta(4));
    assert(a.cauta(5));

}



void testAnteriorSimplu() {
    Multime m;
    m.adauga(1);
    m.adauga(2);

    IteratorMultime it = m.iterator();
    it.prim();

    it.urmator();
    TElem second = it.element();

    it.anterior();
    TElem first = it.element();

    assert(it.valid());

    assert(first != second);

    it.anterior();
    assert(!it.valid());

    bool exceptie = false;
    try {
        it.anterior();
    } catch (const std::out_of_range&) {
        exceptie = true;
    }
    assert(exceptie);
}



void testAll() { //apelam fiecare functie sa vedem daca exista
    Multime m;
    assert(m.vida() == true);
    assert(m.dim() == 0); //adaug niste elemente
    assert(m.adauga(5)==true);
    assert(m.adauga(1)==true);
    assert(m.adauga(10)==true);
    assert(m.adauga(7)==true);
    assert(m.adauga(1)==false);
    assert(m.adauga(10)==false);
    assert(m.adauga(-3)==true);
    assert(m.dim() == 5);
    assert(m.cauta(10) == true);
    assert(m.cauta(16) == false);
    assert(m.sterge(1) == true);
    assert(m.sterge(6) == false);
    assert(m.dim() == 4);


    IteratorMultime im = m.iterator();
    im.prim();
    int s = 0;
    while (im.valid()) {
        TElem e = im.element();
        s += e;
        im.urmator();
    }
    assert(s == 19);
    testReuniune();
    testAnteriorSimplu();

}
