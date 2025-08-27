#include "MD.h"
#include "IteratorMD.h"
#include <exception>
#include <iostream>

using namespace std;


MD::MD(): prim(nullptr), ultim(nullptr), nrElem(0)  {

}


void MD::adauga(TCheie c, TValoare v) {
	/* de adaugat */
	NodCheie* p = prim;
	while (p != nullptr && p->cheie != c) {
		p = p->urm;
	}
	if (p == nullptr) {
		// Adaugă cheie nouă
		p = new NodCheie(c);
		if (ultim == nullptr) {
			prim = ultim = p;
		} else {
			ultim->urm = p;
			p->ant = ultim;
			ultim = p;
		}
	}
	NodValoare* nv = new NodValoare(v);
	if (p->ultimVal == nullptr) {
		p->primVal = p->ultimVal = nv;
	} else {
		p->ultimVal->urm = nv;
		nv->ant = p->ultimVal;
		p->ultimVal = nv;
	}
	nrElem++;
}

//O(n)




bool MD::sterge(TCheie c, TValoare v) {
	/* de adaugat */

	NodCheie* p = prim;
	while (p != nullptr && p->cheie != c)
		p = p->urm;
	if (p == nullptr)
		return false;
	NodValoare* q = p->primVal;
	while (q != nullptr && q->valoare != v)
		q = q->urm;
	if (q == nullptr)
		return false;
	if (q->ant != nullptr)
		q->ant->urm = q->urm;
	else
		p->primVal = q->urm;
	if (q->urm != nullptr)
		q->urm->ant = q->ant;
	else
		p->ultimVal = q->ant;
	delete q;
	nrElem--;

	if (p->primVal == nullptr) {
		// Șterge cheia dacă nu mai are valori
		if (p->ant != nullptr)
			p->ant->urm = p->urm;
		else
			prim = p->urm;
		if (p->urm != nullptr)
			p->urm->ant = p->ant;
		else
			ultim = p->ant;
		delete p;
	}
	return true;
	//return false;
}

//O(n + m)


vector<TValoare> MD::cauta(TCheie c) const {
	/* de adaugat */

	std::vector<TValoare> rezultat;
	NodCheie* p = prim;
	while (p != nullptr && p->cheie != c)
		p = p->urm;
	if (p != nullptr) {
		NodValoare* q = p->primVal;
		while (q != nullptr) {
			rezultat.push_back(q->valoare);
			q = q->urm;
		}
	}
	return rezultat;

	//return vector<TValoare>();
}
//O(n + m)



int MD::dim() const {
	/* de adaugat */
	return nrElem;
	//return 0;
}
//O(1)

bool MD::vid() const {
	/* de adaugat */
	return nrElem == 0;
	//return true;
}
//O(1)


IteratorMD MD::iterator() const {
	return IteratorMD(*this);
}
//O(1)


void MD::goleste() {
	NodCheie* p = prim;
	while (p != nullptr) {
		NodValoare* q = p->primVal;
		while (q != nullptr) {
			NodValoare* aux = q;
			q = q->urm;
			delete aux;
		}
		NodCheie* aux = p;
		p = p->urm;
		delete aux;
	}
	prim = nullptr;
	ultim = nullptr;
	nrElem = 0;
}
/*
*Subalgoritm goleste(m)

 pre:
   - m :MD

 post:
	-  m'=0
    - toate elementele din MD sunt eliminate

   p : NodCheie
   q : NodValoare
   aux : NodValoare

   p ← prim

   CatTimp p ≠ NIL executa
	   q ← p.primVal
	   CatTimp q ≠ NIL executa
		   aux ← q
		   q ← q.urm
		   dealoca(aux)
	   SfCatTimp
	   aux ← p
	   p ← p.urm
	   dealoca(aux)
   SfCatTimp

   prim ← NIL
   ultim ← NIL
   nrElem ← 0

SfSubalgoritm
 */
// Best Case: O(n)
//
// Average Case: O(n * m)
//
// Worst Case: O(n * m)






MD::~MD() {
	/* de adaugat */
	NodCheie* p = prim;
	while (p != nullptr) {
		NodValoare* q = p->primVal;
		while (q != nullptr) {
			NodValoare* aux = q;
			q = q->urm;
			delete aux;
		}
		NodCheie* aux = p;
		p = p->urm;
		delete aux;
	}
}
//O(n + m)
