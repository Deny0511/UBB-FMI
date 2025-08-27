#include "TestExtins.h"
#include "TestScurt.h"
#include <iostream>
#include "Multime.h"
#include "IteratorMultime.h"
using namespace std;

int main() {
	Multime m;

	// Adăugare elemente
	m.adauga(3);
	m.adauga(1);
	m.adauga(7);
	m.adauga(3); // nu va fi adăugat, fiind duplicat

	std::cout << "Elementele din multime:\n";
	IteratorMultime it = m.iterator();
	for (it.prim(); it.valid(); it.urmator()) {
		std::cout << it.element() << " ";
	}
	std::cout << "\n";

	// Ștergere
	bool sters = m.sterge(1);
	std::cout << "Stergere 1: " << (sters ? "reusita" : "esec") << "\n";

	// Verificare existență
	std::cout << "Exista 7 in multime? " << (m.cauta(7) ? "Da" : "Nu") << "\n";
	std::cout << "Exista 1 in multime? " << (m.cauta(1) ? "Da" : "Nu") << "\n";

	// Afișare dimensiune
	std::cout << "Dimensiunea multimii: " << m.dim() << "\n";

	testAll();
	testAllExtins();

    cout << "That's all!" << endl;

}
