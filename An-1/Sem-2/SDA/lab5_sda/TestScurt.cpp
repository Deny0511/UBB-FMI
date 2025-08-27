#include "TestScurt.h"
#include <assert.h>
#include "Matrice.h"
#include <iostream>

using namespace std;

void testIterator() {
    Matrice m(3, 4);

    m.modifica(0, 0, 5);
    m.modifica(1, 2, 7);
    m.modifica(2, 3, 9);

    IteratorMatrice it = m.iterator();

    int count = 0;
    int expectedElements[3][4] = {
        {5, 0, 0, 0},
        {0, 0, 7, 0},
        {0, 0, 0, 9}
    };

    while (it.valid()) {
        int lin = count / m.nrColoane();
        int col = count % m.nrColoane();
        TElem expected = expectedElements[lin][col];
        TElem actual = it.element();
        assert(actual == expected);
        it.urmator();
        count++;
    }

    assert(count == 12);
}

void testAll() { //apelam fiecare functie sa vedem daca exista
    Matrice m(4,4);
    assert(m.nrLinii() == 4);
    assert(m.nrColoane() == 4);
    //adaug niste elemente
    m.modifica(1,1,5);
    assert(m.element(1,1) == 5);
    m.modifica(1,1,6);
    assert(m.element(1,2) == NULL_TELEMENT);
    testIterator();

}
