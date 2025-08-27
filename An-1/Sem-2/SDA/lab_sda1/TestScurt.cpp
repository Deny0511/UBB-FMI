#include "TestScurt.h"
#include <assert.h>
#include "Colectie.h"
#include "IteratorColectie.h"
#include <stdexcept>


void testEliminaAparitii() {
	Colectie c;
	c.adauga(10);
	c.adauga(10);
	c.adauga(10);
	c.adauga(20);

	assert(c.nrAparitii(10) == 3);

	int eliminat = c.eliminaAparitii(2, 10);
	assert(eliminat == 2);
	assert(c.nrAparitii(10) == 1);

	eliminat = c.eliminaAparitii(5, 10);  // mai are doar 1, se elimina toate
	assert(eliminat == 1);
	assert(c.nrAparitii(10) == 0);

	eliminat = c.eliminaAparitii(1, 10); // nu mai exista
	assert(eliminat == 0);

	try {
		c.eliminaAparitii(-1, 20);
		assert(false);
	} catch (const std::invalid_argument&) {
		assert(true); // exceptia e aruncata corect
	}
}


void testAll() { //apelam fiecare functie sa vedem daca exista
	Colectie c;
	assert(c.vida() == true);
	assert(c.dim() == 0); //adaug niste elemente
	c.adauga(5);
	c.adauga(1);
	c.adauga(10);
	c.adauga(7);
	c.adauga(1);
	c.adauga(11);
	c.adauga(-3);
	assert(c.dim() == 7);
	assert(c.cauta(10) == true);
	assert(c.cauta(16) == false);
	assert(c.nrAparitii(1) == 2);
	assert(c.nrAparitii(7) == 1);
	assert(c.sterge(1) == true);
	assert(c.sterge(6) == false);
	assert(c.dim() == 6);
	assert(c.nrAparitii(1) == 1);
	IteratorColectie ic = c.iterator();
	ic.prim();
	while (ic.valid()) {
		TElem e = ic.element();
		ic.urmator();
	}
	testEliminaAparitii();

}