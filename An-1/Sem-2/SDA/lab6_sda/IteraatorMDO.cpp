#include "IteratorMDO.h"
#include "MDO.h"

IteratorMDO::IteratorMDO(const MDO& d) : dict(d), stiva(nullptr){
    prim();
}

void IteratorMDO::apasa_stiva(MDO::NodABC* nod) {
    while (nod != nullptr) {
        stiva = new NodStiva(nod, stiva);
        nod = nod->st;
    }
}

void IteratorMDO::prim() {
    while (stiva != nullptr) {
        NodStiva* temp = stiva;
        stiva = stiva->urm;
        delete temp;
    }
    apasa_stiva(dict.rad);
}


void IteratorMDO::urmator() {
    if (!valid())
        throw std::exception();

    // scoatem nodul din varful stivei
    NodStiva* varf = stiva;
    MDO::NodABC* nod_curent = varf->nod;
    stiva = varf->urm;
    delete varf;

    // daca nodul curent are subarbore drept, apasam stiva pe el
    if (nod_curent->dr != nullptr)
        apasa_stiva(nod_curent->dr);
}

bool IteratorMDO::valid() const {
    return stiva != nullptr;
}

TElem IteratorMDO::element() const {
    if (!valid())
        throw std::exception();

    MDO::NodABC* nod_curent = stiva->nod;
    // Nu mai avem pointer, deci nu mai verificam nullptr pentru valoare
    return TElem(nod_curent->cheie, nod_curent->valoare);
}

