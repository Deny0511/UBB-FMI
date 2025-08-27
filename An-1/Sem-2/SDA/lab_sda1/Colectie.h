#pragma once

#define NULL_TELEM -1

typedef int TElem;

class IteratorColectie;

class Colectie
{
	friend class IteratorColectie;

private:
	int* frecventa;  // Vector de frecvențe
	int minim, maxim; // Valorile minime și maxime din interval
	int dimensiune;   // Dimensiunea vectorului de frecvențe
	int nrElemente;   // Numărul total de elemente din colecție
	void realoca(int nouMin, int nouMax);
public:
		//constructorul implicit
		Colectie();

		//elimina aparitiile unui element
    	int eliminaAparitii(int nr, TElem elem);

		//adauga un element in colectie
		void adauga(TElem e);

		//sterge o aparitie a unui element din colectie
		//returneaza adevarat daca s-a putut sterge
		bool sterge(TElem e);

		//verifica daca un element se afla in colectie
		bool cauta(TElem elem) const;

		//returneaza numar de aparitii ale unui element in colectie
		int nrAparitii(TElem elem) const;


		//intoarce numarul de elemente din colectie;
		int dim() const;

		//verifica daca colectia e vida;
		bool vida() const;

		//returneaza un iterator pe colectie
		IteratorColectie iterator() const;

		// destructorul colectiei
		~Colectie();


};

