#include "Colectie.h"
#include "IteratorColectie.h"
#include <iostream>

using namespace std;



Colectie::Colectie(){
	minim = 0;
	maxim = 0;
	dimensiune = 0;
	frecventa = nullptr;
	nrElemente = 0;
}

int Colectie::eliminaAparitii(int nr, TElem elem) {
	if (nr < 0) {
		throw std::invalid_argument("Numarul de aparitii de eliminat nu poate fi negativ");
	}

	if (elem < minim || elem > maxim || frecventa == nullptr || frecventa[elem - minim] == 0) {
		return 0;
	}

	int eliminat = std::min(nr, frecventa[elem - minim]);
	frecventa[elem - minim] -= eliminat;
	nrElemente -= eliminat;

	return eliminat;
}

//Complexitatea Timp :
// 0(1) — constanta
//
// Complexitatea Spațiu:
// 0(1) — nu se aloca nimic nou.
// Complexitatea totala: 0(1)


// PSEUDOCOD
// functie eliminaAparitii(c,nr, elem)
// 	daca nr < 0 atunci
// 		arunca o exceptie cu mesajul "Numar negativ!"
//  sf daca
//
// 	daca elem < minim SAU elem > maxim SAU frecventa == null SAU frecventa[elem - minim] == 0 atunci
// 		returneaza 0
//  sf daca
//
// 	index <- elem - minim
// 	eliminat <- min(nr, frecventa[index])
// 	frecventa[index] <- frecventa[index] - eliminat
// 	nrElemente <- nrElemente - eliminat
// 	tipareste eliminat
// sf funcție


void Colectie::realoca(int nouMin, int nouMax) {
	int nouDim = nouMax - nouMin + 1;
	int* nouFrecventa = new int[nouDim]();

	if (frecventa != nullptr) {
		for (int i = minim; i <= maxim; ++i) {
			nouFrecventa[i - nouMin] = frecventa[i - minim];
		}
		delete[] frecventa;
	}

	frecventa = nouFrecventa;
	minim = nouMin;
	maxim = nouMax;
	dimensiune = nouDim;
}
/*
 *Alocarea si copierea valorilor au complexitate O(nouDim) și O(dimensiune veche).
 */

void Colectie::adauga(TElem elem) {

	if (dimensiune == 0) {
		realoca(elem, elem);
	} else if (elem < minim || elem > maxim) {
		realoca(min(elem, minim), max(elem, maxim));
	}
	// Elementul este valid, actualizăm frecvența
	frecventa[elem - minim]++; // Creștem frecvența
	nrElemente++; // Incrementăm nrElemente
}


bool Colectie::sterge(TElem elem) {

	if (elem < minim || elem > maxim || frecventa == nullptr || frecventa[elem - minim] == 0) {
		return false; // Elementul nu este valid
	}

	frecventa[elem - minim]--;
	nrElemente--;
	return true;
}
/*
 *complexitatea totala a functiei este O(1)
 */

bool Colectie::cauta(TElem elem) const {

	if (elem < minim || elem > maxim || frecventa == nullptr) {
		return false;
	}
	return frecventa[elem - minim] > 0;
}
/*
 *complexitatea totala a functiei este O(1)
 */

int Colectie::nrAparitii(TElem elem) const {

	if (elem < minim || elem > maxim || frecventa == nullptr) {
		return 0;
	}
	return frecventa[elem - minim];
}
/*
 *complexitatea totala a functiei este O(1)
 */


int Colectie::dim() const {
	return nrElemente;
}

/*
 *complexitatea totala a functiei este O(1)
 */


bool Colectie::vida() const {
	return nrElemente == 0;
}
/*
 *complexitatea totala a functiei este O(1)
 */


IteratorColectie Colectie::iterator() const {
	return  {IteratorColectie(*this)};
}

/*
 *complexitatea totala a functiei este O(1)
 */


Colectie::~Colectie() {
	delete[] frecventa;
}

/*
 *complexitatea totala a functiei este O(1)
 */
