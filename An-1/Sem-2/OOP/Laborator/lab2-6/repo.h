

#ifndef REPO_H
#define REPO_H
#include "cheltuieli.h"

int add(ListaCheltuieli *lista, int zi, float suma, const char *tip);
int modificare(ListaCheltuieli *lista, int index, int zi, float suma, const char *tip);
int stergere(ListaCheltuieli *lista, int index);
ListaCheltuieli* get_all(ListaCheltuieli *lista);

ListaCheltuieli creeaza_lista(int capacitate_initiala);
void distruge_lista(ListaCheltuieli *lista);
void redimensioneaza_lista(ListaCheltuieli *lista);
void micsoreaza_lista(ListaCheltuieli *lista);

#endif //REPO_H
