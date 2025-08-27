#include "MD.h"
#include "IteratorMD.h"


using namespace std;

IteratorMD::IteratorMD(const MD& _md): md(_md) {
    /* de adaugat */
    prim();
}
//O(1)

TElem IteratorMD::element() const{
    /* de adaugat */
    if (!valid())
        throw exception();
    return { curentCheie->cheie, curentValoare->valoare };

    //	return pair <TCheie, TValoare>  (-1, -1);
}
//O(1)

bool IteratorMD::valid() const {
    /* de adaugat */

    return curentCheie != nullptr && curentValoare != nullptr;
    //return false;
}
//O(1)


void IteratorMD::urmator() {
    /* de adaugat */
    if (!valid())
        throw exception();

    curentValoare = curentValoare->urm;
    if (curentValoare == nullptr) {
        curentCheie = curentCheie->urm;
        curentValoare = (curentCheie != nullptr) ? curentCheie->primVal : nullptr;
    }
}
//O(1)

void IteratorMD::prim() {
    /* de adaugat */

    curentCheie = md.prim;
    curentValoare = (curentCheie != nullptr) ? curentCheie->primVal : nullptr;

}
//O(1)

