#include <string.h>
#include "repo.h"
#include <stdlib.h>
#include "Cheltuieli.h"


ListaCheltuieli creeaza_lista(int capacitate_initiala) {
    /**
     * Creeaza o lista de cheltuieli cu o capacitate initiala specificata.
     *
     * @param capacitate_initiala Capacitatea initiala a listei.
     *
     * @return O lista de cheltuieli cu capacitatea initiala alocata si lungimea 0.
     */
    ListaCheltuieli lista;
    lista.lungime = 0;
    lista.capacitate = capacitate_initiala;
    lista.cheltuiala = (Cheltuiala*) malloc(capacitate_initiala * sizeof(Cheltuiala));

    return lista;
}

void distruge_lista(ListaCheltuieli *lista) {
    /**
     * Distruge lista de cheltuieli, eliberand memoria alocata pentru aceasta.
     *
     * @param lista Pointer catre lista de cheltuieli ce trebuie distrusa.
     *
     * Aceasta functie elibereaza memoria ocupata de lista si reseteaza campurile listei la valori implicite.
     */
    free(lista->cheltuiala);
    lista->cheltuiala = NULL;
    lista->lungime = 0;
    lista->capacitate = 0;
}

void redimensioneaza_lista(ListaCheltuieli *lista) {
    /**
     * Redimensioneaza lista de cheltuieli, dubland capacitatea acesteia.
     *
     * @param lista Pointer catre lista de cheltuieli ce urmeaza a fi redimensionata.
     *
     * Aceasta functie dubleaza capacitatea listei, alocand o noua memorie de dimensiune mai mare.
     */

    lista->capacitate *= 2;
    Cheltuiala *noua_cheltuiala = realloc(lista->cheltuiala, lista->capacitate * sizeof(Cheltuiala));

    lista->cheltuiala = noua_cheltuiala;
}


void micsoreaza_lista(ListaCheltuieli *lista) {
    /**
     * Micsoreaza lista de cheltuieli, reducand capacitatea acesteia la jumatate.
     * Daca capacitatea noua este mai mica decat 2, lista nu este redimensionata.
     *
     * @param lista Pointer catre lista de cheltuieli ce urmeaza a fi micsorata.
     *
     * Aceasta functie reduce capacitatea listei la jumatate si elibereaza memoria neutilizata.
     */

    int noua_capacitate = lista->capacitate / 2;
    if (noua_capacitate < 2) {
        return;
    }

    Cheltuiala *noua_lista = (Cheltuiala*) malloc( noua_capacitate * sizeof(Cheltuiala));


    for (int i = 0; i < lista->lungime; i++) {
        noua_lista[i] = lista->cheltuiala[i];
    }

    free(lista->cheltuiala);
    lista->cheltuiala = noua_lista;
    lista->capacitate = noua_capacitate;
}









int add(ListaCheltuieli *lista, int zi, float suma, const char *tip) {
    /**
     * Adauga o noua cheltuiala in lista de cheltuieli.
     *
     * @param lista Pointer catre lista de cheltuieli.
     * @param zi Ziua cheltuielii.
     * @param suma Suma cheltuielii.
     * @param tip Tipul cheltuielii.
     *
     * @return 0 daca adaugarea a fost cu succes,
     *        -1 daca lista este plina.
     */
    if (lista->lungime < MAX_CHELTUIELI) {
        if (lista->lungime == lista->capacitate) {
            redimensioneaza_lista(lista);
        }
        lista->cheltuiala[lista->lungime].zi = zi;
        lista->cheltuiala[lista->lungime].suma = suma;
        strcpy(lista->cheltuiala[lista->lungime].tip, tip);
        lista->lungime++;
        return 0;
    }
    return -1;
}

int modificare(ListaCheltuieli *lista, int index, int zi, float suma, const char *tip) {
    /**
     * Modifica o cheltuiala existenta din lista.
     *
     * @param lista Pointer catre lista de cheltuieli.
     * @param index Indexul cheltuielii de modificat.
     * @param zi Noua zi a cheltuielii.
     * @param suma Noua suma a cheltuielii.
     * @param tip Noul tip al cheltuielii.
     *
     * @return 0 daca modificarea a avut succes,
     *         -2 daca indexul este invalid.
     */
    if (index >= 0 && index < lista->lungime) {
        lista->cheltuiala[index].zi = zi;
        lista->cheltuiala[index].suma = suma;
        strncpy(lista->cheltuiala[index].tip, tip, 50);
        return 0;
    } else {
        return -2;
    }
}

int stergere(ListaCheltuieli *lista, int index) {
    /**
     * Sterge o cheltuiala din lista.
     *
     * @param lista Pointer catre lista de cheltuieli.
     * @param index Indexul cheltuielii de sters.
     *
     * @return 0 daca stergerea a avut succes,
     *        -2 daca indexul este invalid.
     */
    if (index < 0 || index >= lista->lungime) {
        return -2;
    }

    for (int i = index; i < lista->lungime - 1; i++) {
        lista->cheltuiala[i] = lista->cheltuiala[i + 1];
    }

    lista->lungime--;

    if (lista->lungime < lista->capacitate / 4 && lista->capacitate > 2) {
        micsoreaza_lista(lista);
    }

    return 0;
}

ListaCheltuieli* get_all(ListaCheltuieli *lista) {
    /**
     * Returneaza intreaga lista de cheltuieli.
     *
     * @param lista Pointer catre lista de cheltuieli.
     *
     * @return Pointer catre lista de cheltuieli.
     */
    if (!lista) return NULL;
    ListaCheltuieli *copia = (ListaCheltuieli*) malloc(sizeof(ListaCheltuieli));


    copia->capacitate = lista->capacitate;
    copia->lungime = lista->lungime;
    copia->cheltuiala = NULL;
    if (lista->lungime > 0) {
        copia->cheltuiala = (Cheltuiala*) malloc(lista->lungime * sizeof(Cheltuiala));

        memcpy(copia->cheltuiala, lista->cheltuiala, lista->lungime * sizeof(Cheltuiala));
    }
   return copia;
}
