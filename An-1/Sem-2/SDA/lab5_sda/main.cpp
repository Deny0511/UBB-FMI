#include <iostream>
#include "Matrice.h"
#include "TestExtins.h"
#include "TestScurt.h"

using namespace std;


int main() {

	try {
		// Creează o matrice 5x5
		Matrice m(5, 5);

		std::cout << "Nr linii: " << m.nrLinii() << "\n";
		std::cout << "Nr coloane: " << m.nrColoane() << "\n\n";

		// Modifică câteva elemente
		m.modifica(1, 2, 10);
		m.modifica(3, 4, 20);
		m.modifica(0, 0, 5);

		// Citește și afișează acele elemente
		std::cout << "Element la (1,2): " << m.element(1, 2) << "\n";
		std::cout << "Element la (3,4): " << m.element(3, 4) << "\n";
		std::cout << "Element la (0,0): " << m.element(0, 0) << "\n";

		// Acces la o poziție care nu are valoare -> trebuie să dea 0
		std::cout << "Element la (2,2): " << m.element(2, 2) << " (NULL_TELEMENT)\n";

		// Modificare: șterge valoarea de la (1,2)
		int vechi = m.modifica(1, 2, NULL_TELEMENT);
		std::cout << "Valoare veche la (1,2) a fost: " << vechi << "\n";
		std::cout << "Acum la (1,2): " << m.element(1, 2) << " (NULL_TELEMENT)\n";

	} catch (const std::exception& e) {
		std::cerr << "Exceptie: " << e.what() << "\n";
	}






    	testAll();
    	testAllExtins();



    cout<<"End";
}