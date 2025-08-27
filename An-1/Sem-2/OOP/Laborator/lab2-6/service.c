#include<stdio.h>
#include "service.h"
#include <stdlib.h>
#include <string.h>
#include "repo.h"
#include "validator.h"
#include <errno.h>

int add_cheltuiala(ListaCheltuieli *lista, int zi, float suma, const char *tip) {
    /**
     * Adauga o cheltuiala in lista, dupa ce aceasta este validata.
     *
     * @param lista Pointer catre lista de cheltuieli.
     * @param zi Ziua cheltuielii.
     * @param suma Suma cheltuielii.
     * @param tip Tipul cheltuielii.
     *
     * @return 0 daca adaugarea a avut succes,
     *         eroare daca este invalida (zi, suma, tip).
     */

    int eroare = valideaza_zi(zi);
    if (eroare != 0) {
        return eroare;
    }

    eroare = valideaza_suma(suma);
    if (eroare != 0) {
        return eroare;
    }

    eroare = valideaza_tip(tip);
    if (eroare != 0) {
        return eroare;
    }


    return add(lista, zi, suma, tip);
}

int modifica_cheltuiala(ListaCheltuieli *lista, int index, int zi, float suma, const char *tip) {
    /**
     * Modifica o cheltuiala din lista, dupa ce aceasta este validata.
     *
     * @param lista Pointer catre lista de cheltuieli.
     * @param index Indexul cheltuielii de modificat.
     * @param zi Noua zi a cheltuielii.
     * @param suma Noua suma a cheltuielii.
     * @param tip Noul tip al cheltuielii.
     *
     * @return 0 daca modificarea a avut succes,
     *         eroare daca este invalida (zi, suma, tip).
     */
    int eroare = valideaza_zi(zi);
    if (eroare != 0) {
        return eroare;
    }

    eroare = valideaza_suma(suma);
    if (eroare != 0) {
        return eroare;
    }

    eroare = valideaza_tip(tip);
    if (eroare != 0) {
        return eroare;
    }

    return modificare(lista, index, zi, suma, tip);
}

int sterge_cheltuiala(ListaCheltuieli *lista, int index) {
    /**
     * Sterge o cheltuiala din lista.
     *
     * @param lista Pointer catre lista de cheltuieli.
     * @param index Indexul cheltuielii de sters.
     *
     * @return 0 daca stergerea a avut succes.
     */
    return stergere(lista, index);
}
 ListaCheltuieli* vizualizare(ListaCheltuieli *lista, const char *criteriu, const char *valoare) {
     /**
      * Vizualizeaza cheltuieli pe baza unui criteriu (zi, suma, tip).
      *
      * @param lista Pointer catre lista de cheltuieli.
     * @param criteriu Criteriul dupa care se face cautarea (zi, suma, tip).
      * @param valoare Valoarea asociata criteriului.
      *
      * @return 0 daca au fost gasite cheltuieli,
      *        -1 daca nu au fost gasite.
      */
     ListaCheltuieli *lista_filtrata = (ListaCheltuieli*) malloc(sizeof(ListaCheltuieli));
     if (!lista_filtrata) return NULL;

     lista_filtrata->capacitate = lista->capacitate;
     lista_filtrata->lungime = 0;
     lista_filtrata->cheltuiala = (Cheltuiala*) malloc(lista->capacitate * sizeof(Cheltuiala));

    for (int i = 0; i < lista->lungime; i++) {
        if (strcmp(criteriu, "zi") == 0) {
            int zi_val = atoi(valoare);
            if (lista->cheltuiala[i].zi == zi_val) {
                lista_filtrata->cheltuiala[lista_filtrata->lungime] = lista->cheltuiala[i];
                lista_filtrata->lungime++;
            }
        }
        else if (strcmp(criteriu, "suma") == 0) {
            double suma_val = atof(valoare);
            if (lista->cheltuiala[i].suma == suma_val) {
                lista_filtrata->cheltuiala[lista_filtrata->lungime] = lista->cheltuiala[i];
                lista_filtrata->lungime++;
            }
        }
        else if (strcmp(criteriu, "tip") == 0) {
            if (strcmp(lista->cheltuiala[i].tip, valoare) == 0) {
                lista_filtrata->cheltuiala[lista_filtrata->lungime] = lista->cheltuiala[i];
                lista_filtrata->lungime++;
            }
        }
    }

     if (lista_filtrata->lungime == 0) {
         free(lista_filtrata->cheltuiala);
         free(lista_filtrata);
         return NULL;
     }
     free(lista_filtrata->cheltuiala);
     return lista_filtrata;
 }


