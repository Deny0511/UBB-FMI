#include <assert.h>

#include "MDO.h"
#include "IteratorMDO.h"

#include <exception>
#include <vector>

using namespace std;

bool relatie1(TCheie cheie1, TCheie cheie2) {
    if (cheie1 <= cheie2) {
        return true;
    }
    else {
        return false;
    }
}

bool estePar(int val) {
    return val % 2 == 0;
}

void testFiltreaza() {
    auto rel = [](int a, int b) { return a < b; };
    MDO mdo(rel);

    mdo.adauga(5, 2);
    mdo.adauga(5, 3);
    mdo.adauga(3, 4);
    mdo.adauga(3, 5);
    mdo.adauga(7, 8);
    mdo.adauga(7, 9);

    assert(mdo.dim() == 6);

    mdo.filtreaza(estePar);

    assert(mdo.dim() == 3);

    auto vals3 = mdo.cauta(3);
    assert(vals3.size() == 1 && vals3[0] == 4);

    auto vals5 = mdo.cauta(5);
    assert(vals5.size() == 1 && vals5[0] == 2);

    auto vals7 = mdo.cauta(7);
    assert(vals7.size() == 1 && vals7[0] == 8);
}


void testAll(){
    MDO dictOrd = MDO(relatie1);
    assert(dictOrd.dim() == 0);
    assert(dictOrd.vid());
    dictOrd.adauga(1,2);
    dictOrd.adauga(1,3);
    assert(dictOrd.dim() == 2);
    assert(!dictOrd.vid());
    vector<TValoare> v= dictOrd.cauta(1);
    assert(v.size()==2);
    v= dictOrd.cauta(3);
    assert(v.size()==0);
    IteratorMDO it = dictOrd.iterator();
    it.prim();
    while (it.valid()){
        TElem e = it.element();
        it.urmator();
    }
    assert(dictOrd.sterge(1, 2) == true);
    assert(dictOrd.sterge(1, 3) == true);
    assert(dictOrd.sterge(2, 1) == false);
    assert(dictOrd.vid());


    testFiltreaza();
}

