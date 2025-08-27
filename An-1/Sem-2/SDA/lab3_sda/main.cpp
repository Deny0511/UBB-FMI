#include <iostream>
#include "TestExtins.h"
#include "TestScurt.h"
#include"MD.h"
#include"IteratorMD.h"
using namespace std;

int main() {


	// Creăm un obiect MultiDictionar
	MD m;

	// Adăugăm câteva perechi cheie-valoare
	m.adauga(1, 100);
	m.adauga(1, 101);
	m.adauga(2, 200);
	m.adauga(3, 300);

	// Afișăm dimensiunea
	cout << "Dimensiunea MD: " << m.dim() << endl;

	// Căutăm și afișăm valorile pentru cheile 1, 2 și 3
	cout << "Valori pentru cheie 1: ";
	auto v1 = m.cauta(1);
	for (auto val : v1) {
		cout << val << " ";
	}
	cout << endl;

	cout << "Valori pentru cheie 2: ";
	auto v2 = m.cauta(2);
	for (auto val : v2) {
		cout << val << " ";
	}
	cout << endl;

	cout << "Valori pentru cheie 3: ";
	auto v3 = m.cauta(3);
	for (auto val : v3) {
		cout << val << " ";
	}
	cout << endl;

	// Iterăm prin toată colecția și afișăm elementele
	cout << "Iteram prin MD:\n";
	IteratorMD it = m.iterator();
	while (it.valid()) {
		TElem e = it.element();
		cout << "Cheie: " << e.first << " -> Valoare: " << e.second << endl;
		it.urmator();
	}

	// Ștergem o pereche cheie-valoare
	cout << "Stergem perechea (1, 100): " << (m.sterge(1, 100) ? "Succes" : "Eșec") << endl;

	// Re-iterăm pentru a vedea schimbările
	cout << "Iteram din nou prin MD:\n";
	it.prim(); // Resetăm iteratorul la început
	while (it.valid()) {
		TElem e = it.element();
		cout << "Cheie: " << e.first << " -> Valoare: " << e.second << endl;
		it.urmator();
	}

	testAll();
	testAllExtins();
    cout<<"End";

}