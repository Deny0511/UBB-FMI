#include "MDO.h"
#include "IteratorMDO.h"
#include <iostream>

#include "TestScurt.h"
#include "TestExtins.h"
using namespace std;

// Relația de ordine: cheile în ordine crescătoare
bool relatie(TCheie c1, TCheie c2) {
    return c1 <= c2;
}

int main(){
    MDO d(relatie);

    // Adăugăm perechi (cheie, valoare) în MDO
    d.adauga(2, 10);
    d.adauga(4, 20);
    d.adauga(2, 30);
    d.adauga(5, 40);
    d.adauga(4, 50);
    d.adauga(1, 60);

    cout << "Elementele din MDO sunt:\n";

    // Tipărim MDO-ul folosind iteratorul
    IteratorMDO it = d.iterator();
    it.prim();
    while (it.valid()) {
        TElem e = it.element();
        cout << "(" << e.first << ", " << e.second << ") ";
        it.urmator();
    }
    cout << endl;

        testAll();
        testAllExtins();
    std::cout<<"Finished Tests!"<<std::endl;
}
