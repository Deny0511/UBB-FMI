#ifndef SERVICE_H
#define SERVICE_H
#include "Cheltuieli.h"


int add_cheltuiala(ListaCheltuieli *lista, int zi, float suma, const char *tip);
int modifica_cheltuiala(ListaCheltuieli *lista, int index, int zi, float suma, const char *tip);
int sterge_cheltuiala(ListaCheltuieli *lista, int index);
ListaCheltuieli* vizualizare(ListaCheltuieli *lista, const char *criteriu, const char *valoare);
void ordonare(ListaCheltuieli *lista,const char *criteriu,int(*compara)(const void *a, const void *b));
void ordonare_desc(ListaCheltuieli *lista,const char *criteriu,int(*compara)(const void *a, const void *b));
ListaCheltuieli* get_all_(ListaCheltuieli *lista);
int compara_suma(const void *a, const void *b);
int compara_tip(const void *a, const void *b);
int compara_suma_desc(const void *a, const void *b);
int compara_tip_desc(const void *a, const void *b);



#endif