int compara_suma(const void *a, const void *b) {
    /**
     * Compara doua cheltuieli pe baza sumei pentru ordonare.
     *
     * @param a Primul element.
     * @param b Al doilea element.
     *
     * @return Diferenta intre sumele celor doua cheltuieli.
     */
    return ((Cheltuiala *)a)->suma - ((Cheltuiala *)b)->suma;
}

int compara_suma_desc(const void *a, const void *b) {
    /**
     * Compara doua cheltuieli pe baza sumei pentru ordonare.
     *
     * @param a Primul element.
     * @param b Al doilea element.
     *
     * @return Diferenta intre sumele celor doua cheltuieli.
     */
    return ((Cheltuiala *)b)->suma - ((Cheltuiala *)a)->suma;
}

int compara_tip(const void *a, const void *b) {
    /**
     * Compara doua cheltuieli pe baza tipului pentru ordonare.
     *
     * @param a Primul element.
     * @param b Al doilea element.
     *
    * @return - < 0 daca tipul cheltuielii din a este mai mic  decat tipul cheltuielii din b.
     *          - 0 daca tipurile celor doua cheltuieli sunt egale.
     *          - > 0 daca tipul cheltuielii din a este mai mare decat tipul cheltuielii din b.
     */
    return strcmp(((Cheltuiala *)a)->tip, ((Cheltuiala *)b)->tip);
}

int compara_tip_desc(const void *a, const void *b) {
    /**
     * Compara doua cheltuieli pe baza tipului pentru ordonare.
     *
     * @param a Primul element.
     * @param b Al doilea element.
     * @return  - < 0 daca tipul cheltuielii din b este mai mic  decat tipul cheltuielii din a.
     *          - 0 daca tipurile celor doua cheltuieli sunt egale.
     *          - > 0 daca tipul cheltuielii din b este mai mare decat tipul cheltuielii din a.
     */
    return strcmp(((Cheltuiala *)b)->tip, ((Cheltuiala *)a)->tip);
}

void ordonare(ListaCheltuieli *lista, const char *criteriu,int(*compara)(const void *a, const void *b)) {
    /**
     * Ordoneaza lista de cheltuieli crescator dupa suma acestora sau dupa tip.
     *
     * @param lista Pointer catre lista de cheltuieli.
     */
    if (strcmp(criteriu, "suma") == 0) {
        qsort(lista->cheltuiala, lista->lungime, sizeof(Cheltuiala), compara);
    } else if (strcmp(criteriu, "tip") == 0) {
        qsort(lista->cheltuiala, lista->lungime, sizeof(Cheltuiala), compara);
    }
}


void ordonare_desc(ListaCheltuieli *lista,const char *criteriu,int(*compara)(const void *a, const void *b)) {
    /**
     * Ordoneaza lista de cheltuieli descrescator dupa suma acestora sau dupa tip.
     *
     * @param lista Pointer catre lista de cheltuieli.
     */
    if (lista && lista->cheltuiala) {
        if (strcmp(criteriu, "suma") == 0) {
            qsort(lista->cheltuiala, lista->lungime, sizeof(Cheltuiala), compara);
        } else if (strcmp(criteriu, "tip") == 0) {
            qsort(lista->cheltuiala, lista->lungime, sizeof(Cheltuiala), compara);
        }
    }
}

ListaCheltuieli* get_all_(ListaCheltuieli *lista) {
    /**
     * Obtine lista completa de cheltuieli.
     *
     * @param lista Pointer catre lista de cheltuieli.
     *
     * @return Pointer catre lista de cheltuieli.
     */
    return get_all(lista);
}
