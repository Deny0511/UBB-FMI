#include "IteratorColectie.h"
#include "Colectie.h"
#include <stdexcept>
#include <iostream>


IteratorColectie::IteratorColectie(const Colectie& c): col(c),pozitie(0), aparitiiCurente(0) {
	while (pozitie < col.dimensiune && col.frecventa[pozitie] == 0) {
		pozitie++;
	}
	if (pozitie < col.dimensiune) {
		aparitiiCurente = col.frecventa[pozitie];
	}
}
/*
 *  Complexitatea totala in caz favorabil:
 *   in cazul in care vectorul de frecventa contine un element nenul la inceput, complexitatea totala a constructorului este O(1).
 *	Complexitatea totală în caz defavorabil:
 *   bucla va parcurge intregul vector de frecventa, iar complexitatea totala a constructorului va fi O(dimensiune), adica O(col.dimensiune).
 */


void IteratorColectie::prim() {
	pozitie = 0;
	while (pozitie < col.dimensiune && col.frecventa[pozitie] == 0) {
		pozitie++;
	}
	if (pozitie < col.dimensiune) {
		aparitiiCurente = col.frecventa[pozitie];
	}
}

/*
 * Caz favorabil: Daca vectorul contine un element nenul la inceput, complexitatea totala va fi O(1).
 *
 * Caz defavorabil: Daca vectorul contine doar elemente zero si trebuie sa parcurga aproape intregul vector, complexitatea va fi O(dimensiune), adica O(col.dimensiune).
 *
 */


void IteratorColectie::urmator() {
	if (!valid()) {
		std::cout << "Iterator invalid la pozitia: " << pozitie << std::endl;
		throw std::out_of_range("Iterator invalid");
	}

	aparitiiCurente--;
	if (aparitiiCurente == 0) {
		pozitie++;
		while (pozitie < col.dimensiune && col.frecventa[pozitie] == 0) {
			pozitie++;
		}
		if (pozitie < col.dimensiune) {
			aparitiiCurente = col.frecventa[pozitie];
		}else {
			// Dacă am depășit dimensiunea colecției, setăm aparitiiCurente la 0
			aparitiiCurente = 0;
		}
	}
}

/*
 * Caz favorabil: O(1) (daca există elemente nenule imediat disponibile).
 *
 * Caz defavorabil: O(dimensiune), adica O(col.dimensiune) (daca vectorul contine multe elemente zero si iteratorul trebuie sa parcurga mult din colectie pentru a gasi un element nenul).
 */


bool IteratorColectie::valid() const {
	if (pozitie >= col.dimensiune || col.frecventa[pozitie] == 0) {
		return false;
	}

	return true;
}
/*
 *Complexitatea functiei valid() este O(1).
 */

TElem IteratorColectie::element() const {
	if (!valid()) {
		throw std::out_of_range("Iterator invalid");
	}
	TElem element = col.minim + pozitie;
	return element;
}
/*
 *Complexitatea functiei element() este O(1)
 */