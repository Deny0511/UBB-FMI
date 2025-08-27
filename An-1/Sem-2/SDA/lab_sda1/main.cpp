#include <iostream>
#include "Colectie.h"
#include "IteratorColectie.h"
#include "TestExtins.h"
#include "TestScurt.h"
using namespace std;


int main() {
	testAll();
	testAllExtins();
	Colectie c;

	c.adauga(5);
	c.adauga(10);
	c.adauga(-1);
	c.adauga(2);
	c.adauga(3);
	c.adauga(10);
	c.adauga(5);
	c.adauga(5);
	c.adauga(-5);

	std::cout << "Dimensiunea colectiei: " << c.dim() << std::endl;
	std::cout << "Nr. aparitii pentru 5: " << c.nrAparitii(5) << std::endl;
	std::cout << "Nr. aparitii pentru 10: " << c.nrAparitii(10) << std::endl;
	std::cout << "Nr. aparitii pentru -5: " << c.nrAparitii(-5) << std::endl;
	std::cout << "Nr. aparitii pentru -1: " << c.nrAparitii(-1) << std::endl;

	c.sterge(5);
	std::cout << "Nr. aparitii pentru 5 dupa stergere: " << c.nrAparitii(5) << std::endl;

	try {
		int eliminate = c.eliminaAparitii(2, 5);
		std::cout << "Au fost eliminate " << eliminate << " aparitii ale lui 5." << std::endl;
	} catch (const std::exception& e) {
		std::cout << "Exceptie prinsa: " << e.what() << std::endl;
	}

	std::cout << "Nr. aparitii pentru 5 dupa eliminaAparitii: " << c.nrAparitii(5) << std::endl;

	// Test negativ - trebuie să arunce excepție
	try {
		c.eliminaAparitii(-3, 10);
	} catch (const std::exception& e) {
		std::cout << "Exceptie la apel cu nr negativ: " << e.what() << std::endl;
	}

    return 0;
}
